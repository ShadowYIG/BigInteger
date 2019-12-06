#include "BigInteger.h"
#include "calculator.h"
#include "mytime.h"
#include <cstdlib>
#include<ctime>
#include<iostream>
#include<ctime>

BigInteger::BigInteger(QWidget *parent)
	: QMainWindow(parent)
{
    //QLabel* usetime = new QLabel(this);
    //ui.statusBar->addWidget(usetime);
    //ui.statusBar->addPermanentWidget(usetime);
	ui.setupUi(this);
}

void BigInteger::btn_rand1_click()
{
    QString num_text = get_rand_num_text();
    if (num_text != "") {
        ui.text_num1->setPlainText(num_text);
    }
    


}

void BigInteger::btn_rand2_click()
{
    QString num_text = get_rand_num_text();
    if (num_text != "") {
        ui.text_num2->setPlainText(num_text);
    }

}

void BigInteger::btn_cal_click()
{
    MyTimer timer;
    timer.Start();
    BigInt big_num1, big_num2, big_ans;
    QString text_num1 = ui.text_num1->toPlainText();
    QString text_num2 = ui.text_num2->toPlainText();
    QString Qstr_sig="";
    ui.text_res->setPlainText(text_num2);
    if (text_num1!="" && text_num2 != "") {
        if (!BigInteger::get_text_num(text_num1, big_num1))
            return;
        if (!BigInteger::get_text_num(text_num2, big_num2))
            return;
        
        //ui.statusBar->showMessage(QString::fromStdString(big_num2.num)+ QString::number(big_num2.len)+ QString::number(big_num2.sig)+
        //    QString::fromStdString(big_num1.num) + QString::number(big_num1.len) + QString::number(big_num1.sig), 1000000);
        if (ui.com_op->currentText() == "+") {
            add(big_num1, big_num2, big_ans);
            if (big_ans.sig == 0) {
                Qstr_sig = "-";
            }
            else {
                Qstr_sig = "";
            }
            ui.text_res->setPlainText(Qstr_sig + QString::fromStdString(big_ans.num));
        }
        else {
            sub(big_num1, big_num2, big_ans);
            if (big_ans.sig == 0) {
                Qstr_sig = "-";
            }
            else {
                Qstr_sig = "";
            }
            ui.text_res->setPlainText(Qstr_sig + QString::fromStdString(big_ans.num));
        }
        
    }
    else {
        QString dlgTitle = "输入错误";
        QString strInfo = "两个整数不能为空";
        QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
    }
    timer.End();
    ui.statusBar->showMessage(QString::fromStdString("运行耗时:") + QString::number(timer.costTime/1000.0, 10, 5)+ QString::fromStdString("ms"), 120000);
}


QString BigInteger::get_rand_num_text()
{
    //输入随机整数
    QString dlgTitle = "输入位数";
    QString txtLabel = "请输入生成随机位数";
    int defaultValue = 9;
    int minValue = 1, maxValue = 500, stepValue = 1; //范围，步长
    bool ok = false;
    int inputValue = QInputDialog::getInt(this, dlgTitle, txtLabel, defaultValue, minValue, maxValue, stepValue, &ok);
    QString old_text = "";
    int temp_int = 0;
    if (ok) //是否确认输入
    {
        //ui.text_num1->setPlainText("");
        srand((int)time(0));
        for (int i = 0; i < inputValue; i++)
        {
            //QString old_text = ui.text_num1->toPlainText();
            //ui.text_num1->setPlainText(old_text + QString::number(rand() % 10));
            temp_int = rand() % 10;
            
            while(i == 0 && temp_int == 0) {
                temp_int = rand() % 10;
            }
            old_text = old_text + QString::number(temp_int);
        }

    }
    return old_text;
}

bool BigInteger::get_text_num(QString& qstr_num, BigInt& big_num)
{
    string str_num = qstr_num.toStdString();
    trim(str_num);
    int str_len = str_num.length();
    if (str_num.find('-') != string::npos &&  str_num.find('-') != str_num.rfind('-') || 
        str_num.find('+') != string::npos && str_num.find('+') != str_num.rfind('+') ||
        str_num.find('-') != string::npos && str_num.find('+') != string::npos) // 不能同一个输入框有两个符号
    {
        QString dlgTitle = "输入错误";
        QString strInfo = "不能在同一个输入框内输入两个符号";
        QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
        return false;
    }
    else
    {
        int index = -1;
        if ((index=str_num.find('-')) != string::npos) {
            if (index != 0) {
                QString dlgTitle = "输入错误";
                QString strInfo = "符号必须在最开头";
                QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                return false;
            }
            str_num = str_num.replace(index, index + 1, "");
            if (!isNum(str_num)) {
                QString dlgTitle = "输入错误";
                QString strInfo = "请输入整数";
                QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                return false;
            }
            if (str_num.at(0) == '0') {
                QString dlgTitle = "输入错误";
                QString strInfo = "数字开头不能为0";
                QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                return false;
            }
                
            big_num.len = str_len - 1;
            big_num.num = str_num;
            big_num.sig = false;
        }
        else {

            index = -1;
            if ((index = str_num.find('+')) != string::npos) {
                if (index != 0) {
                    QString dlgTitle = "输入错误";
                    QString strInfo = "符号必须在最开头";
                    QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                    return false;
                }
                str_num = str_num.replace(index, index + 1, "");
                big_num.len = str_len - 1;
            }

            else {
                big_num.len = str_len;
            }
            if (!isNum(str_num)) {
                QString dlgTitle = "输入错误";
                QString strInfo = "请输入整数";
                QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                return false;
            }
            if (str_num.at(0) == '0') {
                QString dlgTitle = "输入错误";
                QString strInfo = "数字开头不能为0";
                QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
                return false;
            }
            big_num.num = str_num;
            big_num.sig = true;

        }
        

    }

    //int str_len_pre = str_num.length();
    //int index = -1;
    //if ((index = str_num.find('-')) != string::npos && index>=0) {
    //    str_num = str_num.replace(index,index+1,"");
    //}
    //index = -1;
    //if ((index = str_num.find('+')) != string::npos && index >= 0) {
    //    str_num = str_num.replace(index, index + 1, "");
    //}
    //if (str_num.length() != str_len_pre) {
    //   QString dlgTitle = "输入错误";
    //   QString strInfo = "不能在同一个输入框内输入两个符号";
    //   QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
    //}
    return true;
}

