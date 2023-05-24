#include "tab3controlpannel.h"
#include "ui_tab3controlpannel.h"

Tab3ControlPannel::Tab3ControlPannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab3ControlPannel)
{
    ui->setupUi(this);
    paletteLampOn.setColor(ui->pPBLamp->backgroundRole(),QColor(255,0,0));
    paletteLampOff.setColor(ui->pPBLamp->backgroundRole(),QColor(0,0,255));
    ui->pPBLamp->setPalette(paletteLampOff);
    ui->pPBPlug->setPalette(paletteLampOff);
    connect(ui->pPBLamp,SIGNAL(clicked(bool)),this,SLOT(slotLampOnOff(bool)));
    connect(ui->pPBPlug,SIGNAL(clicked(bool)),this,SLOT(slotPlugOnOff(bool)));
}


void Tab3ControlPannel::slotLampOnOff(bool check)
{
    if(check) {
        emit sigSocketSendData("[ksh_QT]LAMPON");
        ui->pPBLamp->setChecked(false);
    } else {
        emit sigSocketSendData("[ksh_QT]LAMPOFF");
        ui->pPBLamp->setChecked(true);
    }

}
void Tab3ControlPannel::slotPlugOnOff(bool check)
{

    if(check) {
        emit sigSocketSendData("[ksh_QT]GASON");
        ui->pPBPlug->setChecked(false);

    } else {
        emit sigSocketSendData("[ksh_QT]GASOFF");
        ui->pPBPlug->setChecked(true);
    }
}

void Tab3ControlPannel::slotTab3RecvData(QString recvData)
{
//    QIcon icon;
    QStringList qlist = recvData.split("@");
//  qDebug() << "slotTab3RecvData : " << recvData;


    if(qlist[2] == "LAMPON") {     
        ui->pPBLamp->setChecked(true);
        ui->pPBLamp->setPalette(paletteLampOn);
//        icon.addFile(":/IotQtClient/Image/light_on.png");
    }
    else if(qlist[2] == "LAMPOFF") {
        ui->pPBLamp->setChecked(false);
        ui->pPBLamp->setPalette(paletteLampOff);
//        icon.addFile(":/IotQtClient/Image/light_off.png");
    }
    else if(qlist[2] == "GASON") {
        ui->pPBPlug->setChecked(true);
        ui->pPBPlug->setPalette(paletteLampOn);
    }
    else if(qlist[2] == "GASOFF") {
        ui->pPBPlug->setChecked(false);
        ui->pPBPlug->setPalette(paletteLampOff);
    }
}

Tab3ControlPannel::~Tab3ControlPannel()
{
    delete ui;
}
