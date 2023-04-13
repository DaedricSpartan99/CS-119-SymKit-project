#ifndef SKVIEWERPANEL_H
#define SKVIEWERPANEL_H

#include <QWidget>

class SKViewerPanel : public QWidget
{
    Q_OBJECT

public:

    // null parent
    SKViewerPanel(QWidget *parent = 0);

    ~SKViewerPanel() {}

    virtual void updatePanel() = 0;

    virtual QString getLabel() const = 0;

    void addToDedicated(QWidget*);

    void removeFromDedicated(QWidget*);

    virtual QWidget * getDedicated() = 0;

    void setDedicatedLayout(QLayout*);
};

#endif // SKVIEWERPANEL_H
