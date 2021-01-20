#include "workerManager.h"

WorkerManager::WorkerManager()
{
    
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    //1、文件不存在
    if(!ifs.is_open())
    {
        //cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //2、文件存在，但数据为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        //cout << "文件为空！" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //3、文件存在且有数据
    int num = this->get_EmpNum();
    //cout << "职工人数为： " << num << endl;
    this->m_EmpNum = num;
    this->m_FileIsEmpty = false;

    this->m_EmpArray = new Worker*[this->m_EmpNum];
    this->init_Emp();
    
    //测试代码
    // for(int i=0; i<this->m_EmpNum; i++)
    // {
    //     cout << "职工编号： " << this->m_EmpArray[i]->m_Id << "    "
    //          << "职工姓名： " << this->m_EmpArray[i]->m_Name << "    "
    //          << "岗位： " << this->m_EmpArray[i]->m_DeptId << endl;
    // }
    
}

void WorkerManager::Show_Menu()
{
    cout << "*********************************************" << endl;
    cout << "************欢迎使用职工管理系统！***********"    << endl;
    cout << "************   0.退出管理程序    ************"   << endl;
    cout << "************   1.增加职工信息    ************"   << endl;
    cout << "************   2.显示职工信息    ************"   << endl;
    cout << "************   3.删除离职职工    ************"   << endl;
    cout << "************   4.修改职工信息    ************"   << endl;
    cout << "************   5.查找职工信息    ************"   << endl;
    cout << "************   6.按照编号排序    ************"   << endl;
    cout << "************   7.清空所有文档    ************"   << endl;
    cout << "*********************************************" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(0);
}

void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工数量： " << endl;

    int addNum = 0; //保存用户的输入数量
    cin >> addNum;

    if(addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum; //新空间人数 = 原来记录的人数 + 新增人数

        Worker ** newSpace = new Worker*[newSize]; //开辟新空间

        if(this->m_EmpArray != NULL) //将原来空间下的数据，拷贝到新空间下
        {
            for(int i=0; i<this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        for(int i=0; i<addNum; i++) //批量添加新数据
        {
            int id;
            string name;
            int dSelect;

            cout << "请输入第" << i+1 << "个新职工编号： " << endl;
            cin >> id;
            cout << "请输入该职工姓名： " << endl;
            cin >> name;
            cout << "请选择该职工岗位： " << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、总裁" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3:
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
            }

            newSpace[this->m_EmpNum + i] = worker; //将创建的员工保存到数组中
        }  

        delete[] this->m_EmpArray; //释放原有空间
        this->m_EmpArray = newSpace; //更改新空间的指向
        this->m_EmpNum = newSize; //更新新的职工人数

        //成功添加后，保存到文件中
        this->save();

        //更新职工不为空的标志
        this->m_FileIsEmpty = false;

        cout << "成功添加了" << addNum << "名新职工！" << endl; 
    }
    else
    {
        cout << "输入有误！" << endl;
    }

    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
    
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //写文件
    
    for(int i=0; i<this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int num = 0;

    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }
    return num;
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int index = 0;

    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker * worker = NULL;

        if(dId == 1) //普通员工
        {
            worker = new Employee(id, name, dId);
        }
        else if(dId == 2) //经理
        {
            worker = new Manager(id, name, dId); 
        }
        else //总裁
        {
            worker = new Boss(id, name, dId);
        }

        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}

void WorkerManager::Show_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl;
    }
    else
    {
        for(int i=0; i<this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo(); //利用多态调用程序接口
        }
    }
    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
}

int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i=0; i<this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl; 
    }
    else
    {
        cout << "请输入想要删除职工编号： " << endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);
        if(index != -1) //说明职工存在，并删掉index位置上的员工
        {
            for(int i=index; i<this->m_EmpNum-1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1]; //数据前移
            }
            this->m_EmpNum--; //更新数组中记录人员的个数
            this->save(); //数据同步更新到文件中

            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
         
    }
    
    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
}

void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl; 
    }
    else
    {
        cout << "请输入想要修改职工编号： " << endl;
        int id = 0;
        cin >> id;

        int ret = this->IsExist(id);
        if(ret != -1) //说明职工存在
        {
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
            cin >> newId;
            cout << "请输入新姓名： " << endl;
            cin >> newName;
            cout << "请输入新岗位： " << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、总裁" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(newId, newName, 1);
                    break;
                case 2:
                    worker = new Manager(newId, newName, 2);
                    break;
                case 3:
                    worker = new Boss(newId, newName, 3);
                    break;
                default:
                    break;
            }

            this->m_EmpArray[ret] = worker; //更新数据到数组中

            cout << "修改成功！" << endl;
            this->save();
        }
        else
        {
            cout << "修改失败，未找到该职工" << endl;
        }
         
    }
    
    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
}

void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl; 
    }
    else
    {
        cout << "请输入查找的方式： " << endl;
        cout << "1、按照职工的编号查找 " << endl;
        cout << "2、按照职工的姓名查找" << endl;

        int select = 0;
        cin >> select;

        if(select == 1)
        {
            int id;
            cout << "请输入职工的编号： " << endl;
            cin >> id;

            int ret = IsExist(id);
            if(ret != -1)
            {
                cout << "查找成功，该职工信息如下： " << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查找失败，未找到该职工" << endl;
            }
            
        } 
        else if(select == 2)
        {
            string name;
            cout << "请输入职工的姓名： " << endl;
            cin >> name;
            bool flag = false; //是否查到的标志

            for(int i=0; i<this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功，职工编号为" << this->m_EmpArray[i]->m_Id << "号的职工信息如下： " << endl;
                    flag = true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if(flag == false)
                {
                    cout << "查找失败，未找到该职工" << endl;
                }
        }
        else
        {
            cout << "输入选项有误，请重新输入" << endl;
        }
        
    }
    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
}

void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空！" << endl;
        // //按任意键后，清屏回到上级目录
        // pause();
        // system("clear");
    }
    else
    {
        cout << "请选择排序方式： " << endl;
        cout << "1、按照职工号进行升序" << endl;
        cout << "2、按照职工号进行降序" << endl;

        int sselect = 0;
        cin >> sselect;

        for(int i=0; i<this->m_EmpNum; i++)
        {
            int minOrMax = i; //声明最小值或最大值下标
            for(int j=i+1; j<this->m_EmpNum; j++)
            {
                if(sselect == 1) //升序 
                {
                    if(this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else
                {
                    if(this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }  
            }
            // 判断一开始认定的最小值或最大值是不是计算的最小值或最大值，如果不是，交换数据
            if(i != minOrMax)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }

        cout << "排序成功！排序后的结果为： " << endl;
        this->save();
        this->Show_Emp();
    }
}

void WorkerManager::Clean_File()
{
    cout << "确定清空？" << endl;
    cout << "1、确定" << endl;
    cout << "2、返回" << endl;

    int sselect = 0;
    cin >> sselect;

    if(sselect == 1)
    {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            //删除堆区的每个职工对象
            for (int i=0; i<this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;

            //删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功!" << endl;
        
    } 
    // //按任意键后，清屏回到上级目录
    // pause();
    // system("clear");
}

WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray != NULL)
    {
        for (int i=0; i<this->m_EmpNum; i++)
        {
            if(this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}