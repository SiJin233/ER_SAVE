#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
        ui->link->installEventFilter(this);    // 安装事件过滤器

}

about::~about()
{
    delete ui;
}

bool about::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->link)//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

            if(mouseEvent->button() == Qt::LeftButton)
            {
                 QDesktopServices::openUrl(QUrl(QString("https://github.com/SiJin233/ER_SAVE")));
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


