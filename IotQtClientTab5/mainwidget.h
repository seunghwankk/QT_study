#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1devcontrol.h"
#include "tab2socketclient.h"
#include "tab3controlpannel.h"
#include "tab5chartplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab1DevControl * pTab1DevControl;
    Tab2SocketClient * pTab2SocketClient;
    Tab3ControlPannel * pTab3ControlPannel;
    Tab5ChartPlot * pTab5ChartPlot;
};
#endif // MAINWIDGET_H
