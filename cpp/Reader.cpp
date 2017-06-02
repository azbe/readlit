#include "src/Reader.h"
#include "src/Constants.h"

#include <QResizeEvent>
#include <QThread>
#include <QDebug>
#include <QPainter>

#include "src/ImageLoader.h"

Reader::Reader(QWidget *parent) : QWidget(parent)
{
    book = nullptr;
    scrollArea = nullptr;
    scrollBar = nullptr;
    pageArea = nullptr;
    pageAreaLayout = nullptr;
    pages = nullptr;
    isActualized = nullptr;
}

Reader::Reader(QWidget *parent, const QString& path) : QWidget(parent)
{
    book = Poppler::Document::load(path);
    if(!book || book->isLocked())
    {
        qDebug() << "Reader::Reader(QWidget,QString,int) - Error opening poppler document at path = " << path << "\nUsing empty constructor instead";
        book = nullptr;
        scrollArea = nullptr;
        scrollBar = nullptr;
        pageArea = nullptr;
        pageAreaLayout = nullptr;
        pages = nullptr;
        isActualized = nullptr;
        delete book;
        return;
    }
    if (!book->page(0))
    {
        qDebug() << "Reader::Reader(QWidget,QString,int) - Error opening poppler page 0 for aspect ratio\nUsing empty constructor instead";
        book = nullptr;
        scrollArea = nullptr;
        scrollBar = nullptr;
        pageArea = nullptr;
        pageAreaLayout = nullptr;
        pages = nullptr;
        isActualized = nullptr;
        delete book;
        return;
    }
    Poppler::Page *page = book->page(0);
    pageAspectRatio = (ReaderConstants::SCAN_DEFAULT_VERTICAL_RES * (page->pageSizeF().height() / 72)) / (ReaderConstants::SCAN_DEFAULT_HORIZONTAL_RES * (page->pageSizeF().width() / 72));
    delete page;
    updatePageCount();

    scrollArea = new QScrollArea(this);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollBar = scrollArea->verticalScrollBar();
    scrollBar->setMaximum(pageCount);
    lastScrollBarValue = 0;
    isMouseScrolling = false;
    QObject::connect(scrollBar, SIGNAL(sliderPressed()), this, SLOT(scrollBarPressed()));
    QObject::connect(scrollBar, SIGNAL(sliderReleased()), this, SLOT(scrollBarReleased()));
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged()));

    pageArea = new QFrame(scrollArea);
    resizeTimerId = 0;
    pageAreaLayout = new QVBoxLayout(pageArea);

    pages = new QLabel*[pageCount];
    isActualized = new bool[pageCount];
    for (int index = 0; index < pageCount; index++)
    {
        pages[index] = new QLabel(pageArea);
        pageAreaLayout->addWidget(pages[index]);

        isActualized[index] = false;
    }

    pageScrollSize = (1.0 * pages[0]->height() + pageAreaLayout->spacing() - scrollBar->minimum()) / (scrollBar->maximum() - scrollBar->minimum());
    updateCurrentPage();
    scrollArea->setWidget(pageArea);

    setFocusPolicy(Qt::StrongFocus);
}

bool Reader::isNull() const
{
    return !book;
}

Reader::~Reader()
{
    if (pages)
        for (int index = 0; index < pageCount; index++)
            if (pages[index])
                delete pages[index];
    delete[] pages;
    delete[] isActualized;
    delete pageAreaLayout;
    delete pageArea;
    delete scrollBar;
    delete scrollArea;
    delete book;
}

QImage Reader::getPageImage(const int& index) const
{
    Poppler::Page *page = book->page(index);
    if (!page)
    {
        qDebug() << "Reader::getPageImage - Error receiving poppler page #" << index;
        return QImage();
    }
    QImage image = page->renderToImage(ReaderConstants::SCAN_DEFAULT_HORIZONTAL_RES, ReaderConstants::SCAN_DEFAULT_VERTICAL_RES);
    delete page;
    if (image.isNull())
    {
        qDebug() << "Reader::getPageImage - Error rendering poppler page #" << index << " to image";
        return QImage();
    }
    return image;
}

void Reader::goToPage(int page)
{
    scrollBar->setValue(page * pageScrollSize * (scrollBar->maximum() - scrollBar->minimum()) + scrollBar->minimum());
}

void Reader::updatePageCount()
{
    int index;
    Poppler::Page *page;
    for(index = 0;; index++)
    {
        page = book->page(index);
        if (!page)
        {
            delete page;
            break;
        }
        delete page;
    }

    pageCount = index;
}

void Reader::updateCurrentPage()
{
    currentPage = (int)(getScrollBarPercent() / pageScrollSize);
    if (currentPage >= pageCount) currentPage = pageCount - 1;
}

double Reader::getScrollBarPercent() const
{
    if (1.0 * scrollBar->maximum() - scrollBar->minimum() != 0)
        return (scrollBar->value() - scrollBar->minimum())/(1.0 * scrollBar->maximum() - scrollBar->minimum());
    else
    {
        qDebug() << "Reader::getScrollBarPercent - Error: division by 0 - scrollBar->maximum() = " << scrollBar->maximum() << " scrollBar->minimum() = " << scrollBar->minimum() << "\nReturning lastScrollBarValue = " << lastScrollBarValue;
        return lastScrollBarValue;
    }
}

void Reader::resizeEvent(QResizeEvent *event)
{
    if (!book) return;
    isMouseScrolling = true;
    newSize = size();
    if(resizeTimerId)
    {
        killTimer(resizeTimerId);
        resizeTimerId = 0;
    }
    resizeTimerId = startTimer(ReaderConstants::RESIZE_DEFAULT_TIMER);
}

