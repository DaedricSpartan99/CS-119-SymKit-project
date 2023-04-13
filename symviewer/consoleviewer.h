#ifndef CONSOLEVIEWER_H
#define CONSOLEVIEWER_H

#include <QPlainTextEdit>
#include <QThread>

#include <fstream>

class ConsoleThread : public QThread
{
    std::ifstream stream;

    volatile bool running;
    volatile bool enabled;

    virtual void run() override;

    Q_OBJECT

public:

    ConsoleThread(std::istream&);
    ~ConsoleThread();

    void setInputEnabled(bool);

    bool isInputEnabled() const;

    void startInputLoop();
    void stopInputLoop();

signals:

    void inputLine(const QString&);
};

class ConsoleViewer : public QPlainTextEdit
{
    Q_OBJECT

    ConsoleThread thread;

private slots:

    void inputLineHandler(const QString&);

public:

    ConsoleViewer(std::istream&, QWidget *parent = 0);

    ConsoleThread * getConsoleThread();
};

/*#include <fstream>

class ConsoleViewer : public QPlainTextEdit
{

    std::ifstream stream;

public:

    ConsoleViewer(std::istream&, QWidget *parent = 0);

    void checkForPushedData();
};*/

#endif // CONSOLEVIEWER_H
