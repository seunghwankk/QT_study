#include "tab5chartplot.h"
#include "ui_tab5chartplot.h"

Tab5ChartPlot::Tab5ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab5ChartPlot)
{
    ui->setupUi(this);
    pIlluLine = new QLineSeries(this);
    pIlluLine->setName("조도");

    pTempLine = new QLineSeries(this);
    pTempLine->setName("온도");

    pHumiLine = new QLineSeries(this);
    pHumiLine->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pIlluLine->setPen(pen);

    chart = new QChart();
    chart->addSeries(pIlluLine);

    pen.setBrush(Qt::green);
    pTempLine->setPen(pen);
    chart->addSeries(pTempLine);

    pen.setBrush(Qt::blue);
    pHumiLine->setPen(pen);
    chart->addSeries(pHumiLine);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0,100);
//    chart->axes(Qt::Horizontal).first()->setRange(0,20);

/*     pIlluLine->append(0, 20);
     pIlluLine->append(5, 80);
     pIlluLine->append(10, 50);
     pIlluLine->append(15, 70);
     pIlluLine->append(20, 10);
*/
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->pChartHLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
//    axisX->setFormat("MM.dd h:mm");
    axisX->setFormat("h:mm");

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    firstDate.setDate(date);
    firstDate.setTime(time);
    chartView->chart()->setAxisX(axisX,pIlluLine);
    chartView->chart()->setAxisX(axisX,pTempLine);
    chartView->chart()->setAxisX(axisX,pHumiLine);

    QTime tempTime = time.addSecs(4200); //60*10분
    lastDate.setDate(date);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate,lastDate);

    connect(ui->pPBAddButton,SIGNAL(clicked()),this,SLOT(chartPlotAdd()));
    connect(ui->pPBClearButton,SIGNAL(clicked()),this,SLOT(chartPlotClear()));

}

Tab5ChartPlot::~Tab5ChartPlot()
{
    delete ui;
}
void Tab5ChartPlot::chartPlotClear()
{
    pIlluLine->clear();
}

void Tab5ChartPlot::chartPlotAdd()
{
    pIlluLine->append(ui->pLExPosition->text().toDouble(),ui->pLEyPosition->text().toDouble());
    ui->pLExPosition->clear();
    ui->pLEyPosition->clear();
}

void Tab5ChartPlot::slotTab5RecvData(QString recvData)
{
//    qDebug() << recvData;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    recvData.replace("[","@");
    recvData.replace("]","@");
    QStringList qlist = recvData.split("@");

    pIlluLine->append(xValue.toMSecsSinceEpoch(),qlist[3].toDouble()); //조도
    pTempLine->append(xValue.toMSecsSinceEpoch(),qlist[4].toDouble()); //온도
    pHumiLine->append(xValue.toMSecsSinceEpoch(),qlist[5].toDouble()); //습도
}
