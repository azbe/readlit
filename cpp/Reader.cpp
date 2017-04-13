#include <string>

#include <QVBoxLayout>
#include <QPixmap>

#include "src/Reader.h"
#include "src/Constants.h"

Reader::Reader(QWidget *parent, const QString& path, const int& firstPage) : QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);

    filePath = path;
    book = Poppler::Document::load(filePath);
    if (!book); //TO DO: erori
    firstPageIndex = firstPage;

    scrollArea = new VerticalScrollArea(this);
    layout->addWidget(scrollArea);

    imageArea = new QFrame();
    //imageArea->setStyleSheet("border: 3px solid blue");
    imageArea->setContentsMargins(0,0,0,0);
    imageAreaLayout = new QVBoxLayout(imageArea);

    labels = new QLabel*[ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER];
    images = new QImage*[ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER];
    for (int index = firstPageIndex; index < firstPageIndex + ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER; index++)
    {
        labels[index - firstPageIndex] = new QLabel(imageArea);
        images[index - firstPageIndex] = new QImage(getPageImage(index));
        labels[index - firstPageIndex]->setPixmap((QPixmap::fromImage(*images[index - firstPageIndex])));
        //labels[index - firstPageIndex]->setStyleSheet("border: 1px solid red");
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
    if (images)
    {
        for (int index = 0; index < ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER; index++)
            if (images[index])
                delete images[index];
        delete images;
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

bool Reader::event(QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        QSize newSize = this->size();
        for (int index = 0; index < ReaderConstants::PRELOAD_PAGES_DEFAULT_NUMBER; index++)
            labels[index]->setPixmap(QPixmap::fromImage(*images[index]).scaledToWidth(0.9 * newSize.width(), Qt::SmoothTransformation));
            //labels[index]->setPixmap(QPixmap::fromImage(*images[index]).scaled(newSize.width(), newSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    return QWidget::event(event);
}

