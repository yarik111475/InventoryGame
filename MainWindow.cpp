#include "MainWindow.h"


void MainWindow::slotStartGame()
{
    m_pControlButtonsGroupBox->setEnabled(false);
    m_pGameFieldGroupBox->setEnabled(true);
    m_pInventoryGroupBox->setEnabled(true);
}

void MainWindow::slotResetGame()
{
    m_pInventoryModel->resetModel();
}

void MainWindow::slotQuit()
{
    qApp->quit();
}

void MainWindow::slotMainMenu()
{
    m_pControlButtonsGroupBox->setEnabled(true);
    m_pGameFieldGroupBox->setEnabled(false);
    m_pInventoryGroupBox->setEnabled(false);
}

void MainWindow::slotReorederModel(int oldRow, int oldColumn, int newRow, int newColumn)
{
    if(oldRow!=-1 && oldColumn!=-1){
        int oldCurrentValue=m_pInventoryModel->getInventoryItem(oldRow,oldColumn).getValue();
        int newCurrentValue=m_pInventoryModel->getInventoryItem(newRow,newColumn).getValue();

        m_pInventoryModel->setInventoryItem(newRow,newColumn, InventoryItem(newRow,newColumn, oldCurrentValue+newCurrentValue));
        m_pInventoryModel->removeInventoryItem(oldRow,oldColumn);
    }
    else{
        int currentValue=m_pInventoryModel->getInventoryItem(newRow,newColumn).getValue();
        m_pInventoryModel->setInventoryItem(newRow,newColumn, InventoryItem(newRow,newColumn,++currentValue));
    }
}

void MainWindow::slotEatItem(int row, int column)
{
    int currentValue=m_pInventoryModel->getInventoryItem(row,column).getValue();
    if(currentValue==0){
        return;
    }
    QSound::play(":/sounds/apple.wav");
    currentValue-=1;
    if(currentValue==0){
        m_pInventoryModel->removeInventoryItem(row, column);
    }
    else{
         m_pInventoryModel->setInventoryItem(row, column, InventoryItem(row, column,currentValue));
    }

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton* pStartGamePushButton=
            new QPushButton(QObject::tr("Start game"));
    QObject::connect(pStartGamePushButton, SIGNAL(clicked(bool)),
                     this, SLOT(slotStartGame()));
    QPushButton* pResetGamePushButton=
            new QPushButton(QObject::tr("Reset game"));
    QObject::connect(pResetGamePushButton, SIGNAL(clicked(bool)),
                     this, SLOT(slotResetGame()));

    QPushButton* pQuitPushButton=
            new QPushButton(QObject::tr("Quit"));
    QObject::connect(pQuitPushButton, SIGNAL(clicked(bool)),
                     this, SLOT(slotQuit()));

    QHBoxLayout* pControlButtonsHBoxLayout=new QHBoxLayout;
    pControlButtonsHBoxLayout->addWidget(pStartGamePushButton);
    pControlButtonsHBoxLayout->addWidget(pResetGamePushButton);
    pControlButtonsHBoxLayout->addWidget(pQuitPushButton);
    m_pControlButtonsGroupBox=new QGroupBox(QObject::tr("Control buttons"));
    m_pControlButtonsGroupBox->setLayout(pControlButtonsHBoxLayout);


    m_pInventoryView=new InventoryView;
    QObject::connect(m_pInventoryView, SIGNAL(signalReorederModel(int,int,int,int)),
                     this, SLOT(slotReorederModel(int,int,int,int)));
    QObject::connect(m_pInventoryView, SIGNAL(signalEatItem(int,int)),
                     this, SLOT(slotEatItem(int,int)));

    m_pInventoryModel=new InventoryModel(4,4);
    m_pInventoryView->setModel(m_pInventoryModel);


    for(int i=0;i<m_pInventoryModel->rowCount(QModelIndex());i++){
        m_pInventoryView->setRowHeight(i, BASE_SIZE);
    }
    for(int j=0;j<m_pInventoryModel->columnCount(QModelIndex());++j){
        m_pInventoryView->setColumnWidth(j, BASE_SIZE);
    }

    m_pGameFieldGroupBox=new QGroupBox(QObject::tr("Game field"));
    QVBoxLayout* pGameFieldVBoxLayout=new QVBoxLayout;
    pGameFieldVBoxLayout->addWidget(m_pInventoryView);
    m_pGameFieldGroupBox->setLayout(pGameFieldVBoxLayout);

    QVBoxLayout* pLeftVBoxLayout=new QVBoxLayout;
    pLeftVBoxLayout->addWidget(m_pControlButtonsGroupBox);
    pLeftVBoxLayout->addWidget(m_pGameFieldGroupBox);

    QPushButton* pMainMenuPushButton
            =new QPushButton(QObject::tr("Main menu"));
    QObject::connect(pMainMenuPushButton, SIGNAL(clicked(bool)),
                     this, SLOT(slotMainMenu()));

    InventoryLabel* pInventoryLabel=new InventoryLabel;
    pInventoryLabel->setPixmap(QPixmap(":/images/apple.jpg").scaled(BASE_SIZE,BASE_SIZE));


    QVBoxLayout* pRightVBoxLayout=new QVBoxLayout;
    pRightVBoxLayout->addWidget(pMainMenuPushButton);
    pRightVBoxLayout->addWidget(pInventoryLabel);

    m_pInventoryGroupBox=new QGroupBox(QObject::tr("Inventory"));
    m_pInventoryGroupBox->setLayout(pRightVBoxLayout);

    QHBoxLayout* pMainHBoxLayout=new QHBoxLayout;
    pMainHBoxLayout->addLayout(pLeftVBoxLayout);
    pMainHBoxLayout->addWidget(m_pInventoryGroupBox);

    QWidget* pCentralWidget=new QWidget;
    pCentralWidget->setLayout(pMainHBoxLayout);
    setCentralWidget(pCentralWidget);

    m_pInventoryGroupBox->setEnabled(false);
    m_pGameFieldGroupBox->setEnabled(false);
    resize(570,517);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"width: " + QString::number(event->size().width());
    qDebug()<<"height: " + QString::number(event->size().height());
}

