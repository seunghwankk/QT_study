#ifndef TAB3CONTROLPANNEL_H
#define TAB3CONTROLPANNEL_H

#include <QWidget>
#include <QDebug>
#include <QPalette>
namespace Ui {
class Tab3ControlPannel;
}

class Tab3ControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3ControlPannel(QWidget *parent = nullptr);
    ~Tab3ControlPannel();

private:
    Ui::Tab3ControlPannel *ui;
    QPalette paletteLampOn;
    QPalette paletteLampOff;

signals:
    void sigSocketSendData(QString);

private slots:
    void slotLampOnOff(bool);
    void slotPlugOnOff(bool);
    void slotTab3RecvData(QString);
};

#endif // TAB3CONTROLPANNEL_H
