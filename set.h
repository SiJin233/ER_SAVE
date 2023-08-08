#ifndef SET_H
#define SET_H

#include <QDialog>
#include<QFileDialog>
#include<QRegularExpression>
#include<QSettings>
#include<QMessageBox>

namespace Ui {
class set;
}

class set : public QDialog
{
    Q_OBJECT
signals:
    void setsuccess(QString);
private slots:
    void on_setcreate(QString,QWidget*);

    void on_choose_clicked();

    void on_save_clicked();

public:
    explicit set(QWidget *parent = nullptr);
    ~set();

private:
    Ui::set *ui;
};

#endif // SET_H
