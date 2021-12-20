#include "InventoryBase.h"
#include "InventoryItem.h"

#include <QSqlQuery>
#include <QSqlDatabase>

InventoryBase* InventoryBase::m_instance{nullptr};

InventoryBase::InventoryBase()
{
    initInventory();
}

void InventoryBase::initInventory()
{
    QString connectionName;

    if(!QFile::exists(m_inventoryPath)){
        QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(m_inventoryPath);
        if(!database.open()){
            m_isValid=false;
        }
        else{
            connectionName=database.connectionName();
            QString queryText="CREATE TABLE IF NOT EXISTS 'inventoryTable' ('row' INT, 'column' INT, 'value' INT)";
            QSqlQuery query(database);
            query.prepare(queryText);
            if(query.exec()){
                m_isValid=true;
            }
            else{
                m_isValid=false;
            }
        }
    }
    else{
        m_isValid=true;
    }
    QSqlDatabase::removeDatabase(connectionName);
}

bool InventoryBase::isValid()
{
    return m_isValid;
}

InventoryBase *InventoryBase::getInstance()
{
    if(m_instance==nullptr){
       m_instance=new InventoryBase;
    }
    return m_instance;
}

QList<InventoryItem> InventoryBase::loadInventoryList()
{
    QList<InventoryItem> inventoryList;
    QString connectionName;
    {
        QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(m_inventoryPath);
        if(!database.open()){
            return inventoryList;
        }
        else{
            connectionName=database.connectionName();
            QString queryText="SELECT * FROM 'inventoryTable'";
            QSqlQuery query(database);
            query.prepare(queryText);
            if(query.exec()){
                while(query.next()){
                    int row=query.value("row").toInt();
                    int column=query.value("column").toInt();
                    int value=query.value("value").toInt();

                    inventoryList.push_back(InventoryItem(row,column,value));
                }
            }
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    return inventoryList;
}

void InventoryBase::saveInventoryList(const QList<InventoryItem> &inventoryList)
{
    QString connectionName;
    {
        QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(m_inventoryPath);
        if(!database.open()){
            return;
        }
        else{
            connectionName=database.connectionName();
            QString queryText="INSERT INTO 'inventoryTable' (row,column,value) VALUES(:row, :column, :value)";
            QSqlQuery query(database);

            query.prepare(queryText);
            for(const InventoryItem& item : inventoryList){
                query.bindValue(":row", item.getRow());
                query.bindValue(":column", item.getColumn());
                query.bindValue(":value", item.getValue());
                query.exec();
            }
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
}

void InventoryBase::clearInventory()
{
    QString connectionName;
    {
        QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(m_inventoryPath);
        if(!database.open()){
            m_isValid=false;
        }
        else{
            connectionName=database.connectionName();
            QString queryText="DELETE FROM 'inventoryTable'";
            QSqlQuery query(database);
            query.prepare(queryText);
            query.exec();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
}




