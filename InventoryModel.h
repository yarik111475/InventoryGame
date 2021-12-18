#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H
#include <QEvent>
#include <QtWidgets>
#include "InventoryItem.h"


class InventoryModel : public QAbstractTableModel
{
private:
    int m_rows;
    int m_columns;
    int m_rowFrom;
    int m_columnFrom;
    int m_currentValue;
    QHash<QModelIndex, QVariant> m_inventoryHash;
public:
    InventoryModel(int rows, int columns, QObject* parent=nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    Qt::DropActions supportedDropActions() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool canDropMimeData(const QMimeData *data,
                         Qt::DropAction action,
                         int row,
                         int column,
                         const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data,
                      Qt::DropAction action,
                      int row,
                      int column,
                      const QModelIndex &parent)override;


    Q_INVOKABLE
    InventoryItem getInventoryItem(int row, int column)const;
    Q_INVOKABLE
    void setInventoryItem(int row, int column, const InventoryItem &item);
    Q_INVOKABLE
    void removeInventoryItem(int row, int column);
    Q_INVOKABLE
    QList<InventoryItem> getInventoriyList()const;
    Q_INVOKABLE
    void setInventoryList(const QList<InventoryItem>& inventoryList);
    Q_INVOKABLE
    void resetModel();
    Q_INVOKABLE
    bool isEmpty();
};

#endif // INVENTORYMODEL_H
