#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QImage>
#include <QEvent>
#include <QLabel>
#include <QScrollBar>
#include <QTimer>
#include <poppler-qt5.h>

class Reader : public QWidget
{
    Q_OBJECT

    private:
    void actualizeView(int page);
    QImage getPageImage(const int& index) const;
    void updatePageCount();
    void updateCurrentPage();

    public:
    explicit Reader(QWidget *parent, const QString& path, const int& startingPage = 0);
    ~Reader();

    void changeBook(const QString& newPath);

    private:
    Poppler::Document *book;

    QScrollArea *scrollArea;
    QScrollBar *scrollBar;
    QFrame *pageArea;
    QLabel **pages;
    bool *isActualized;

    double pageAspectRatio;
    int pageCount;
    int currentPage;
    int lastScrollBarValue;
    bool isMouseScrolling;

    int resizeTimerId = 0;
    QSize newSize;

    bool event(QEvent *event);
    void timerEvent(QTimerEvent *te);

    private slots:
    void scrollBarValueChanged(int value);
    void scrollBarPressed();
    void scrollBarReleased();
    void handleImage(QImage image, int pagenum);
};

#endif // READER_H

