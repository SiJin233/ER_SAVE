#include "er_save.h"
#include "ui_er_save.h"


er_save::er_save(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::er_save)
{
    ui->setupUi(this);

    sb=new QStatusBar;
    ui->test->addWidget(sb);
    sb->setSizeGripEnabled(false);
    QFont font;
    font.setPixelSize(15);
    sb->setFont(font);
    sb->showMessage("欢迎使用");


    ui->set->installEventFilter(this);    // 安装事件过滤器
    ui->about->installEventFilter(this);    // 安装事件过滤器
   contextMenu = new QMenu;
    QAction* action = contextMenu->addAction("备注");
     ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->list, &QListView::customContextMenuRequested, this, &er_save::showContextMenu);


    config = new QSettings (QDir::homePath()+"/AppData/Roaming/EldenRing/ER_SAVE/config.ini", QSettings::IniFormat);//构建函数.参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
    loc=config->value("/SET/LOC").toString();
    if(loc==""){
        loc=QDir::homePath()+"/AppData/Roaming/EldenRing/ER_SAVE";
        config->setValue("/SET/LOC",loc);
    }else{
        QDir dir(loc);
        if(!dir.exists())
        {
            loc=QDir::homePath()+"/AppData/Roaming/EldenRing/ER_SAVE";
            config->setValue("/SET/LOC",loc);
        }
    }
refresh();

    newnotes=new notes;
    connect(this,SIGNAL(notescreate(QString,QWidget*)),newnotes,SLOT(on_notescreate(QString,QWidget*)));
    connect(action, &QAction::triggered, this, [=]() {
          emit notescreate(loc+"/"+ui->list->currentItem()->text(),this);
          newnotes->show();
      });



    newset=new set;
    connect(this,SIGNAL(setcreate(QString,QWidget*)),newset,SLOT(on_setcreate(QString,QWidget*)));



}


er_save::~er_save()
{
    delete ui;
}

void er_save::showContextMenu(const QPoint& pos) {
    contextMenu->exec(QCursor::pos());
}

void er_save::refresh()
{
    ui->list->clear();
    QDir dir(loc);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList folders2=dir.entryList();
    ui->list->addItems(folders2);
    ui->time->setText(folders2[folders2.size()-1]);
}

void er_save::on_setsuccess(QString temploc)
{
    loc=temploc;
}

void er_save::on_notessuccess(QString notes)
{
   sb->showMessage(notes);
}


bool DirExistEx(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkdir(fullPath);
        return ok;
    }
}

//事件过滤器
bool er_save::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->set)//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

            if(mouseEvent->button() == Qt::LeftButton)
            {
                emit setcreate(loc,this);
                newset->show();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
        if (obj == ui->about)//指定某个QLabel
        {
            if (event->type() == QEvent::MouseButtonPress) //鼠标点击
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

                if(mouseEvent->button() == Qt::LeftButton)
                {
                    newabout=new about;
                    newabout->show();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(obj, event);
    }
}

void er_save::on_pushButton_2_clicked()
{

    QDir dir(QDir::homePath()+"/AppData/Roaming/EldenRing/");
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    //    QStringList folders;
    //    QFileInfoList fileList = dir.entryInfoList();
    //    for (int i = 0; i < fileList.size(); ++i) {
    //        QFileInfo fileInfo = fileList.at(i);
    //        folders.append(fileInfo.fileName());
    //    }
    QStringList folders2=dir.entryList();
    QString waitsavefolder;
    for (int i = 0; i < folders2.size(); i++) {
        // 获取字符串匹配结果
        QRegularExpression re("[0-9]{15,}");
        QRegularExpressionMatch match = re.match(folders2[i]);
        if (match.hasMatch()) {
            waitsavefolder = match.captured(0);
            break;
        }

    }

    dir.setPath(QDir::homePath()+"/AppData/Roaming/EldenRing/"+waitsavefolder);
    dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
    QStringList waitsave=dir.entryList();;
    QString savetime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh_mm_ss");
    DirExistEx(loc+"/"+savetime+"/");
    for (int i = 0; i <  waitsave.size(); i++)
    {
        QString originFilePath =QDir::homePath()+"/AppData/Roaming/EldenRing/"+waitsavefolder+"/"+waitsave[i];
        //qDebug()<<"originFilePath=="<<originFilePath;
        QString destFilePath =loc+"/"+savetime +"/"+waitsave[i];
        // qDebug()<<"destFilePath=="<<destFilePath;
        //             //如果已经存在，则删除原来的文件
        //             if(QFile::exists(destFilePath))
        //             {
        //               QFile::remove(destFilePath);
        //             }
        //开始复制
        QFile::copy(originFilePath,destFilePath);

    }
    refresh();
    sb->showMessage("最新存档备份成功！");
}




void er_save::on_del_clicked()
{
    if(ui->list->selectedItems().empty())
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "警告",  "确定删除"+ui->list->currentItem()->text()+"的存档吗?",
                                  QMessageBox::Yes | QMessageBox::No);

    // 判断用户的选择
    if (reply == QMessageBox::Yes) {
        QDir dir(loc+"/"+ui->list->currentItem()->text());
        dir.removeRecursively();
        sb->showMessage(ui->list->currentItem()->text()+"的存档删除成功！");
        refresh();
        return ;
    }

    else
    {
        return ;
    }
}


void er_save::on_restore_clicked()
{
    if(ui->list->selectedItems().empty())
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "警告",  "确定恢复"+ui->list->currentItem()->text()+"的存档吗？（当前正在使用的存档将会消失！）",
                                  QMessageBox::Yes | QMessageBox::No);

    // 判断用户的选择
    if (reply == QMessageBox::Yes) {

        QDir dir(QDir::homePath()+"/AppData/Roaming/EldenRing/");
        dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        QStringList folders2=dir.entryList();
        QString waitsavefolder;
        for (int i = 0; i < folders2.size(); i++) {
            // 获取字符串匹配结果
            QRegularExpression re("[0-9]{15,}");
            QRegularExpressionMatch match = re.match(folders2[i]);
            if (match.hasMatch()) {
                waitsavefolder = match.captured(0);
                break;
            }

        }
        QString savetime=ui->list->currentItem()->text();
        dir.setPath(loc+"/"+savetime);
        dir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
        QStringList waitsave=dir.entryList();;

        for (int i = 0; i <  waitsave.size(); i++)
        {
            QString originFilePath =loc+"/"+savetime +"/"+waitsave[i];
            qDebug()<<"originFilePath=="<<originFilePath;
            QString destFilePath =QDir::homePath()+"/AppData/Roaming/EldenRing/"+waitsavefolder+"/"+waitsave[i];
          qDebug()<<"destFilePath=="<<destFilePath;
                         //如果已经存在，则删除原来的文件
                         if(QFile::exists(destFilePath))
                         {
                           QFile::remove(destFilePath);
                         }
            QFile::copy(originFilePath,destFilePath);
        }
        sb->showMessage(ui->list->currentItem()->text()+"的存档恢复成功！");
        refresh();
         return ;
    }

    else
    {
        return ;
    }



}



void er_save::on_list_clicked(const QModelIndex &index)
{
    QSettings* config = new QSettings (loc+"/"+index.data().toString()+"/notes.ini", QSettings::IniFormat);//构建函数.参数：参数一为配置文件，一般位于项目文件下，参数二表示针对ini文件格式
     sb->showMessage(config->value("/NOTES/CONTENT").toString());
}

