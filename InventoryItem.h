#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H
#include <QtWidgets>


class InventoryItem
{
    Q_GADGET
private:
    int m_row;
    int m_column;
    int m_value;
public:
    InventoryItem();
    InventoryItem(int row, int column, int value);
    int getRow()const;
    int getColumn()const;
    int getValue()const;

    void setRow(int row);
    void setColumn(int column);
    void setValue(int value);
};

Q_DECLARE_METATYPE(InventoryItem)

#endif // INVENTORYITEM_H
