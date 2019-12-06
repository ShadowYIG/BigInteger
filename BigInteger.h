#pragma once
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include <QtWidgets/QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include "ui_BigInteger.h"
#include "calculator.h"

class BigInteger : public QMainWindow
{
	Q_OBJECT

public:
	BigInteger(QWidget *parent = Q_NULLPTR);
    

private slots:
    void btn_rand1_click();
    void btn_rand2_click();
    void btn_cal_click();

private:
	Ui::BigIntegerClass ui;
    QString get_rand_num_text();
    bool BigInteger::get_text_num(QString& qstr_num, BigInt& big_num);

};

