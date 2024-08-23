#ifndef TIPS_H
#define TIPS_H

#include <QWidget>
#include<QPixmap>

namespace Ui {
class tips;
}

class tips : public QWidget
{
    Q_OBJECT

public:
    explicit tips(QWidget *parent = nullptr);
    void ShowTips();
    ~tips();

private:
    Ui::tips *ui;

protected:
    void closeEvent(QCloseEvent *event);
signals:
    void back();
};

#endif // TIPS_H
