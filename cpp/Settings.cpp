#include "src/Settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent)
{

   // QSizePolicy *sizePolicy;

   /* defaultPaths = new QGroupBox(this);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            sizePolicy.setHorizontalStretch(1);
            sizePolicy.setVerticalStretch(1);
            //sizePolicy.setHeightForWidth(defaultPaths->sizePolicy().hasHeightForWidth());
           // defaultPaths->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    defaultPaths->setSizePolicy(sizePolicy);*/
}

Settings::~Settings()
{
    delete save;
    delete defaults;
    delete defaultPaths;
    delete settingsPaths;
    delete layoutSettings;
}
