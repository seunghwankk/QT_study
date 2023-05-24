#ifndef LEDKEYWIDGET_H
#define LEDKEYWIDGET_H

#include <QWidget>
#include <QTimer>
#include "keyled.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LedkeyWidget; }
QT_END_NAMESPACE

class LedkeyWidget : public QWidget
{
    Q_OBJECT

public:
    LedkeyWidget(QWidget *parent = nullptr);
    ~LedkeyWidget();

private:
    Ui::LedkeyWidget *ui;
    KeyLed * pKeyled;
    QTimer * pQTimer;

private slots:
    void slotKeyCheckBoxUpdate(int);
    void slotSetValueDial();
    void slotTimerStart(bool);
    void slotTimerValueChange(QString);
};
#endif // LEDKEYWIDGET_H
