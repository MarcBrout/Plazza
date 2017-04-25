//
// Created by brout_m on 13/04/17.
//

#include <AstParse.hpp>
#include <GraphReader.hpp>
#include <wait.h>
#include "GUI.hpp"

gui::GUI::GUI(int p_width, int p_height, QWidget *p_parent) :
        QWidget(p_parent),
        m_width(p_width),
        m_height(p_height),
        m_searchButton("Search", this),
        m_clearButton("Clear", this),
        m_quitButton("Quit", this),
        m_results(this),
        m_searchLabel("Searching for :", this),
        m_emailAddress("emails", this),
        m_phoneNumber("phone numbers", this),
        m_ipAddress("ip addresses", this),
        m_fileLabel("Files to search : ", this),
        m_files(this),
        m_cmdGen({"EMAIL_ADDRESS", "PHONE_NUMBER", "IP_ADDRESS"}),
        m_getFilesButton("Open Files", this),
        m_clearFilesButton("Clear", this),
        m_timer(this),
        m_sock(),
        m_process_manager(&m_sock),
        m_resultQ(),
        m_wait(0)

{
    initializePositions();
    initializeStyle();
    connectGui();
}

void gui::GUI::searchClicked()
{
    std::string l_str = m_files.toPlainText().toUtf8().toStdString();

    if (m_emailAddress.isChecked())
        m_cmdGen.feed(l_str, "EMAIL_ADDRESS");
    if (m_ipAddress.isChecked())
        m_cmdGen.feed(l_str, "IP_ADDRESS");
    if (m_phoneNumber.isChecked())
        m_cmdGen.feed(l_str, "PHONE_NUMBER");

    plazza::AstParse    l_parser;
    plazza::GraphReader l_graph_reader;
    std::vector<std::pair<std::string, plazza::Information>> l_orders;
    std::string l_cmd = m_cmdGen.getCmd();

    l_parser.feedCommand(l_cmd);
    l_graph_reader.readGraph(l_parser.getGraph());
    l_orders = std::move(l_graph_reader.getReader());
    m_process_manager.process(l_orders, 5);

    m_cmdGen.clear();
}

void gui::GUI::clearClicked()
{
    m_results.clear();
    m_clearButton.setDisabled(true);
}

void gui::GUI::checkBoxesClicked()
{
    if ((m_emailAddress.isChecked() || m_ipAddress.isChecked() ||
         m_phoneNumber.isChecked()) && m_files.toPlainText().size() > 0)
        m_searchButton.setEnabled(true);
    else
        m_searchButton.setDisabled(true);
}

void gui::GUI::initializePositions()
{
    setFixedSize(m_width, m_height);

    m_searchLabel.move(25, 25),
    m_emailAddress.move(25, 50);
    m_phoneNumber.move(25, 75);
    m_ipAddress.move(25, 100);
    m_fileLabel.move(25, 150);
    m_files.setGeometry(25, 175, 300, 350);
    m_searchButton.setGeometry(345, 25, 200, 25);
    m_searchButton.setDisabled(true);
    m_clearButton.setGeometry(565, 25, 200, 25);
    m_clearButton.setDisabled(true);
    m_results.setGeometry(345, 75, 420, 450);
    m_quitButton.setGeometry(565, 550, 200, 25);
    m_getFilesButton.setGeometry(25, 550, 145, 25);
    m_clearFilesButton.setGeometry(180, 550, 145, 25);
    m_clearFilesButton.setDisabled(true);
}

void gui::GUI::initializeStyle()
{
    QFont l_labelFont(QFont("Times", 16));
    QFont l_buttonFont(QFont("Times", 15, QFont::Bold));
    QFont l_textFieldFont(QFont("Times", 12));
    QFont l_boxFont(QFont("Times", 14));

    m_searchLabel.setFont(l_labelFont);
    m_emailAddress.setFont(l_boxFont);
    m_phoneNumber.setFont(l_boxFont);
    m_ipAddress.setFont(l_boxFont);
    m_fileLabel.setFont(l_labelFont);
    m_files.setFont(l_textFieldFont);
    m_searchButton.setFont(l_buttonFont);
    m_clearButton.setFont(l_buttonFont);
    m_results.setFont(l_textFieldFont);
    m_quitButton.setFont(l_buttonFont);
    m_getFilesButton.setFont(l_buttonFont);
    m_clearFilesButton.setFont(l_buttonFont);
}

void gui::GUI::connectGui()
{
    connect(&m_quitButton, &QAbstractButton::clicked, qApp,
            &QCoreApplication::quit);
    connect(&m_searchButton, &QAbstractButton::clicked, this,
            &GUI::searchClicked);
    connect(&m_clearButton, &QAbstractButton::clicked, this,
            &GUI::clearClicked);
    connect(&m_ipAddress, &QAbstractButton::clicked, this,
            &GUI::checkBoxesClicked);
    connect(&m_phoneNumber, &QAbstractButton::clicked, this,
            &GUI::checkBoxesClicked);
    connect(&m_emailAddress, &QAbstractButton::clicked, this,
            &GUI::checkBoxesClicked);
    connect(&m_files, &QTextEdit::textChanged, this,
            &GUI::checkBoxesClicked);
    connect(&m_results, &QTextEdit::textChanged, this,
            &GUI::searchFieldUpdated);
    connect(&m_getFilesButton, &QAbstractButton::clicked, this,
            &GUI::openFiles);
    connect(&m_clearFilesButton, &QAbstractButton::clicked, this,
            &GUI::clearOpenedFilesList);
    connect(&m_timer, &QTimer::timeout, this, &GUI::updateResults);
    m_timer.start(500);
}

void gui::GUI::searchFieldUpdated()
{
    if (m_results.toPlainText().size() > 0)
        m_clearButton.setEnabled(true);
}

void gui::GUI::openFiles()
{
    QList<QString> getFilesNames = QFileDialog::getOpenFileNames
            (this, "Open Files", QDir::currentPath());
    QString currentText = m_files.toPlainText();

    for (QString &line : getFilesNames)
    {
        if (currentText.size())
            currentText += "\n" + line;
        else
            currentText = line;
    }

    if (currentText.size())
        m_clearFilesButton.setEnabled(true);

    m_files.setText(currentText);
}

void gui::GUI::clearOpenedFilesList()
{
    m_files.clear();
    m_clearFilesButton.setDisabled(true);
}

void gui::GUI::updateResults()
{
    std::vector<std::string> l_results;
    std::string l_str = m_results.toPlainText().toUtf8().toStdString();

    m_process_manager.getResults(l_results);

    for (std::string &r_str : l_results)
    {
        if (l_str.size())
        {
            l_str += "\n" + r_str;
        }
        else
        {
            l_str = r_str;
        }
    }

    m_results.setText(QString(l_str.c_str()));
    waitpid(-1, &m_wait, WNOHANG);
}
