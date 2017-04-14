//
// Created by brout_m on 13/04/17.
//

#ifndef CPP_PLAZZA_GUI_HPP
# define CPP_PLAZZA_GUI_HPP

# include "QtWidgets/QApplication"
# include "QtWidgets/QWidget"
# include "QtWidgets/QPushButton"
# include "QtWidgets/QTextEdit"
# include "QtWidgets/QCheckBox"
# include "QtWidgets/QLabel"
# include "QtWidgets/QFileDialog"
# include "CommandGenerator.hpp"

namespace gui
{
    class GUI : public QWidget
    {

    public:
        GUI(int p_width = 800, int p_height = 600, QWidget *p_parent = nullptr);

    private:
        int                 m_width;
        int                 m_height;
        QPushButton         m_searchButton;
        QPushButton         m_clearButton;
        QPushButton         m_quitButton;
        QTextEdit           m_results;
        QLabel              m_searchLabel;
        QCheckBox           m_emailAddress;
        QCheckBox           m_phoneNumber;
        QCheckBox           m_ipAddress;
        QLabel              m_fileLabel;
        QTextEdit           m_files;
        CommandGenerator    m_cmdGen;
        QPushButton         m_getFilesButton;
        QPushButton         m_clearFilesButton;

    private:
        void searchClicked();
        void clearClicked();
        void checkBoxesClicked();
        void initializePositions();
        void initializeStyle();
        void connectGui();
        void searchFieldUpdated();
        void openFiles();
        void clearOpenedFilesList();
    };
}

#endif //CPP_PLAZZA_GUI_HPP
