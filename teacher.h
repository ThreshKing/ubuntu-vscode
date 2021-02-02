#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<string>
#include"orderFile.h"
#include<vector>

class Teacher : public Identity
{
public:
    Teacher();  //默认构造

    Teacher(int empid, string name, string pwd); //有参构造

    virtual void operMenu(); //菜单界面

    void showAllOrder(); //查看所有预约

    void validOrder(); //审核预约

    int m_empId; //教师编号

};