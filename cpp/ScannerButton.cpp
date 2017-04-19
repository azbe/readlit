#include "src/ScannerButton.h"
#include "src/Constants.h"

#include <QDir>

ScannerButton::ScannerButton(QWidget *parent, QLineEdit *folderPaths) : QPushButton(parent)
{
    this->folderPaths = folderPaths;
	setText(UIConstants::SCANNER_BUTTON_DEFAULT_TEXT);
}

ScannerButton::~ScannerButton() {}

void ScannerButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QStringList pieces = folderPaths->text().split(",", QString::SkipEmptyParts);

        QStringList bookPaths;
        for (int index = 0; index < pieces.size(); index++)
            bookPaths.append(getBooksInFolder(pieces.value(index)));
        emit sendBookPaths(bookPaths);
    }
}

QStringList ScannerButton::getBooksInFolder(QString folderPath)
{
    QDir dir(folderPath);
    QStringList filePaths;

    dir.setNameFilters(QStringList("*.pdf"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList fileList = dir.entryList();
    for (int index = 0; index < fileList.size(); ++index)
        filePaths.append(QString("%1/%2").arg(folderPath).arg(fileList[index]));

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for (int index = 0; index < dirList.size(); ++index)
    {
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(index));
        QStringList newBooks = getBooksInFolder(newPath);
        for (int index1 = 0; index1  < newBooks.size(); index1++)
            filePaths.append(newBooks.value(index1));
    }

    return filePaths;
}
