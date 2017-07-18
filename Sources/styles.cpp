#include "styles.h"


////////////////////////общее///////////////////////////

void setWindowTopButtonsStyle (QString windowButtonsStyle [], const QString style)
{
    if (style == "Red")
    {
        windowButtonsStyle[0] = "#min_button{"
                                "border-image: url(:/Images/LightMin.png);"
                                "border: none;"
                                "background:none;}"
                                "#min_button:hover{"
                                "background-color:rgb(150, 0, 65);}";

        windowButtonsStyle[1] = "#full_size_button{"
                                "border-image: url(:/Images/LightFull_size.png);"
                                "border: none;"
                                "background:none;}"
                                "#full_size_button:hover{"
                                "background-color:rgb(150, 0, 65);}";
    }
}

void setExitButtonStyle (QString exitbuttonStyle [], const QString style)
{
    if (style == "Red")
    {
        exitbuttonStyle[0] = "QPushButton{"
                             "border-image: url(:/Images/LightExit.png);"
                             "border: none;"
                             "background:none;}"
                             "QPushButton:hover {"
                             "background-color:rgb(203, 0, 88);}";
    }
}

void setBackgroundWindowColor(QString windowButtonsStyle [], const QString style)
{
    if (style == "Red")
    {
        windowButtonsStyle[0] = "#MainWidget "
                                "{background-color:rgb(150, 0, 60);}"

                                "QScrollBar:vertical {"
                                "border: none;"
                                "background: rgb(150, 0, 60);"
                                "width: 10px;"
                                "margin: 0px;}"
                                "QScrollBar::handle:vertical {"
                                "border: none;"
                                "background: white;"
                                "min-height: 20px;}"
                                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                "height: 0px;"
                                "background: none;}"
                                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                "background: none;}";

        windowButtonsStyle[1] = "QDialog {"
                                "background-color:rgb(150, 0, 60);"
                                "color:white;}";
    }
}

void setTopBarBackgroundColor(QString TopBarStyle [], const QString style)
{
    if (style == "Red")
    {
        TopBarStyle[0] = "#TopBarWidget{"
                         "border:none;"
                         "background-color:rgb(170, 0, 80);}";
    }
}


////////////////////////логин///////////////////////////////
void setLoginWindowStyle (QString windowButtonsStyle [], const QString style)
{
    if (style == "Red")
    {
        windowButtonsStyle[0] = "#login{"
                                "background-color:rgb(151, 151, 227);"
                                "border: none;}"
                                "#login:hover{"
                                "background-color:rgb(130, 130, 195);}";

        windowButtonsStyle[1] = "QLineEdit{"
                                "background-color:rgb(130, 0, 55);"
                                "color: white;}";

        windowButtonsStyle[2] = "#Recovery{"
                                "color: white;"
                                "margin: 0;"
                                "text-align:right;"
                                "border:none}"
                                "#Recovery:hover{"
                                "color: rgb(151, 151, 227);}";

        windowButtonsStyle[3] = "#Registration{"
                                "text-align:left;"
                                "border:none;"
                                "margin:0;"
                                "color: white;}"
                                "#Registration:hover{"
                                "color: rgb(151, 151, 227);}";

        windowButtonsStyle[4] = "#Remember{color: white;}"
                                "#Remember:hover{color: rgb(151, 151, 227);}"
                                "#Remember::indicator:off{image: url(:/Images/LightCheck_no.png);}"
                                "#Remember::indicator:on{image: url(:/Images/LightCheck_ok.png);}";

    }
}


