#include"employee.h"

Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

void Employee::showInfo() //显示个人信息
{
    cout << "职工编号： " << this->m_Id << "    ";
    cout << "职工姓名： " << this->m_Name << "    ";
    cout << "岗位： " << this->getDeptName() << "    ";
    cout << "岗位职责： 完成经理布置的任务" << endl;
} 
        
string Employee::getDeptName() //获取岗位名称
{
    return string("员工");
}