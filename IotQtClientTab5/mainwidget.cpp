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

    pTab3ControlPannel = new Tab3ControlPannel(ui->pTab3);
    ui->pTab3->setLayout(pTab3ControlPannel->layout());

    pTab5ChartPlot = new Tab5ChartPlot(ui->pTab5);
    ui->pTab5->setLayout(pTab5ChartPlot->layout());

    connect(pTab2SocketClient, SIGNAL(sigLedWrite(int)), pTab1DevControl, SLOT(slotDialsetValue(int)));
    connect(pTab3ControlPannel, SIGNAL(sigSocketSendData(QString)), pTab2SocketClient, SLOT(slotSocketSendData(QString)));
    connect(pTab2SocketClient, SIGNAL(sigTab3RecvData(QString)), pTab3ControlPannel, SLOT(slotTab3RecvData(QString)));
    connect(pTab2SocketClient, SIGNAL(sigTab5RecvData(QString)), pTab5ChartPlot, SLOT(slotTab5RecvData(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

