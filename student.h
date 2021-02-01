#pragma once
#include<iostream>
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"
using namespace std;


class Student : public Identity
{
public:
    Student();  //默认构造

    Student(int id, string name, string pwd); //有参构造

    virtual void operMenu(); //菜单界面

    void applyOrder(); //申请预约

    void showMyOrder(); //查看我的预约

    void showAllOrder(); //查看所有预约

    void cancelOrder(); //取消预约

    int m_Id; //学号

    vector<ComputerRoom>vCom;


};