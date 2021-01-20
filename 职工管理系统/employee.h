#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;

class Employee :public Worker
{
    public:
        Employee(int id, string name, int dId);

        virtual void showInfo(); //显示个人信息
        virtual string getDeptName(); //获取岗位名称
        
};