///////////////////////////библиотека///////////////////////////
void setMenusButtonsStyle (QString menuButtonsStyle [], const QString style)
{
    if (style == "Red")
    {
        menuButtonsStyle[0] =  " #Library "
                               " {background-color: rgb(162, 0, 70); "
                               " background-image: url(:/Images/LightLibrary_img.png);"
                               " border:none;} "
                               " #Library:hover "
                               " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[1] =  " #Settings "
                               " {background-color: rgb(162, 0, 70); "
                               " background-image: url(:/Images/LightSettings_img.png);"
                               " border:none;} "
                               " #Settings:hover "
                               " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[2] =  " #Synchronization "
                               " {background-color: rgb(162, 0, 70); "
                               " background-image: url(:/Images/LightSynchronization_img.png);"
                               " border:none;} "
                               " #Synchronization:hover "
                               " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[3] = " #Logout "
                              " {background-color: rgb(162, 0, 70); "
                              " background-image: url(:/Images/LightLogout_img.png);"
                              " border:none;} "
                              " #Logout:hover "
                              " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[4] = " #Library "
                              " {background-color: rgb(150, 0, 60); "
                              " background-image: url(:/Images/LightLibrary_img.png);"
                              " border:none;} "
                              " #Library:hover "
                              " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[5] = " #Settings "
                              " {background-color: rgb(150, 0, 60); "
                              " background-image: url(:/Images/LightSettings_img.png);"
                              " border:none;} "
                              " #Settings:hover "
                              " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[6] = " #Synchronization "
                              " {background-color: rgb(150, 0, 60); "
                              " background-image: url(:/Images/LightSynchronization_img.png);"
                              " border:none;} "
                              " #Synchronization:hover "
                              " { background-color:rgb(147, 0, 60); } ";

        menuButtonsStyle[7] = " #Logout "
                              " {background-color: rgb(150, 0, 60); "
                              " background-image: url(:/Images/LightLogout_img.png);"
                              " border:none;} "
                              " #Logout:hover "
                              " { background-color:rgb(147, 0, 60); } ";


        menuButtonsStyle[8] = "QWidget{background-color: rgb(162, 0, 70); border:none; }";
    }
}

void setTabButtonsStyle (QString tabButtonsStyle [], const QString style)
{
    if (style == "Red")
    {
        tabButtonsStyle[0] = "QPushButton "
                             "{background-color: rgb(162, 0, 70);"
                             "border:none;"
                             "color:white;}"
                             "QPushButton:hover"
                             "{background-color:rgb(147, 0, 60);}";

        tabButtonsStyle[1] = "QPushButton "
                             "{background-color: rgb(150, 0, 60);"
                             "border:none;"
                             "color:white;}"
                             "QPushButton:hover"
                             "{background-color:rgb(147, 0, 60);}";

        tabButtonsStyle[2] = "QPushButton "
                             "{background-color: rgb(162, 0, 70);"
                             "border:none;"
                             "color:white;"
                             "text-align:right;}"
                             "QPushButton:hover"
                             "{background-color:rgb(147, 0, 60);}";

        tabButtonsStyle[3] = "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable{"
                             "border:none;"
                             "background-color: rgb(162, 0, 70);"
                             "color:white;}"
                             "QComboBox::drop-down{"
                             "max-width:0px;"
                             "border:none;}"
                             "QComboBox:editable:hover, QComboBox:!editable:hover, QComboBox QAbstractItemView::item:selected{"
                             "background-color: rgb(150, 0, 60);}"
                             "QComboBox QAbstractItemView, QComboBox QAbstractItemView::item{"
                             "background-color: rgb(162, 0, 70);"
                             "outline: 0px;"
                             "border:none;"
                             "color:white;"
                             "min-height: 35px;}";

        tabButtonsStyle[4] = "QPushButton"
                             "{background-color: rgb(162, 0, 70);"
                             "border:none;"
                             "color:white;}"
                             "QPushButton:hover"
                             "{background-color:rgb(147, 0, 60);}"
                             "QPushButton:checked"
                             "{background-color:rgb(151, 151, 227);}"
                             "QPushButton:checked:hover"
                             "{background-color:rgb(130, 130, 195);}";

        tabButtonsStyle[5] = "#ShowButton"
                             "{background-color:rgb(130, 0, 45);"
                             "background-repeat: no-repeat;"
                             "background-position: center center;"
                             "background-image: url(:/Images/LightArrowVertClose.png);"
                             "border: none;}"

                             "#ShowButton:checked"
                             "{background-image: url(:/Images/LightArrowVertOpen.png);"
                             "}"

                             "#ShowButton:hover, #ShowButton:checked:hover"
                             "{background-color:rgb(120, 0, 45);}";

        tabButtonsStyle[6] = "#_SortDirection"
                          "{background-color: rgb(162, 0, 70);"
                          "background-image: url(:/Images/LightSortArrowFalse.png);"
                          "border:none;}"
                          "#_SortDirection:hover"
                          "{background-color:rgb(147, 0, 60);}"
                          "#_SortDirection:checked"
                          "{background-image: url(:/Images/LightSortArrowTrue.png);}";
    }
}


