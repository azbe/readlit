#include "src/BrowserButton.h"

BrowserButton::BrowserButton(QWidget *parent, const BrowserButtonType& type) : QToolButton(parent)
{
	setText(UIConstants::BROWSER_BUTTON_DEFAULT_TEXT);
    this->type = type;
}

BrowserButton::~BrowserButton() {}

void BrowserButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QStringList fileNames;
        switch (type)
        {
            case ANY:
            {
                fileNames = QFileDialog::getOpenFileNames(0, QString(), ".", "Any (*)");
                break;
            }
            case DIR:
            {
                fileNames.append(QFileDialog::getExistingDirectory());
                break;
            }
            case PYTHON:
            {
                fileNames = QFileDialog::getOpenFileNames(0, QString(), ".", "Python Files (*.py)");
                break;
            }
            case JSON:
            {
                fileNames.append(QFileDialog::getOpenFileName(0, QString(), ".", "JSON files (*.json)"));
                break;
            }
        }

        emit sendPaths(fileNames);
    }
}
