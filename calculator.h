#pragma once
#include <string>
using namespace std;

typedef struct BI
{
    string num;
    int len;//数值位长度
    bool sig;//符号,真为正假为负
}BigInt, * pBigInt;



void add(BigInt& num1, BigInt& num2, BigInt& ans);
void sub(BigInt& num1, BigInt& num2, BigInt& ans);
int compare(const BigInt& num1, const BigInt& num2);
void trim(string& s);
bool isNum(string str);


