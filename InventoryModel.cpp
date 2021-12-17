#include "InventoryModel.h"

InventoryModel::InventoryModel(int rows, int columns, QObject *parent)
    :QAbstractTableModel(parent),
      m_rows{rows},
      m_columns{columns}
{

}

QVariant InventoryModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    if(!index.isValid()){
        return QVariant();
    }
    InventoryItem item=m_inventoryHash[index].value<InventoryItem>();
    if(item.getValue() && role==Qt::DecorationRole){
        return QPixmap(":/images/apple.jpg").scaled(70,70);
    }
    if(item.getValue() && role==Qt::DisplayRole){
        return item.getValue();
    }

    return QVariant();
}

bool InventoryModel::setData(const QModelIndex &index,
                             const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(index.isValid()){
        m_inventoryHash[index]=value;

        emit dataChanged(index,index);
        return true;
    }
    return false;
}

int InventoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rows;
}

int InventoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columns;
}

Qt::DropActions InventoryModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags InventoryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

bool InventoryModel::canDropMimeData(const QMimeData *data,
                                     Qt::DropAction action,
                                     int row,
                                     int column,
                                     const QModelIndex &parent) const
{
    Q_UNUSED(data)
    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)

    return true;
}

bool InventoryModel::dropMimeData(const QMimeData *data,
                                  Qt::DropAction action,
                                  int row,
                                  int column,
                                  const QModelIndex &parent)
{
    Q_UNUSED(data)
    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)

    return true;
}

InventoryItem InventoryModel::getInventoryItem(int row, int column) const
{
    QModelIndex idx=index(row, column);
    if(idx.isValid()){
        return m_inventoryHash[idx].value<InventoryItem>();
    }
    return InventoryItem();
}

void InventoryModel::setInventoryItem(int row, int column, const InventoryItem& item)
{
    QModelIndex idx=index(row, column);
    if(idx.isValid()){
        setData(idx, QVariant::fromValue(item), Qt::DisplayRole);
    }
}

void InventoryModel::removeInventoryItem(int row, int column)
{
    QModelIndex idx=index(row, column);
    if(idx.isValid()){
        InventoryItem item=m_inventoryHash[idx].value<InventoryItem>();
        int oldValue=(item.getValue()==0) ? item.getValue() : item.getValue()-1;
        item.setValue(oldValue);
        setData(idx, QVariant::fromValue(item), Qt::DisplayRole);
    }
}

QList<InventoryItem> InventoryModel::getInventoriyList() const
{
    QList<InventoryItem> inventoryList;
    for(const QModelIndex& idx : m_inventoryHash.keys()){
        InventoryItem item=m_inventoryHash[idx].value<InventoryItem>();
        inventoryList.push_back(item);
    }
    return inventoryList;
}

void InventoryModel::setInventoryList(const QList<InventoryItem> &inventoryList)
{
    for(const InventoryItem& item : inventoryList){
        setInventoryItem(item.getRow(), item.getColumn(),item);
    }
}

void InventoryModel::resetModel()
{
    for(int row=0;row<rowCount(QModelIndex());row++){
        for(int column=0;column<columnCount(QModelIndex());++column){
            setInventoryItem(row, column, InventoryItem(row,column,0));
        }
    }
}

