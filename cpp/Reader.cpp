#include "src/Reader.h"
#include "src/Constants.h"

#include <QResizeEvent>
#include <QThread>

#include "src/ImageLoader.h"

Reader::Reader(QWidget *parent) : QWidget(parent)
{
    book = 0;
    scrollArea = 0;
    scrollBar = 0;
    pageArea = 0;
    pageAreaLayout = 0;
    pages = 0;
    isActualized = 0;
}

Reader::Reader(QWidget *parent, const QString& path, const int& startingPage) : QWidget(parent)
{
    book = Poppler::Document::load(path);
    if(book); //TO DO: erori

    Poppler::Page *page = book->page(0);
    pageAspectRatio = (ReaderConstants::SCAN_DEFAULT_VERTICAL_RES * (page->pageSizeF().height() / 72)) / (ReaderConstants::SCAN_DEFAULT_HORIZONTAL_RES * (page->pageSizeF().width() / 72));
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
    pageAreaLayout = new QVBoxLayout(pageArea);

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
    if(pages)
    {
        for (int index = 0; index < pageCount; index++)
            if (pages[index])
                delete pages[index];
        delete[] pages;
        delete[] isActualized;
    }
    if(pageAreaLayout) delete pageAreaLayout;
    if(pageArea) delete pageArea;
    if(scrollBar) delete scrollBar;
    if(scrollArea) delete scrollArea;
    if(book) delete book;
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
    int a[3] = {scrollBar->minimum(), scrollBar->value(), scrollBar->maximum()};
    currentPage = (scrollBar->value() - scrollBar->minimum())/(1.0 * scrollBar->maximum() - scrollBar->minimum()) * pageCount;
    if (currentPage == pageCount) --currentPage;
}

double Reader::getScrollBarPercent() const
{
    return (1.0*scrollBar->value() - scrollBar->minimum())/(scrollBar->maximum() - scrollBar->minimum());
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
    resizeTimerId = startTimer(200);
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
        scrollBarValueChanged();
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
    pages[pagenum]->setPixmap(QPixmap::fromImage(image));
}

