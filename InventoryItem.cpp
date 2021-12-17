#include "InventoryItem.h"

InventoryItem::InventoryItem()
    :m_row{0}, m_column{0}, m_value{0}
{

}

InventoryItem::InventoryItem(int row, int column, int value)
    :m_row{row},m_column{column},m_value{value}
{

}

int InventoryItem::getRow() const
{
    return m_row;
}

int InventoryItem::getColumn() const
{
    return m_column;
}

int InventoryItem::getValue() const
{
    return m_value;
}

void InventoryItem::setRow(int row)
{
    m_row=row;
}

void InventoryItem::setColumn(int column)
{
    m_column=column;
}

void InventoryItem::setValue(int value)
{
    m_value=value;
}