void Reader::timerEvent(QTimerEvent *te)
{
    if(te->timerId() == resizeTimerId)
    {
        scrollArea->resize(newSize);
        pageArea->resize(newSize.width() - 15, pageCount * pageAspectRatio * (newSize.width() - 15)); //magic numbers

        for (int index = 0; index < pageCount; index++)
        {
            pages[index]->clear();
            isActualized[index] = false;
        }
        scrollBar->setValue(lastScrollBarValue * scrollBar->maximum());
        pageScrollSize = (1.0 * pages[0]->height() + pageAreaLayout->spacing() - scrollBar->minimum()) / (scrollBar->maximum() - scrollBar->minimum());
        isMouseScrolling = false;
        startTimer(100); //magic number

        killTimer(te->timerId());
        resizeTimerId = 0;
    }
    else
    {
        scrollBarValueChanged();
    }
}

void Reader::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
        case Qt::Key_Right:
        {
            if (currentPage < pageCount - 1)
                scrollBar->setValue(scrollBar->value() + pages[0]->height() + pageAreaLayout->spacing());
            break;
        }
        case Qt::Key_Left:
        {
            if (currentPage > 0)
                scrollBar->setValue(scrollBar->value() - pages[0]->height() - pageAreaLayout->spacing());
            break;
        }
        case Qt::Key_Down:
        {
            if (scrollBar->value() < scrollBar->maximum() - 9)
                scrollBar->setValue(scrollBar->value() + 10);
            break;
        }
        case Qt::Key_Up:
        {
            if (scrollBar->value() > 9)
                scrollBar->setValue(scrollBar->value() - 10);
            break;
        }
    }
}

void Reader::actualizeView(int page)
{
    QThread *imageLoadingThread = new QThread();
    if (page < 0 || page > pageCount)
    {
        qDebug() << "Reader::actualizeView - Error: pagenum = " << page << " too big or too small (pageCount = " << pageCount << ")";
        return;
    }
    if (!book->page(page))
    {
        qDebug() << "Reader::actualizeView - Error receiving poppler page " << page;
        return;
    }
    ImageLoader *imageLoader = new ImageLoader(Q_NULLPTR, book->page(page), page, pages[page]->width(), pages[page]->height());
    imageLoader->moveToThread(imageLoadingThread);
    QObject::connect(imageLoader, SIGNAL(result(QImage,int)), this, SLOT(handleImage(QImage,int)));
    QObject::connect(imageLoadingThread, SIGNAL(started()), imageLoader, SLOT(process()));
    QObject::connect(imageLoader, SIGNAL(finished()), imageLoadingThread, SLOT(quit()));
    QObject::connect(imageLoader, SIGNAL(finished()), imageLoader, SLOT(deleteLater()));
    QObject::connect(imageLoadingThread, SIGNAL(finished()), imageLoadingThread, SLOT(deleteLater()));
    imageLoadingThread->start();
}

void Reader::scrollBarValueChanged()
{
    if (isMouseScrolling) return;
    updateCurrentPage();
    for (int index = currentPage - ReaderConstants::PRELOAD_DEFAULT_NUMBER_PAGES; index <= currentPage + ReaderConstants::PRELOAD_DEFAULT_NUMBER_PAGES; index++)
    {
        if (index < 0 || index >= pageCount)
            continue;
        if (!isActualized[index])
        {
            isActualized[index] = true;
            actualizeView(index);
        }
    }
    lastScrollBarValue = getScrollBarPercent();
}

void Reader::scrollBarPressed()
{
    isMouseScrolling = true;
}

void Reader::scrollBarReleased()
{
    lastScrollBarValue = getScrollBarPercent();
    updateCurrentPage();
    for (int index = currentPage - ReaderConstants::PRELOAD_DEFAULT_NUMBER_PAGES; index <= currentPage + ReaderConstants::PRELOAD_DEFAULT_NUMBER_PAGES; index++)
    {
        if (index < 0 || index >= pageCount)
            continue;
        if (!isActualized[index])
        {
            isActualized[index] = true;
            actualizeView(index);
        }
    }
    isMouseScrolling = false;
}

void Reader::handleImage(QImage image, int pagenum)
{
    if (pagenum < 0 || pagenum >= pageCount)
    {
        qDebug() << "Reader::handleImage - Error: pagenum = " << pagenum << " too big or too small";
        return;
    }
    if (image.isNull())
    {
        qDebug() << "Reader::handleImage - Error: received null image from ImageLoader";
        if (isActualized[pagenum])
            isActualized[pagenum] = false;
        return;
    }
    pages[pagenum]->setPixmap(QPixmap::fromImage(image));
}

void Reader::find(const QString &search)
{
    if (search.size() < 2)
        return;
    for (int index = currentPage; index < pageCount; index++)
    {
        Poppler::Page *page = book->page(index);
        if (!page)
            break;
        QList<QRectF> found = page->search(search, Poppler::Page::CaseInsensitive);
        int which = -1;
        for (int i = 0; i < found.size(); i++)
        {
            qDebug() << pages[0]->height() * (found[i].top() / page->pageSizeF().height()) << (getScrollBarPercent() - (currentPage * pageScrollSize)) * (scrollBar->maximum() - scrollBar->minimum()) + scrollBar->minimum();
            if ((index != currentPage) || (pages[0]->height() * (found[i].top() / page->pageSizeF().height()) > 1.0 + (getScrollBarPercent() - (currentPage * pageScrollSize)) * (scrollBar->maximum() - scrollBar->minimum()) + scrollBar->minimum()))
            {
                qDebug() << "Taken";
                which = i;
                break;
            }
        }
        if (which > -1)
        {
            goToPage(index);
            scrollBar->setValue(scrollBar->value() + pages[0]->height() * (found[which].top() / page->pageSizeF().height()));
            delete page;
            break;
        }
        delete page;
    }
}
