#include "calculator.h"
#include <sstream>

void add(BigInt& num1, BigInt& num2, BigInt& ans)
{
    if (num1.sig == num2.sig)//两个数同号
    {
        int len_max = num1.len, len_min = num2.len;
        const BigInt* pmax = &num1;
        string temp1(num1.num.rbegin(), num1.num.rend());//利用反向迭代器将字符逆序 
        num1.num = temp1;
        string temp2(num2.num.rbegin(), num2.num.rend());
        num2.num = temp2;
        if (num1.len < num2.len) {
            len_max = num2.len;
            len_min = num1.len;
            pmax = &num2;
        }
        ans.sig = num1.sig;//结果的符号与两个num相同
        ans.num = "";
        ans.len = len_max;
        //从后往前计算
        int i = 0, int_num = 0, carry = 0;

        for (; i < len_min; i++) {
            int_num = ((int)num1.num.at(i) - 48) + ((int)num2.num.at(i) - 48) + carry;
            carry = 0;
            if (int_num > 9) {
                carry = int_num / 10;
                int_num = int_num % 10;
            }
            ans.num = ans.num + to_string(int_num);

        }
        for (; i < len_max; i++) {
            int_num = (int)pmax->num.at(i) - 48 + carry;
            carry = 0;
            if (int_num > 9) {
                carry = int_num / 10;
                int_num = int_num % 10;
            }
            ans.num = ans.num + to_string(int_num);
        }
        if (carry >= 1)
        {
            ans.num = ans.num + to_string(carry);
            ans.len = len_max + 1;
        }
        string temp3(ans.num.rbegin(), ans.num.rend());
        ans.num = temp3;
    }
    else
    {
        BigInt temp = num2;
        temp.sig = !num2.sig;
        sub(num1, temp, ans);

    }

}

void sub( BigInt& num1, BigInt& num2, BigInt& ans)
{
    if (num1.sig == num2.sig)
    {
        bool flag = compare(num1, num2) >= 0 ? true : false;
        string temp1(num1.num.rbegin(), num1.num.rend());//利用反向迭代器将字符逆序 
        num1.num = temp1;
        string temp2(num2.num.rbegin(), num2.num.rend());
        num2.num = temp2;
        const BigInt* pmax = &num1, * pmin = &num2;//pmax为绝对值大的num的指针 
        if (num1.sig == 1) {
            ans.sig = 1;//+大数在前为正，小数在前为负 ； 
        }
        else {
            ans.sig = 0;
        }
        if (!flag)
        {
            pmax = &num2;
            pmin = &num1;
            if (num1.sig == 1) {
                ans.sig = 0;//+大数在前为正，小数在前为负 ； 
            }
            else {
                ans.sig = 1;
            }
        }


        ans.num = "";
        //从后往前计算
        int i = 0, int_num = 0, borrow = 0;
        for (; i < pmin->len; i++) {
            int_num = ((int)pmax->num.at(i) - 48) - ((int)pmin->num.at(i) - 48) - borrow;
            borrow = 0;
            if (int_num < 0) {
                borrow = 1;
                int_num += 10;
            }
            ans.num = ans.num + to_string(int_num);

        }
        for (; i < pmax->len; i++) {
            int_num = (int)pmax->num.at(i) - 48 - borrow;
            borrow = 0;
            if (int_num < 0) {
                borrow = 1;
                int_num += 10;
            }
            ans.num = ans.num + to_string(int_num);
        }
        ans.len = ans.num.length();
        string temp3(ans.num.rbegin(), ans.num.rend());
        ans.num = temp3;
        for (int i = 0; i < ans.len - 1; i++) {
            if (ans.num.at(i) == '0') {
                ans.len--;
                ans.num = ans.num.replace(i, i + 1, "");
            }
            else {
                break;
            }
        }
    }
    else
    {
        BigInt temp = num2;
        temp.sig = !num2.sig;
        add(num1, temp, ans);
    }

}

void trim(string& s)//去除所有空格
{
    int index = 0;
    if (!s.empty())
    {
        while ((index = s.find(' ', index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

bool isNum(string str)//是否为纯整数
{
    //stringstream sin(str);
    //int d;
    //char c;
    //if (str.find(".") != std::string::npos)
    //    return false;
    //if (!(sin >> d))
    //    return false;
    //if (sin >> c)
    //    return false;
    //return true;
    for (int i = 0; i < str.size(); i++)
    {
        if ((str.at(i) > '9') || (str.at(i) < '0'))
        {
            return false;
        }
    }
    return true;
}

int compare(const BigInt& num1, const BigInt& num2)//a>b,return 1;a=b,return 0 a<b,return -1仅比较数值大小，忽略符号 
{
    if (num1.len != num2.len) {
        if (num1.len > num2.len) {
            return 1;
        }
        else if (num1.len < num2.len) {
            return -1;
        }
        else {
            return 0;
        }
    }
    else {
        for (int i = 0; i < num1.len; i++) {
            if (num1.num.at(i) > num2.num.at(i)) {
                return 1;
            }
            else if (num1.num.at(i) < num2.num.at(i)) {
                return -1;
            }
            else {
                return 0;
            }
        }

    }
    return 0;
}