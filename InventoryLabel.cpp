#include "InventoryLabel.h"

InventoryLabel::InventoryLabel(QWidget *parent) : QLabel(parent)
{

}

void InventoryLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        m_startPoint=ev->pos();
    }
    QLabel::mousePressEvent(ev);
}

void InventoryLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton){
        int distance=(ev->pos()-m_startPoint).manhattanLength();
        if(distance > QApplication::startDragDistance()){
            QMimeData* pMimeData=new QMimeData;
            pMimeData->setText("external");
            QDrag* pDrag=new QDrag(this);
            pDrag->setMimeData(pMimeData);
            pDrag->setPixmap(QPixmap(":/images/apple.jpg").scaled(50,50));
            pDrag->exec(Qt::CopyAction);
        }
    }
   QLabel::mouseMoveEvent(ev);
}
