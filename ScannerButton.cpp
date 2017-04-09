#include "ScannerButton.h"
#include "Constants.h"

ScannerButton::ScannerButton(const QString& text, QWidget *parent) : QPushButton(text, parent) {}

ScannerButton::ScannerButton(QWidget *parent) : QPushButton(parent)
{
	setText(UIConstants::SCANNER_BUTTON_DEFAULT_TEXT);
}

ScannerButton::~ScannerButton() {}
