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
#include <QDebug>
#include <poppler-qt5.h>

class Reader : public QWidget
{
    Q_OBJECT

    private:
    void actualizeView(int page);
    QImage getPageImage(const int& index) const;
    double getScrollBarPercent() const;
    void updatePageCount();
    void updateCurrentPage();

    public:
    explicit Reader(QWidget *parent);
    bool isNull() const;
    explicit Reader(QWidget *parent, const QString& path);
    ~Reader();

    private:
    Poppler::Document *book;

    QScrollArea *scrollArea;
    QScrollBar *scrollBar;
    QFrame *pageArea;
    QVBoxLayout *pageAreaLayout;
    QLabel **pages;
    bool *isActualized;

    double pageAspectRatio;
    int pageCount;
    int currentPage;
    double lastScrollBarValue;
    bool isMouseScrolling;

    int resizeTimerId = 0;
    QSize newSize;

    void resizeEvent(QResizeEvent *event);
    void timerEvent(QTimerEvent *te);

    private slots:
    void scrollBarValueChanged();
    void scrollBarPressed();
    void scrollBarReleased();
    void handleImage(QImage image, int pagenum);
    void find(const QString& search);
};

#endif // READER_H

