#include "notes.h"
#include "ui_notes.h"


notes::notes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notes)
{
    ui->setupUi(this);
}

notes::~notes()
{
    delete ui;
}

//收到登录成功的槽函数
void notes::on_notescreate(QString loc_temp,QWidget* temp)
{
    loc=loc_temp;
QSettings* config = new QSettings (loc+"/notes.ini", QSettings::IniFormat);//构建函数.参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
ui->note->setText(config->value("/NOTES/CONTENT").toString());
 connect(this,SIGNAL(notessuccess(QString)),temp,SLOT(on_notessuccess(QString)));
}

void notes::on_save_clicked()
{
    QSettings* config = new QSettings (loc+"/notes.ini", QSettings::IniFormat);//构建函数.参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
     config->setValue("/NOTES/CONTENT",ui->note->text());
     emit notessuccess(ui->note->text());
     this->close();
}

