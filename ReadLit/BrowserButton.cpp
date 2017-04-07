#include "BrowserButton.h"
#include "Constants.h"

BrowserButton::BrowserButton(QWidget *parent) : QToolButton(parent) 
{
	setText(UIConstants::BROWSER_BUTTON_DEFAULT_TEXT);
}

BrowserButton::~BrowserButton() {}
