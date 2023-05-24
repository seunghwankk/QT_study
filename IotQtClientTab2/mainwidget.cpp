#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    pTab1DevControl = new Tab1DevControl(ui->pTab1);
    ui->pTab1->setLayout(pTab1DevControl->layout());
    pTab2SocketClient = new Tab2SocketClient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SocketClient->layout());
//    connect(pTab2SocketClient, SIGNAL(sigLedWrite(int)), pTab1DevControl->getpKeyled(), SLOT(writeLedData(int)));
    connect(pTab2SocketClient, SIGNAL(sigLedWrite(int)), pTab1DevControl, SLOT(slotDialsetValue(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

