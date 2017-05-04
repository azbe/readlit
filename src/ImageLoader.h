#ifndef IMAGELOADER
#define IMAGELOADER

#include <QObject>
#include <QThread>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <poppler-qt5.h>

class ImageLoader : public QObject
{
    Q_OBJECT

    public:
    ImageLoader(QObject *parent, Poppler::Page *page, int pagenum, int width, int height);
    ~ImageLoader();

    private:
    int pagenum;
    int width;
    int height;
    Poppler::Page *page;

    signals:
    void finished();
    void result(QImage image, int pagenum);

    public slots:
    void process();
};

#endif // IMAGELOADER

