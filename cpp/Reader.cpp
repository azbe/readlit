#include <string>

#include <QVBoxLayout>
#include <QPixmap>

#include "src/Reader.h"
#include "src/Constants.h"

Reader::Reader(QWidget *parent, const QString& path, const int& firstPage) : QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout *layout = new QVBoxLayout(this);

    filePath = path;
    book = Poppler::Document::load(filePath);
    if (!book); //TO DO: erori
    firstPageIndex = firstPage;

    scrollArea = new QScrollArea(this);
    layout->addWidget(scrollArea);

    imageArea = new QFrame();
    imageArea->setContentsMargins(0,0,0,0);
    imageAreaLayout = new QVBoxLayout(imageArea);

    labels = new QLabel*[ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER];
    for (int index = firstPageIndex; index < firstPageIndex + ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER; index++)
    {
        labels[index - firstPageIndex] = new QLabel(imageArea);
        labels[index - firstPageIndex]->setScaledContents(true);
        labels[index - firstPageIndex]->setPixmap((QPixmap::fromImage(getPageImage(index))).scaled(1080, 1920, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageAreaLayout->addWidget(labels[index - firstPageIndex]);
    }
    scrollArea->setWidget(imageArea);
}

Reader::~Reader()
{
    if (book) delete book;
    if (scrollArea) delete scrollArea;
    if (labels)
    {
        for (int index = 0; index < ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER; index++)
            if (labels[index])
                delete labels[index];
        delete labels;
    }
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
