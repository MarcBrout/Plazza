//
// Created by brout_m on 13/04/17.
//

#ifndef CPP_PLAZZA_GUI_HPP
# define CPP_PLAZZA_GUI_HPP
# include <QApplication>
# include <QWidget>
# include <QPushButton>
# include <QTextEdit>
# include <QCheckBox>
# include <QLabel>
# include <QFileDialog>
# include <QTimer>
# include <SocketInternet.hpp>
# include <ProcessManager.hpp>
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
        QTimer              m_timer;
        plazza::com::SocketInternet     m_sock;
        plazza::ProcessManager          m_process_manager;
        std::vector<std::string>        m_resultQ;
        int                             m_wait;

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
        void updateResults();
    };
}

#endif //CPP_PLAZZA_GUI_HPP
