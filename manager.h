#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"identity.h"
#include"globalFile.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include"computerRoom.h"
using namespace std;


class Manager : public Identity
{
public:
    Manager();  //默认构造

    Manager(string name, string pwd); //有参构造

    virtual void operMenu(); //菜单界面

    void addPerson(); //添加帐号

    void showPerson(); //查看帐号

    void showComputer(); //查看机房信息

    void cleanFile(); //清空预约记录

    void initVector();// 初始化容器
    vector<Student>vStu;
    vector<Teacher>vTea;
    bool checkRepeat(int id, int type); //检测重复
    vector<ComputerRoom>vCom;

};