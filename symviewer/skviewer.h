#ifndef SKVIEWER_H
#define SKVIEWER_H

#include <QMainWindow>

class QListWidget;
class SKViewerPanel;
class SKViewerScreen;
class QSplitter;
class QListWidgetItem;
class QVBoxLayout;

class SKPlot2D;

class SKViewer : public QMainWindow
{
    Q_OBJECT

    QSplitter * panelSplitter, * windowSplitter;

    QWidget * screenContainer;
    QVBoxLayout * screenContainerLayout;

    QListWidget * chooser;
    SKViewerScreen * screen;

private slots:

    void chooseHandler(QListWidgetItem*);

public:

    SKViewer(const QString& title);
    ~SKViewer();

    void addViewerPanel(SKViewerPanel*);
    void removeViewerPanel(SKViewerPanel*, bool del = false);

    void clear(bool del = false);

    void updatePanels();
};

#endif // SKVIEWER_H
