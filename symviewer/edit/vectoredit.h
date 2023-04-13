#ifndef SVECTOREDIT_H
#define SVECTOREDIT_H

#include <QGroupBox>
#include <vector>

#include <memory>
#include <QLineEdit>

class QBoxLayout;

class VectorEdit : public QGroupBox
{
    Q_OBJECT

    std::vector<std::unique_ptr<QLineEdit>> components;

    QBoxLayout * layout;

signals:

    void valueChanged(std::size_t, double value);

private slots:

    void returnHandle();

public:

    VectorEdit(const QString &label,
               Qt::Orientation orient,
               const double *init = 0,
               std::size_t size = 3,
               QWidget *parent = 0);

    ~VectorEdit();

    std::size_t pushComponent(double init = 0);
    void popComponent();

    std::size_t size() const;

    void setContent(std::size_t index, double value, bool force = false);
    double getContent(std::size_t index);

    bool isFocused(std::size_t) const;

    void setAll(const double *buffer, std::size_t count, bool force = false);
};

#endif // SVECTOREDIT_H
