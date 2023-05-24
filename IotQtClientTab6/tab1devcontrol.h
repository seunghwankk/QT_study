#ifndef Tab1DevControl_H
#define Tab1DevControl_H

#include <QWidget>
#include <QTimer>
#include "keyled.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tab1DevControl; }
QT_END_NAMESPACE

class Tab1DevControl : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1DevControl(QWidget *parent = nullptr);
    ~Tab1DevControl();
    KeyLed * getpKeyled();

private:
    Ui::Tab1DevControl *ui;
    KeyLed * pKeyled;
    QTimer * pQTimer;

private slots:
    void slotKeyCheckBoxUpdate(int);
    void slotSetValueDial();
    void slotTimerStart(bool);
    void slotTimerValueChange(QString);
public slots:
    void slotDialsetValue(int);
};
#endif // Tab1DevControl_H
