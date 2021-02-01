#include "manager.h"

Manager::Manager()  //默认构造
{

}

Manager::Manager(string name, string pwd) //有参构造
{
    //初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器
    this->initVector();

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    ComputerRoom com;
    while(ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
}

void Manager::operMenu() //菜单界面
{
    cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t----------------------------------------\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t|            1、添加帐号               |\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t|            2、查看帐号               |\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t|            3、查看机房               |\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t|            4、清空预约               |\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t|            0、注销登录               |\n";
    cout << "\t\t|                                      |\n";
    cout << "\t\t----------------------------------------\n";
    cout << "请输入您的选择：" << endl;
}

void Manager::addPerson() //添加帐号
{
    cout << "请输入添加帐号的类型" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加教师" << endl; 

    string fileName; //操作文件名
    string tip; //提示id号
    string errorTip;//错误提示

    ofstream ofs;
    int select = 0;
    cin >> select;
    if(select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号： ";
        errorTip = "学号重复，请重新输入";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工编号： ";
        errorTip = "职工号重复，请重新输入";
    }
    ofs.open(fileName, ios::out | ios:: app);

    int id;
    string name;
    string pwd;
    
    cout << tip << endl;
    while(true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if(ret)
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
        
    }
    cout << "请输入姓名： " << endl;
    cin >> name;
    cout << "请输入密码： " << endl;
    cin >> pwd;

    //向文件中添加数据
    ofs << id << " " << name << " " << pwd << endl;
    cout << "添加成功" << endl;
    ofs.close();

    this->initVector();
}

void printStudent(Student &s)
{
    cout << "学号： " << s.m_Id << "  姓名： " << s.m_Name << "  密码： " << s.m_Pwd << endl;
}
void printTeacher(Teacher &t)
{
    cout << "职工号： " << t.m_empId << "  姓名： " << t.m_Name << "  密码： " << t.m_Pwd << endl;
}
void Manager::showPerson() //查看帐号
{
    cout << "请选择查看内容" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int select = 0;
    cin >> select;
    if(select == 1)
    {
        cout << "所有学生信息如下： " << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else
    {
        cout << "所有教师信息如下： " << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
}

void Manager::showComputer() //查看机房信息
{
    cout << "机房信息如下： " << endl;
    for(vector<ComputerRoom>::iterator it=vCom.begin(); it!=vCom.end(); it++)
    {
        cout << "机房编号： " << it->m_ComId << "  机房最大容量： " << it->m_MaxNum << endl;
    }
}

void Manager::cleanFile() //清空预约记录
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();
    cout << "清空成功！" << endl;
}

void Manager::initVector() //初始化容器
{
    vStu.clear();
    vTea.clear();

    ifstream ifs;
    //读取学生信息
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "文件读取失败！" << endl;
        return;
    }
    Student s;
    while(ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }
    cout << "当前学生数量为： " << vStu.size() << endl;
    ifs.close();

    //读取老师信息
    ifs.open(TEACHER_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "文件读取失败！" << endl;
        return;
    }
    Teacher t;
    while(ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "当前老师数量为： " << vTea.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
    if(type == 1)
    {
        for(vector<Student>::iterator it=vStu.begin(); it!=vStu.end(); it++)
        {
            if(id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        for(vector<Teacher>::iterator it=vTea.begin(); it!=vTea.end(); it++)
        {
            if(id == it->m_empId)
            {
                return true;
            }
        }
    }
    return false;
}