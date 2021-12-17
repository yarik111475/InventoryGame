#ifndef INVENTORYVIEW_H
#define INVENTORYVIEW_H
#include <QtWidgets>


class InventoryView : public QTableView
{
    Q_OBJECT
private:
    QPoint m_dragStartPosition;
    bool m_leftPressed;
    bool m_externalMove;
    int m_oldRow;
    int m_oldColumn;
    int m_newRow;
    int m_newColumn;
protected:
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;
    virtual void dragEnterEvent(QDragEnterEvent *event)override;
    virtual void dropEvent(QDropEvent *event)override;
public:
    InventoryView(QWidget *parent = nullptr);
signals:
    void signalReorederModel(int oldRow,int oldColumn,int newRow,int newColumn);
    void signalEatItem(int row, int column);
};

#endif // INVENTORYVIEW_H
