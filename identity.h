#pragma once
#include<iostream>
using namespace std;

class Identity
{
public:
    //操作菜单
    virtual void operMenu() = 0;
    //姓名
    string m_Name;
    //密码
    string m_Pwd;
};