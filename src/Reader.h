#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QEvent>
#include <poppler/qt5/poppler-qt5.h>

#include "src/VerticalScrollArea.h"

class Reader : public QWidget
{
    Q_OBJECT
    public:
    explicit Reader(QWidget *parent, const QString& path, const int& firstPage = 0);
    ~Reader();

    QImage getPageImage(const int& index) const;

    protected:
    bool event(QEvent *event);

    private:
    QString filePath;
    Poppler::Document *book;
    int firstPageIndex;

    VerticalScrollArea *scrollArea;
    QFrame *imageArea;
    QLayout *imageAreaLayout;
    QLabel **labels;
    QImage **images;
};

#endif // READER_H
