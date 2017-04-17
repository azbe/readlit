#include "src/Reader.h"
#include "src/Constants.h"

#include <QResizeEvent>
#include <QThread>

#include "src/ImageLoader.h"

Reader::Reader(QWidget *parent, const QString& path, const int& startingPage) : QWidget(parent)
{
    book = Poppler::Document::load(path);
    if(book); //TO DO: erori

    Poppler::Page *page = book->page(0);
    pageAspectRatio = (600 * (page->pageSizeF().height() / 72)) / (600 * (page->pageSizeF().width() / 72));
    delete page;
    updatePageCount();

    scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollBar = scrollArea->verticalScrollBar();
    scrollBar->setMaximum(pageCount);
    lastScrollBarValue = 0;
    isMouseScrolling = false;
    QObject::connect(scrollBar, SIGNAL(sliderPressed()), this, SLOT(scrollBarPressed()));
    QObject::connect(scrollBar, SIGNAL(sliderReleased()), this, SLOT(scrollBarReleased()));
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged()));

    updateCurrentPage();
    pageArea = new QFrame(scrollArea);
    resizeTimerId = 0;
    //pageArea->setStyleSheet("border: 3px solid blue");
    QVBoxLayout *pageAreaLayout = new QVBoxLayout(pageArea);

    pages = new QLabel*[pageCount];
    isActualized = new bool[pageCount];
    for (int index = 0; index < pageCount; index++)
    {
        pages[index] = new QLabel(pageArea);
        //pages[index]->setStyleSheet("border: 1px solid red");
        pageAreaLayout->addWidget(pages[index]);

        isActualized[index] = false;
    }

    scrollArea->setWidget(pageArea);
}

Reader::~Reader()
{
    if(scrollArea) delete scrollArea;
    if(book) delete book;
}

void Reader::changeBook(const QString &newPath)
{
    for (int index = 0; index < pageCount; index++)
    {
        pages[index]->clear();
        isActualized[index] = false;
    }

    if (book) delete book;
    book = Poppler::Document::load(newPath);

    Poppler::Page *page = book->page(0);
    pageAspectRatio = (600 * (page->pageSizeF().height() / 72)) / (600 * (page->pageSizeF().width() / 72));
    delete page;
    updatePageCount();

    scrollBar->setValue(scrollBar->minimum());
    scrollBar->setMaximum(pageCount);
    lastScrollBarValue = 0;
    isMouseScrolling = false;
    updateCurrentPage();

    resize(size());
}

QImage Reader::getPageImage(const int& index) const
{
    //TO DO: erori
    Poppler::Page *page = book->page(index);
    if (!page);
    QImage image = page->renderToImage(ReaderConstants::SCAN_DEFAULT_HORIZONTAL_RES, ReaderConstants::SCAN_DEFAULT_VERTICAL_RES);
    if (image.isNull());
    delete page;
    return image;
}

void Reader::updatePageCount()
{
    int index;
    for(index = 0;; index++)
        if (!(book->page(index)))
            break;
    pageCount = index;
}

void Reader::updateCurrentPage()
{
    currentPage = (scrollBar->value() - scrollBar->minimum())/(1.0 * scrollBar->maximum() - scrollBar->minimum()) * pageCount;
    if (currentPage == pageCount) --currentPage;
}

double Reader::getScrollBarPercent() const
{
    return (1.0*scrollBar->value() - scrollBar->minimum())/(scrollBar->maximum() - scrollBar->minimum());
}

bool Reader::event(QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        isMouseScrolling = true;
        newSize = size();
        if(resizeTimerId)
        {
            killTimer(resizeTimerId);
            resizeTimerId = 0;
        }
        resizeTimerId = startTimer(200);
    }
    return QWidget::event(event);
}

void Reader::timerEvent(QTimerEvent *te)
{
    if(te->timerId() == resizeTimerId)
    {
        scrollArea->resize(newSize);
        pageArea->resize(newSize.width() - 15, pageCount * pageAspectRatio * (newSize.width() - 15));

        for (int index = 0; index < pageCount; index++)
        {
            pages[index]->clear();
            isActualized[index] = false;
        }
        scrollBar->setValue(lastScrollBarValue * scrollBar->maximum());
        isMouseScrolling = false;
        startTimer(100);

        killTimer(te->timerId());
        resizeTimerId = 0;
    }
    else
    {
        scrollBar->valueChanged(0);
    }
}

void Reader::actualizeView(int page)
{
    QThread *imageLoadingThread = new QThread();
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
    //int oldPage = currentPage;
    updateCurrentPage();
    if (!isActualized[currentPage])
    {
        actualizeView(currentPage);
        isActualized[currentPage] = true;
    }
    if (currentPage > 0 && !isActualized[currentPage-1] && getScrollBarPercent() < lastScrollBarValue)
    {
        actualizeView(currentPage-1);
        isActualized[currentPage-1] = true;
    }
    if (currentPage < pageCount - 1 && !isActualized[currentPage+1] && getScrollBarPercent() > lastScrollBarValue)
    {
        actualizeView(currentPage+1);
        isActualized[currentPage+1] = true;
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
    if (currentPage > 0)
    {
        actualizeView(currentPage-1);
        isActualized[currentPage-1] = true;
    }
    actualizeView(currentPage);
    isActualized[currentPage] = true;
    if (currentPage < pageCount - 1)
    {
        actualizeView(currentPage+1);
        isActualized[currentPage+1] = true;
    }

    isMouseScrolling = false;
}

void Reader::handleImage(QImage image, int pagenum)
{
    pages[pagenum]->setPixmap(QPixmap::fromImage(image));
}

