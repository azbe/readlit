#ifndef SETTINGS
#define SETTINGS
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include "src/DataButton.h"
#include "src/Constants.h"
class Settings : public QWidget
{
    Q_OBJECT

    public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
private:
    DataButton *save;
    DataButton *defaults;
    QGroupBox *defaultPaths;
    QGroupBox *settingsPaths;
    QGridLayout *layoutSettings;
};

#endif // SETTINGS

