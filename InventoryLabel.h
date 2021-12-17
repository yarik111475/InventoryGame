#ifndef INVENTORYLABEL_H
#define INVENTORYLABEL_H

#include <QtWidgets>

class InventoryLabel : public QLabel
{
    Q_OBJECT
private:
    QPoint m_startPoint;
public:
    explicit InventoryLabel(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *ev)override;
    virtual void mouseMoveEvent(QMouseEvent *ev)override;

signals:

};

#endif // INVENTORYLABEL_H
