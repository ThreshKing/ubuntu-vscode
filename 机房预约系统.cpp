#include<iostream>
#include"identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
using namespace std;

//进入管理员的子菜单界面
void managerMenu(Identity * &manager)
{
    while(true)
    {
        //调用管理员子菜单
        manager->operMenu();

        //将父类指针转为子类指针，调用子类里其他接口
        Manager * man = (Manager*)manager;

        int select = 0;
        cin >> select;
        if(select == 1) //添加帐号
        {
            cout << "添加帐号" << endl;
            man->addPerson();
        }
        else if(select == 2) //查看帐号
        {
            cout << "查看帐号" << endl;
            man->showPerson();
        }
        else if(select == 3) //查看机房
        {
            cout << "查看机房" << endl;
            man->showComputer();
        }
        else if(select == 4) //清空预约
        {
            cout << "清空预约" << endl;
            man->cleanFile();
        }
        else
        {
            delete manager;
            cout << "注销成功" << endl;
            system("clear");
            return;
        }
    }
}

void studentMenu(Identity * &student)
{
    while(true)
    {
        student->operMenu();
        Student * stu = (Student*)student;

        int select = 0;
        cin >> select;
        if(select == 1) //申请预约
        {
            cout << "申请预约" << endl;
            stu->applyOrder();
        }
        else if(select == 2) //查看自身预约
        {
            cout << "查看自身预约" << endl;
            stu->showMyOrder();
        }
        else if(select == 3) //查看所有人预约
        {
            cout << "查看所有人预约" << endl;
            stu->showAllOrder();
        }
        else if(select == 4) //取消预约
        {
            cout << "取消预约" << endl;
            stu->cancelOrder();
        }
        else
        {
            delete student;
            cout << "注销成功" << endl;
            system("clear");
            return;
        }
        
    }
}

void teacherMenu(Identity * &teacher)
{
    while(true)
    {
        teacher->operMenu();
        Teacher * tea = (Teacher*)teacher;

        int select = 0;
        cin >> select;
        if(select == 1) //查看所有预约
        {
            cout << "查看所有预约" << endl;
            tea->showAllOrder();
        }
        else if(select == 2) //审核预约
        {
            cout << "审核预约" << endl;
            tea->validOrder();
        }
        
        else
        {
            delete teacher;
            cout << "注销成功" << endl;
            system("clear");
            return;
        }
        
    }
}

//登录功能
void LoginIN(string fileName, int type)
{
    Identity * person = NULL; //父类指针，用于指向子类对象

    ifstream ifs;
    ifs.open(fileName, ios::in);

    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    //准备接收用户信息
    int id = 0;
    string name;
    string pwd;

    if(type == 1) //学生身份
    {
        cout << "请输入你的学号: " << endl;
        cin >> id;
    }
    else if(type == 2) //学生身份
    {
        cout << "请输入您的职工号: " << endl;
        cin >> id;
    }

    cout << "请输入用户名： " << endl;
    cin >> name;

    cout << "请输入密码： " << endl;
    cin >> pwd;

    if(type == 1)
    {
        //文件中获取的信息
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "学生验证登录成功！" << endl;
                person = new Student(id, name, pwd);
                studentMenu(person);

                return;
            }
        }

    }
    else if(type == 2)
    {
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "教师验证登录成功！" << endl;
                person = new Teacher(id, name, pwd);
                teacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3)
    {
        string fName;
        string fPwd;
        while(ifs >> fName && ifs >> fPwd)
        {
            if(fName == name && fPwd == pwd)
            {
                system("clear");
                cout << "管理员验证登录成功！" << endl;
                person = new Manager(name, pwd);
                managerMenu(person);

                return;
            }
        }
    }
    cout << "验证登录失败！" << endl;


}

int main()
{
    int select = 0;

    while(true)
    {
        cout << "=======================欢迎来到机房预约系统======================" << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t----------------------------------------\n";
        cout << "\t\t|                                      |\n";
        cout << "\t\t|            1、学生代表               |\n";
        cout << "\t\t|                                      |\n";
        cout << "\t\t|            2、老    师               |\n";
        cout << "\t\t|                                      |\n";
        cout << "\t\t|            3、管 理 员               |\n";
        cout << "\t\t|                                      |\n";
        cout << "\t\t|            0、退    出               |\n";
        cout << "\t\t|                                      |\n";
        cout << "\t\t----------------------------------------\n";
        cout << "请输入您的选择：" << endl;
        
        cin >> select;
        switch(select)
        {
            case 1: //学生身份
                LoginIN(STUDENT_FILE, 1);
                break;
            case 2: //老师身份
                LoginIN(TEACHER_FILE, 2);
                break;
            case 3: //管理员身份
                LoginIN(ADMIN_FILE, 3);
                break;
            case 0: //退出系统
                cout << "欢迎下次使用" << endl;
                return 0;
                break;
            default:
                system("clear");
                cout << "输入有误，请重新选择！" << endl;
                break;    
        }
    }
    
    return 0;
}