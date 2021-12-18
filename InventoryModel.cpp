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
        beginResetModel();
        m_inventoryHash.insert(idx,QVariant::fromValue(item));
        endResetModel();
    }
}

void InventoryModel::removeInventoryItem(int row, int column)
{
    QModelIndex idx=index(row, column);
    if(idx.isValid()){
        beginResetModel();
        m_inventoryHash.remove(idx);
        endResetModel();
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
    beginResetModel();
    for(const InventoryItem& item : inventoryList){
        setInventoryItem(item.getRow(), item.getColumn(),item);
    }
    endResetModel();
}

void InventoryModel::resetModel()
{
    beginResetModel();
    for(int row=0;row<rowCount(QModelIndex());row++){
        for(int column=0;column<columnCount(QModelIndex());++column){
            QModelIndex idx{index(row,column)};
            if(idx.isValid()){
                m_inventoryHash.remove(idx);
            }
        }
    }
    endResetModel();
}

bool InventoryModel::isEmpty()
{
    return m_inventoryHash.isEmpty();
}

