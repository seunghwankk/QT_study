#include "tab6database.h"
#include "ui_tab6database.h"

Tab6Database::Tab6Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6Database)
{
    ui->setupUi(this);
    sqlDb = QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName("temp.db");
    if(sqlDb.open()) {
        qDebug() << "success DB connection";
    }
    else {
        qDebug() << "fail DB connection";
    }
    QString query = "CREATE TABLE temp_db ("
                    "id integer primary key,"
                    "date DATETIME,"
                    "illu VARCHAR(10))";
    QSqlQuery qry;
    if(!qry.exec(query))
    {

    }
    else
    {
        qDebug() << "create table";
    }
    connect(ui->pPBSearchButton,SIGNAL(clicked()),this,SLOT(slotSearchDb()));
    connect(ui->pPBDeleteButton,SIGNAL(clicked()),this,SLOT(slotDeleteDb()));
}

Tab6Database::~Tab6Database()
{
    delete ui;
}
void Tab6Database::slotTab6RecvData(QString recvData)
{
//    qDebug() << recvData;
    QDateTime dateTime = QDateTime::currentDateTime();
    QSqlQuery qry;
    QString query;

    recvData.replace("[","@");
    recvData.replace("]","@");
    QStringList qlist = recvData.split("@");
    QString illu = qlist[3];   //조도

    query = "insert into temp_db(date,illu) values('" +
            dateTime.toString("yy/MM/dd hh:mm:ss") +
            "', '" + illu + "')";
    if(qry.exec(query))
    {
//        qDebug() << "insert Ok";
    }
    else
    {
        qDebug() << qry.lastError().text();
    }
}
void Tab6Database::slotSearchDb()
{
    QSqlQuery qry;
    QString query;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    int rowCount = 0;
    ui->pTableWidget->clearContents();
    query = "select * from temp_db where date>'"+strFrom+"' AND date < '" + strTo +"'";
    if(qry.exec(query)) {
        while(qry.next()) {
           rowCount++;
           ui->pTableWidget->setRowCount(rowCount);
           QTableWidgetItem *id = new QTableWidgetItem();
           QTableWidgetItem *date = new QTableWidgetItem();
           QTableWidgetItem *illu = new QTableWidgetItem();

           id->setText(qry.value("id").toString());
           date->setText(qry.value("date").toString());
           illu->setText(qry.value("illu").toString());
           ui->pTableWidget->setItem(rowCount-1,0,id);
           ui->pTableWidget->setItem(rowCount-1,1,date);
           ui->pTableWidget->setItem(rowCount-1,2,illu);
        }
    }
}
void Tab6Database::slotDeleteDb()
{
    QSqlQuery qry;
    QString query;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    query = "delete from temp_db where date >'" + strFrom + "' AND date < '"+ strTo + "'";
    if(qry.exec(query)) {
    }
}
