#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEvent>
#include <QMainWindow>
#include <QtWidgets>
#include <QSound>

#include "InventoryModel.h"
#include "InventoryLabel.h"
#include "InventoryView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    const int BASE_SIZE=100;
    InventoryModel* m_pInventoryModel;
    InventoryView* m_pInventoryView;

    QGroupBox* m_pControlButtonsGroupBox;
    QGroupBox* m_pGameFieldGroupBox;
    QGroupBox* m_pInventoryGroupBox;

private slots:
    void slotStartGame();
    void slotResetGame();
    void slotQuit();
    void slotMainMenu();
    void slotReorederModel(int oldRow,int oldColumn,int newRow,int newColumn);
    void slotEatItem(int row, int column);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void resizeEvent(QResizeEvent *event)override;
};
#endif // MAINWINDOW_H