void setLastBookWidgetStyle(QString styles [], const QString style)
{
    if (style == "Red")
    {
        styles[0] = "#LastBookLayout"
                        "{background-color: rgb(140, 0, 50);"
                        "border-right: 1px solid rgb(130, 0, 45);}"

                        "QLabel"
                        "{color:white;}";

        styles[1] = "#ReadButton"
                        "{background-color:rgb(151, 151, 227);"
                        "border: none;"
                        "color:white;}"
                        "#ReadButton:hover"
                        "{background-color:rgb(130, 130, 195);}";

        styles[2] = "#PageButton"
                        "{background-color:rgb(152, 0, 60);"
                        "border: none;"
                        "color:white;}"
                        "#PageButton:hover"
                        "{background-color:rgb(147, 0, 60);}";
    }
}


void setLibraryLayoutButtons (QString buttonsStyle [], const QString style)
{
    if (style == "Red")
    {
        buttonsStyle[0] =   "#_ChangeViewMode"
                            "{background-color: rgb(162, 0, 70);"
                            "background-image: url(:/Images/LightBarView.png);"
                            "border:none;}"
                            "#_ChangeViewMode:hover, #_ChangeViewMode:checked:hover"
                            "{background-color: rgb(147, 0, 60);}"
                            "#_ChangeViewMode:checked"
                            "{background-image: url(:/Images/LightListView.png);}";

        buttonsStyle[1] =   "#_Upscale "
                            "{background-color: rgb(162, 0, 70);"
                            "background-image: url(:/Images/LightUpscale.png);"
                            "border:none;}"
                            "#_Upscale:hover"
                            "{background-color:rgb(147, 0, 60);}";

        buttonsStyle[2] =   "#_Downscale"
                            "{background-color: rgb(162, 0, 70);"
                            "background-image: url(:/Images/LightDownscale.png);"
                            "border:none;}"
                            "#_Downscale:hover"
                            "{background-color:rgb(147, 0, 60);}";
    }
}

void setBookOrFolderStyle (QString buttonStyle [], const QString style)
{
    if (style == "Red")
    {
        buttonStyle[0] = " QPushButton "
                         " {background-color: rgb(162, 0, 70); "
                         " border:none;"
                         " color: white;}"
                         " QPushButton:hover "
                         " { background-color:rgb(147, 0, 60); } ";
    }
}


void setLibraryStyle (QString ListViewStyle[], const QString style)
{
    if (style == "Red")
    {
        ListViewStyle[0] = " QListView"
                           " {background-color:rgb(150, 0, 60);"
                           " border:none;"
                           " color: white;}"

                           " QListView::item"
                           " {outline: 0px;"
                           " border: none;}"

                           " QListView::item:hover"
                           "{background-color:rgb(100,0,30);}"

                           " QListView::item:selected"
                           "{background-color:rgb(151,151,227);}"

                           " QListView::item:selected:hover"
                           "{background-color:rgb(130,130,195);}";
    }
}


///////////////////////////диалог подтверждения///////////////////////////
void setAnswerDialogStyle (QString windowStyle [], const QString style)
{
    if (style == "Red")
    {
        windowStyle[0] =    "QWidget"
                            "{background-color:rgb(130, 0, 55);"
                            "color:white;}";

        windowStyle[1] =    "QPushButton"
                            "{background-color:rgb(160, 0, 0);"
                            "border: none;}"
                            "QPushButton:hover"
                            "{background-color:rgb(190, 0, 0);"
                            "border: none;}";

        windowStyle[2] =    "QPushButton"
                            "{background-color: rgb(60, 90, 130);"
                            "border: none;}"
                            "QPushButton:hover"
                            "{background-color:rgb(80, 110, 150);"
                            "border: none;}";
    }
}

