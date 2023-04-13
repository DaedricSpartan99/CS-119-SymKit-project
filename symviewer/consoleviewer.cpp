#include "consoleviewer.h"

#include <istream>
#include <ostream>

using namespace std;

ConsoleThread::ConsoleThread(istream& is)

    : running(false), enabled(true)
{
    /* copy input stream */

    stream.copyfmt(is);

    stream.clear(is.rdstate());
    stream.basic_ios<char>::rdbuf(is.rdbuf());
}

ConsoleThread::~ConsoleThread()
{
    stopInputLoop();
}

void ConsoleThread::startInputLoop()
{
    if (!running)
    {
        running = true;
        QThread::start();
    }
}

void ConsoleThread::stopInputLoop()
{
    if (running)
    {
        running = false;

        /*
         * Not a good method but
         * it's the only one to return from
         * getline blocking call
         */
        QThread::terminate();
    }
}

void ConsoleThread::setInputEnabled(bool enabled)
{
    this->enabled = enabled;
}

bool ConsoleThread::isInputEnabled() const
{
    return enabled;
}

//#include <iostream>

void ConsoleThread::run()
{
    string buffer;

    while(running)
    {
        if (enabled && getline(stream, buffer) && !buffer.empty())
        {
            //cout << "Working" << endl;
            emit inputLine(QString(buffer.c_str()));
        }
    }
}

ConsoleViewer::ConsoleViewer(std::istream& is, QWidget *parent)

    : QPlainTextEdit(parent), thread(is)
{
    connect(&thread, SIGNAL(inputLine(QString)), this, SLOT(inputLineHandler(QString)));
}

void ConsoleViewer::inputLineHandler(const QString &str)
{
    moveCursor(QTextCursor::End);
    insertPlainText(str);
    moveCursor(QTextCursor::End);

    update();
}

ConsoleThread * ConsoleViewer::getConsoleThread()
{
    return &thread;
}
