#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace ReaderConstants
{
    const int PRELOAD_DEFAULT_NUMBER_PAGES = 3;
    const int SCAN_DEFAULT_HORIZONTAL_RES = 600;
    const int SCAN_DEFAULT_VERTICAL_RES = 600;
    const int RESIZE_DEFAULT_TIMER = 200;
}

namespace UIConstants
{
	//Values
	const int LOCAL_BOOKS_LIST_HORIZONTAL_STRETCH = 2;
    const int LOCAL_BOOKS_DETAILS_WIDGET_HORIZONTAL_STRETCH = 1;
	const int LOCAL_AUTHORS_LIST_HORIZONTAL_STRETCH = 1;
    const int LOCAL_AUTHORS_DETAILS_WIDGET_HORIZONTAL_STRETCH = 1;

	const int DATA_BUTTON_DEFAULT_MAX_SIZE = 75;

	const int MAINWINDOW_DEFAULT_WIDTH = 800;
	const int MAINWINDOW_DEFAULT_HEIGHT = 600;

	//Strings
	const QString BROWSER_BUTTON_DEFAULT_TEXT = "...";
	const QString SCANNER_BUTTON_DEFAULT_TEXT = "Scan 'n Save";
}

namespace SettingsConstants
{

    const QString DATABASE_DEFAULT_PATH = "database.json";
    const QString SCANNER_DEFAULT_PATH ="scanner.txt";
    const QString TRANSLATOR_DEFAULT_PATH="translator.py";
    const QString DICTIONARY_DEFAULT_PATH="dictionary.py";
    const QString BOOK_SYNC_DEFAULT_PATH="sync_book.py";
    const QString AUTHOR_SYNC_DEFAULT_PATH="sync_author.py";
    const QString PYTHON2_DEFAULT_PATH="python2";
}

#endif //CONSTANTS_h
