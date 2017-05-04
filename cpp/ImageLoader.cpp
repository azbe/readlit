#include "src/ImageLoader.h"
#include "src/Constants.h"

ImageLoader::ImageLoader(QObject *parent, Poppler::Page *page, int pagenum, int width, int height) : QObject(parent)
{
    this->page = page;
    this->pagenum = pagenum;
    this->width = width;
    this->height = height;
}

ImageLoader::~ImageLoader() {} //*page is deleted in process

void ImageLoader::process()
{
    QImage image = page->renderToImage(ReaderConstants::SCAN_DEFAULT_HORIZONTAL_RES, ReaderConstants::SCAN_DEFAULT_VERTICAL_RES).scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    delete page;
    if (image.isNull())
        qDebug() << "ImageLoader::process - Error rendering image";
    //Emiting null image is fine here
    emit result(image, pagenum);
    emit finished();
}
