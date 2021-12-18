#include "InventoryView.h"

void InventoryView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        m_leftPressed=true;
        m_oldRow=rowAt(event->pos().y());
        m_oldColumn=columnAt(event->pos().x());
    }
    else if(event->button()==Qt::RightButton){
        int row=rowAt(event->pos().y());
        int column=columnAt(event->pos().x());
        emit signalEatItem(row, column);
    }

    QTableView::mousePressEvent(event);
}

void InventoryView::mouseMoveEvent(QMouseEvent *event)
{
    QTableView::mouseMoveEvent(event);
}

void InventoryView::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
    const QMimeData* pMimeData=event->mimeData();
    if(pMimeData){
        QString marker=pMimeData->text();
        if(marker=="external"){
            setDragDropMode(QTableView::InternalMove);
        }
    }
    QTableView::dragEnterEvent(event);
}

void InventoryView::dropEvent(QDropEvent *event)
{
    if(m_leftPressed){
        m_newRow=rowAt(event->pos().y());
        m_newColumn=columnAt(event->pos().x());
        emit signalReorederModel(m_oldRow, m_oldColumn, m_newRow,m_newColumn);
    }
    const QMimeData* pMimeData=event->mimeData();
    if(pMimeData){
        QString marker=pMimeData->text();
        if(marker=="external"){
            m_newRow=rowAt(event->pos().y());
            m_newColumn=columnAt(event->pos().x());
            emit signalReorederModel(-1, -1, m_newRow,m_newColumn);
        }
    }
    setDragDropMode(QTableView::DragDrop);

    m_leftPressed=false;
    m_oldRow=-1;
    m_oldColumn=-1;
    QTableView::dropEvent(event);
}

InventoryView::InventoryView(QWidget *parent)
    :QTableView(parent),m_externalMove{false},m_leftPressed{false},
      m_oldRow{-1}, m_oldColumn{-1}, m_newRow{-1},m_newColumn{-1}
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QTableView::DragDrop);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setFocusPolicy(Qt::NoFocus);
    setDropIndicatorShown(true);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

}