///////////////////////////сраница книги///////////////////////////
void setBookPageStyle(QString BookPageStyle[], const QString style)
{
    if (style == "Red")
    {
        BookPageStyle[0] =  "#BookPage"
                            "{background-color:rgb(162, 0, 70);"
                            "border: 1px solid;"
                            "border-color:black;}";

        BookPageStyle[1] =  "#startReading"
                            "{background-color:rgb(151, 151, 227);"
                            "border: none;"
                            "color:white;}"
                            "#startReading:hover"
                            "{background-color:rgb(130, 130, 195);}";

        BookPageStyle[2] =  "QLabel"
                            "{color:white;}";

        BookPageStyle[3] =  "QTextEdit"
                            "{background-color:rgb(162, 0, 70);"
                            "border:none;"
                            "color:white;}";

        BookPageStyle[4] =  "#deleteBook"
                            "{background-color: rgb(162, 0, 70);"
                            "border: none;}"
                            "#deleteBook:hover"
                            "{background-color:rgb(210, 68, 68);}";

        BookPageStyle[5] =  "#leftLine, #leftLine_2"
                            "{background-color: rgb(157, 0, 60);"
                            "color: rgb(157, 0, 60);}";

        BookPageStyle[6] = "#NextIllustration{"
                           "background-color: rgb(151, 151, 227);"
                           "border:none;"
                           "background-repeat: no-repeat;"
                           "background-position: center center;"
                           "background-image:url(:/Images/LightArrowVertOpen.png);}";

        BookPageStyle[7] = "#PrevIllustration{"
                           "background-color: rgb(151, 151, 227);"
                           "border:none;"
                           "background-repeat: no-repeat;"
                           "background-position: center center;"
                           "background-image:url(:/Images/LightArrowVertClose.png);}";

    }
}


