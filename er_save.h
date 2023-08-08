#ifndef ER_SAVE_H
#define ER_SAVE_H

#include <QWidget>
#include <QMouseEvent>
#include<QDir>
#include <QSettings>
#include<QDateTime>
#include <QStatusBar>
#include<QMessageBox>
#include<QMenu>
#include"set.h"
#include<QListWidgetItem>
#include"notes.h"
#include"about.h"
QT_BEGIN_NAMESPACE
namespace Ui { class er_save; }
QT_END_NAMESPACE

class er_save : public QWidget
{
    Q_OBJECT
signals:
    void setcreate(QString,QWidget*);
    void notescreate(QString,QWidget*);
private slots:
    void on_setsuccess(QString);
    void on_notessuccess(QString);
public:
    set *newset;
   notes *newnotes;
     about *newabout;
    QString loc;
    void refresh();

bool eventFilter(QObject *obj, QEvent *event);	// 添加时间过滤器声明
    er_save(QWidget *parent = nullptr);
    ~er_save();

private slots:
    void on_pushButton_2_clicked();

    void on_del_clicked();

    void on_restore_clicked();

    void on_list_clicked(const QModelIndex &index);

private:
     void showContextMenu(const QPoint& pos);
     QStatusBar* sb;
    Ui::er_save *ui;
     QSettings *config;//申明一个QSetting类函数
     QMenu *contextMenu;
};
#endif // ER_SAVE_H
