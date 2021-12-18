#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEvent>
#include <QMainWindow>
#include <QtWidgets>
#include <QSound>



class InventoryModel;
class InventoryLabel;
class InventoryView;
class InventoryBase;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    const int BASE_SIZE=100;
    InventoryModel* m_pInventoryModel;
    InventoryView* m_pInventoryView;
    InventoryBase* m_pInventoryBase;

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
    void tryLoadGame();
    ~MainWindow();
protected:
    virtual void resizeEvent(QResizeEvent *event)override;
    virtual void closeEvent(QCloseEvent *event)override;
};
#endif // MAINWINDOW_H
