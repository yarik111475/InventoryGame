#ifndef INVENTORYBASE_H
#define INVENTORYBASE_H

#include <QSql>
#include <QtCore>
#include <QObject>

class InventoryItem;

class InventoryBase
{
private:
    bool m_isValid;
    static InventoryBase* m_instance;
    const QString m_inventoryPath{qApp->applicationDirPath() + "/inventory.sqlite"};
    InventoryBase();
    void initInventory();

public:

    InventoryBase(const InventoryBase& other)=delete;
    InventoryBase& operator=(const InventoryBase& other)=delete;

    bool isValid();
    static InventoryBase* getInstance();
    QList<InventoryItem> loadInventoryList();
    void saveInventoryList(const QList<InventoryItem>& inventoryList);
    void clearInventory();
};

#endif // INVENTORYBASE_H
