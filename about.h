#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include<QDesktopServices>
#include<QMouseEvent>
namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();
bool eventFilter(QObject *obj, QEvent *event);	// 添加时间过滤器声明
private:
    Ui::about *ui;
};

#endif // ABOUT_H
