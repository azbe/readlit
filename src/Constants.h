#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace ReaderConstants
{
    const int PRELOAD_PAGES_DEFAULT_NUMBER = 5;
    const int SCAN_DEFAULT_HORIZONTAL_RES = 300;
    const int SCAN_DEFAULT_VERTICAL_RES = 300;
}

namespace UIConstants
{
	//Values
	const int LOCAL_BOOKS_LIST_HORIZONTAL_STRETCH = 2;
	const int LOCAL_BOOKS_DETAILS_WIDGET_HORIZONTAL_STRETCH = 3;
	const int LOCAL_AUTHORS_LIST_HORIZONTAL_STRETCH = 1;
	const int LOCAL_AUTHORS_DETAILS_WIDGET_HORIZONTAL_STRETCH = 2;

	const int DATA_BUTTON_DEFAULT_MAX_SIZE = 75;

	const int MAINWINDOW_DEFAULT_WIDTH = 800;
	const int MAINWINDOW_DEFAULT_HEIGHT = 600;

	//Strings
	const QString BROWSER_BUTTON_DEFAULT_TEXT = "...";
	const QString SCANNER_BUTTON_DEFAULT_TEXT = "Scan 'n Save";
}

#endif //CONSTANTS_h