///////////////////////////окно поиска///////////////////////////
void setSearchWindowStyle(QString SearchStyle[], const QString style)
{
    if (style == "Red")
    {
        SearchStyle[0] =    "QPushButton "
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "color:white;}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        SearchStyle[1] =    "QLineEdit{"
                            "background-color:rgb(130, 0, 55);"
                            "color: white;"
                            "border:none;}";

        SearchStyle[2] =    "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable{"
                            "border:none;"
                            "background-color: rgb(130, 0, 55);"
                            "color:white;}"
                            "QComboBox::drop-down{"
                            "max-width:0px;"
                            "border:none;}"
                            "QComboBox:editable:hover, QComboBox:!editable:hover, QComboBox QAbstractItemView::item:selected{"
                            "background-color: rgb(120, 0, 45);}"
                            "QComboBox QAbstractItemView, QComboBox QAbstractItemView::item{"
                            "background-color: rgb(130, 0, 55);"
                            "outline: 0px;"
                            "border:none;"
                            "color:white;"
                            "min-height: 35px;}";

        SearchStyle[3] = "QLabel"
                         "{color:white;"
                         "border:none;}";
    }
}


///////////////////////////виджет настроек///////////////////////////
void setProgramLayoutStyle(QString LayoutStyle[], const QString style)
{
    if (style == "Red")
    {
        LayoutStyle[0] =   "QWidget"
                                 "{background-color:rgb(150, 0, 60);"
                                 "color:white;}"

                                 "QLineEdit{"
                                 "border:none;"
                                 "background-color: rgb(130, 0, 55);}"


                                 "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable{"
                                 "border:none;"
                                 "background-color: rgb(130, 0, 55);"
                                 "color:white;}"
                                 "QComboBox::drop-down{"
                                 "border:none;}"
                                 "QComboBox::down-arrow, QComboBox::up-arrow{"
                                 "image: url(:/Images/LightArrow.png);}"
                                 "QComboBox:editable:hover, QComboBox:!editable:hover, QComboBox QAbstractItemView::item:selected{"
                                 "background-color: rgb(120, 0, 45);}"
                                 "QComboBox QAbstractItemView, QComboBox QAbstractItemView::item{"
                                 "background-color: rgb(130, 0, 55);"
                                 "outline: 0px;"
                                 "border:none;"
                                 "color:white;"
                                 "min-height: 35px;}"

                                 "QPushButton"
                                 "{border:none;"
                                 "color:white;"
                                 "background-color: rgb(162, 0, 70);}"
                                 "QPushButton:hover"
                                 "{background-color:rgb(147, 0, 60);}";

        LayoutStyle[1] =    "QPushButton"
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "color:white;}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}"
                            "QPushButton:checked"
                            "{background-color:rgb(151, 151, 227);}"
                            "QPushButton:checked:hover"
                            "{background-color:rgb(130, 130, 195);}";
    }
}

void setReaderLayoutStyle(QString LayoutStyle[], const QString style)
{
    if (style == "Red")
    {
        LayoutStyle[0] =    "QWidget"
                            "{background-color:rgb(150, 0, 60);"
                            "color:white;}"

                            "QLineEdit{"
                            "border:none;"
                            "background-color: rgb(130, 0, 55);}"


                            "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable{"
                            "border:none;"
                            "background-color: rgb(130, 0, 55);"
                            "color:white;}"
                            "QComboBox::drop-down{"
                            "border:none;}"
                            "QComboBox::down-arrow, QComboBox::up-arrow{"
                            "image: url(:/Images/LightArrow.png);}"
                            "QComboBox:editable:hover, QComboBox:!editable:hover, QComboBox QAbstractItemView::item:selected{"
                            "background-color: rgb(120, 0, 45);}"
                            "QComboBox QAbstractItemView, QComboBox QAbstractItemView::item{"
                            "background-color: rgb(130, 0, 55);"
                            "outline: 0px;"
                            "border:none;"
                            "color:white;"
                            "min-height: 35px;}"

                            "QPushButton"
                            "{border:none;"
                            "color:white;"
                            "background-color: rgb(162, 0, 70);}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        LayoutStyle[1] =    "#YepButton"
                            "{border:none;"
                            "color:white;"
                            "background-image: url(:Images/LightNewReadProfile.png);"
                            "background-color: rgb(150, 0, 60);}"
                            "#YepButton:hover"
                            "{background-color:rgb(137, 0, 60);}";

        LayoutStyle[2] = "#YepButton"
                           "{border:none;"
                           "color:white;"
                           "background-image: url(:Images/LightYepButton.png);"
                           "background-color: rgb(150, 0, 60);}"
                           "#YepButton:hover"
                           "{background-color:rgb(137, 0, 60);}";

        LayoutStyle[3] =    "#NopeButton"
                            "{border:none;"
                            "color:white;"
                            "background-color: rgb(150, 0, 60);"
                            "background-image: url(:Images/LightDeleteButton.png);}"
                            "#NopeButton:hover"
                            "{background-color:rgb(200, 0, 0);}";

        LayoutStyle[4] =    "#NopeButton"
                            "{border:none;"
                            "color:white;"
                            "background-color: rgb(150, 0, 60);"
                            "background-image: url(:Images/LightNopeButton.png);}"
                            "#NopeButton:hover"
                            "{background-color:rgb(137, 0, 60);}";
    }
}

void setProfileLayoutStyle(QString LayoutStyle[], const QString style)
{
    if (style == "Red")
    {
        LayoutStyle[0] =    "QWidget"
                            "{background-color:rgb(150, 0, 60);"
                            "border:none;"
                            "color:white;}"

                            "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable{"
                            "border:none;"
                            "background-color: rgb(130, 0, 55);"
                            "color:white;}"
                            "QComboBox::drop-down{"
                            "border:none;}"
                            "QComboBox::down-arrow, QComboBox::up-arrow{"
                            "image: url(:/Images/LightArrow.png);}"
                            "QComboBox:editable:hover, QComboBox:!editable:hover, QComboBox QAbstractItemView::item:selected{"
                            "background-color: rgb(120, 0, 45);}"
                            "QComboBox QAbstractItemView, QComboBox QAbstractItemView::item{"
                            "background-color: rgb(130, 0, 55);"
                            "outline: 0px;"
                            "border:none;"
                            "color:white;"
                            "min-height: 35px;}";
    }
}

void setSavebuttonStyle(QString SavebuttonStyle[], const QString style)
{
    if (style == "Red")
    {
        SavebuttonStyle[0] =    "#SaveButton"
                                "{background-color:rgb(151, 151, 227);"
                                "border: none;}"
                                "#SaveButton:hover"
                                "{background-color:rgb(130, 130, 195);}";

        SavebuttonStyle[1] =    "#SaveButton"
                                "{background-color:rgb(43, 138, 0);"
                                "border: none;}"
                                "#SaveButton:hover"
                                "{background-color:rgb(38, 121, 0);}";
    }
}

///////////////////////////окно чтения///////////////////////////
void setReaderWindowStyle(QString WindowStyle[], const QString style)
{
    if (style == "Red")
    {
        WindowStyle[0] = "QPushButton"
                         "{background-color:rgb(151, 151, 227);"
                         "color:white;"
                         "border: none;}"
                         "QPushButton:hover"
                         "{background-color:rgb(130, 130, 195);}";

        WindowStyle[1] = "QLabel"
                         "{color:white;}";

        WindowStyle[2] = "QPushButton{"
                         "background-color: rgb(170, 0, 80);"
                         "border:none;"
                         "background-image: url(:/Images/LightReadProfileSwap.png);}"
                         "QPushButton:hover{"
                         "background-color:rgb(147, 0, 60);}";

        WindowStyle[3] = "QListView{"
                         "border:none;"
                         "outline: 0px;"
                         "background-color: rgb(162, 0, 70);"
                         "color:white;}"
                         "QListView::item{"
                         "min-height:30px;}"
                         "QListView::item:hover{"
                         "background-color: rgb(120, 0, 45);}"
                         "QListView::item:selected{"
                         "background-color:rgb(151, 151, 227);"
                         "border:none;}";
    }
}

void setReaderWindowMenuButtons(QString ButtonsStyle[], const QString style)
{
    if (style == "Red")
    {
        ButtonsStyle[0] =   "QPushButton{"
                            "background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "background-image: url(:/Images/LightMenuContents.png);}"
                            "QPushButton:hover{"
                            "background-color:rgb(147, 0, 60);}";

        ButtonsStyle[1] =   "QPushButton{"
                            "background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "background-image: url(:/Images/LightMenuSearch.png);}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        ButtonsStyle[2] =   "QPushButton"
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "background-image: url(:/Images/LightMenuSettings.png);}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        ButtonsStyle[3] =   "QPushButton"
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "background-image: url(:/Images/LightMenuSynchronization.png);}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        ButtonsStyle[4] =   "QPushButton"
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "background-image: url(:/Images/LightMenuLibrary.png);}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";

        ButtonsStyle[5] = "#MainWidget {background-color: rgb(162, 0, 70);}";
    }
}

