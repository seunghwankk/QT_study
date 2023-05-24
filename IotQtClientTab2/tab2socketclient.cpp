#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);
    ui->pPBSendButton->setEnabled(false);
    connect(ui->pPBServerConnect, SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer(bool)));
    connect(ui->pPBSendButton, SIGNAL(clicked()), this, SLOT(slotSocketSendData()));
    connect(pSocketClient, SIGNAL(sigSocketRecv(QString)), this, SLOT(slotSocketRecvUpdate(QString)));
}

void Tab2SocketClient::slotConnectToServer(bool check)
{
    bool bOk;
    if(check)
    {
        pSocketClient->slotConnectToServer(bOk);
        if(bOk)
        {
            ui->pPBServerConnect->setText("서버 해제");
            ui->pPBSendButton->setEnabled(true);
        }
        else
        {
            ui->pPBServerConnect->setChecked(false);
        }
    }
    else
    {
        pSocketClient->slotClosedByServer();
        ui->pPBServerConnect->setText("서버 해제");
        ui->pPBServerConnect->setChecked(false);
    }
}

void Tab2SocketClient::slotSocketSendData()
{
    QString strRecvId;
    QString strSendData;

    strRecvId = ui->pLErecvId->text();
    strSendData = ui->pLEsendData->text();
    if(strRecvId.isEmpty())
        strSendData = "[ALLMSG]" + strSendData;
    else
        strSendData = "[" + strRecvId + "]" + strSendData;
    pSocketClient->slotSocketSendData(strSendData);
    ui->pLEsendData->clear();
}

void Tab2SocketClient::slotSocketRecvUpdate(QString strRecvData)
{
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strRecvData.chop(1);               //'\n'제거
    strTime = strTime + " " + strRecvData;
    ui->pTErecvData->append(strTime);
    ui->pTErecvData->moveCursor(QTextCursor::End);

    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList qlist = strRecvData.split("@");

    if(qlist[2] == "LED")
    {
        int iLedNo = qlist[3].toInt();
        emit sigLedWrite(iLedNo);
    }
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}
