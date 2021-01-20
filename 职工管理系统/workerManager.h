#pragma once
#include<iostream>
#include<unistd.h>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager
{
    public:
        WorkerManager(); //构造函数

        int m_EmpNum; //记录职工人数
        Worker ** m_EmpArray; //职工数组指针
        bool m_FileIsEmpty; //判断文件是否为空 标志

        void Show_Menu(); //展示菜单
        void ExitSystem(); //退出系统
        void Add_Emp(); //添加职工
        void save(); //保存文件
        int get_EmpNum(); //获取文件中人数
        void init_Emp(); //初始化职工
        void Show_Emp(); //显示员工
        void Del_Emp(); //删除员工
        int IsExist(int id); //判断员工是否存在 如果存在返回职工所在数组中的位置，不存在返回-1
        void Mod_Emp(); //修改职工
        void Find_Emp(); //查找职工
        void Sort_Emp(); //排序职工
        void Clean_File(); //清空文件

        ~WorkerManager(); //析构函数
};
