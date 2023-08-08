#include "set.h"
#include "ui_set.h"

set::set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set)

{
    ui->setupUi(this);

}

set::~set()
{
    delete ui;
}

//收到登录成功的槽函数
void set::on_setcreate(QString loc,QWidget* temp)
{
ui->loc->setText(loc);
 connect(this,SIGNAL(setsuccess(QString)),temp,SLOT(on_setsuccess(QString)));
}


void set::on_choose_clicked()
{
        QByteArray data;
          QString selectedDir=QFileDialog::getExistingDirectory(this,"请选择存档的备份目录","./",QFileDialog::ShowDirsOnly);

        if (!selectedDir.isEmpty())
        {

            static QRegularExpression re("\\");
            selectedDir = selectedDir.replace(re, "/");
              //显示选择的目录路径
             ui->loc->setText(selectedDir);

        }

}


void set::on_save_clicked()
{
     QSettings *config = new QSettings (QDir::homePath()+"/AppData/Roaming/EldenRing/ER_SAVE/config.ini", QSettings::IniFormat);//构建函数
  QString selectedDir=ui->loc->text();
      QDir dir(selectedDir);
      if(!dir.exists())
      {
         QMessageBox::information(this,"错误","保存失败，所填写的路径不存在");
          return;
     }else{
          static QRegularExpression re("\\");
          selectedDir = selectedDir.replace(re, "/");
          config->setValue("/SET/LOC",selectedDir);
          ui->loc->setText(selectedDir);
          emit setsuccess(selectedDir);
          this->close();

}
}