void setReaderTableOfContents(QString WindowStyle[], const QString style)
{
    if (style == "Red")
    {
        WindowStyle[0] =    "QTreeWidget{"
                            "border:none;"
                            "outline: 0px;"
                            "background-color: rgb(162, 0, 70);"
                            "color:white;}"
                            "QTreeWidget::item{"
                            "min-height:30px;}"

                            "QTreeWidget::item:hover{"
                            "background-color: rgb(120, 0, 45);}"

                            "QTreeWidget::item:selected{"
                            "background-color:rgb(151, 151, 227);"
                            "border:none;}"

                            "QTreeWidget::branch:has-children:closed{"
                            "background-image: url(:/Images/LightArrowVertOpen.png);"
                            "background-repeat: no-repeat;"
                            "background-position: center center;}"

                            "QTreeWidget::branch:has-children:open{"
                            "background-repeat: no-repeat;"
                            "background-position: center center;"
                            "background-image: url(:/Images/LightArrowOpen.png)}"

                            "QScrollBar:vertical {"
                            "border: none;"
                            "background: rgb(150, 0, 60);"
                            "width: 10px;"
                            "margin: 0px;}"
                            "QScrollBar::handle:vertical {"
                            "border: none;"
                            "background: white;"
                            "min-height: 20px;}"
                            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                            "height: 0px;}"
                            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                            "background: none;}";

        WindowStyle[1] =    "QPushButton "
                            "{background-color: rgb(162, 0, 70);"
                            "border:none;"
                            "color:white;}"
                            "QPushButton:hover"
                            "{background-color:rgb(147, 0, 60);}";
    }
}
