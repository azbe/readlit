# ReadLit

ReadLit is a small GUI desktop application made in Qt with C++ for opening, reading and storing a small databases of all pdfs from a given list of folders.

## Usage:

The **_Reader_** tab contains the personalized PDF Reader made using the Poppler library. The reader is initially blank, if no pdf has been loaded:
- upon loading a page (by double-clicking its name in the Local/Books tab), the reader becomes active, as do the find and dictionary modules
- the find is implemented using poppler function that returns a square in the page containing the searched text
- the dictionary is implemented using a python script (the dictionary script path can be changed from the settings tab, or the script can be modified; using python is not necessary, just redirect the script executor path to another binary file other than python3 i.e. perl)
- the reader uses multi-threading for scanning pages at 600dpi in real time with no lag (may take a long time on pdfs that have natively big page sizes)

The **_Local_** tab contains the actual information regarding the stored pdfs (moving a pdf from its stored location will cause errors):
- the "Books" subtab and the "Authors" one are very similar
- both show a couple of buttons, followed by a table containing information pertaining to a certain book/author from the database
- the button functions are intuitive, but it is worth mentioning that the sync button uses a python script (changeable, just like the dictionary one) to search google (goodreads, actually) for information regarding the current selected book (it is very important to first supply the correct pdf name, rather than the default name, which is the file path) or the current selected author, respectively (and again, it is very important to supply the correct author name)
- the Books tab shows a list of stored pdfs
- the Authors tab shows a list of stored authors, and for each selected author, a list of said author's books

The **_Settings_** tab contains some intuitive, graphical forms for changing mostly paths used by the application.
