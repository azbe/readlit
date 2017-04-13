#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <poppler/qt5/poppler-qt5.h>

class Reader : public QWidget
{
    Q_OBJECT
    public:
    explicit Reader(QWidget *parent, const QString& path, const int& firstPage = 0);
    ~Reader();

    QImage getPageImage(const int& index) const;

    private:
    QString filePath;
    Poppler::Document *book;
    int firstPageIndex;

    QScrollArea *scrollArea;
    QFrame *imageArea;
    QLayout *imageAreaLayout;
    QLabel **labels;
};

#endif // READER_H
