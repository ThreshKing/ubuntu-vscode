#include"speechManager.h"


//构造函数
SpeechManager::SpeechManager()
{
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();
}

void SpeechManager::show_Menu()
{
    cout << "*********************************************" << endl;
    cout << "************  欢迎参加演讲比赛！  ***********"    << endl;
    cout << "************   1.开始演讲比赛    ************"   << endl;
    cout << "************   2.查看往届记录    ************"   << endl;
    cout << "************   3.清空比赛记录    ************"   << endl;
    cout << "************   0.退出比赛系统    ************"   << endl;
    cout << "*********************************************" << endl;
    cout << endl;
}

void SpeechManager::eixtSystem()
{
    cout << "欢迎下次使用"  << endl;
    exit(0);
}

void SpeechManager::pause()
{
    cout << "请按n键继续..." << endl;
    while (1)
    {
        std::string flag;
        cin >> flag;
        if (flag == "n")
        {
            break;
        }
    }
}

void SpeechManager::initSpeech()
{
    //容器都置空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();

    //初始化比赛轮数
    this->m_Index = 1;

    this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for(int i=0; i<nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;
        for(int j=0; j<2; j++)
        {
            sp.m_Score[j] = 0;
        } 

        this->v1.push_back(i + 10001);
        this->m_Speaker.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech()
{
    //第一轮开始比赛
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示晋级结果
    this->showScore();
    //第二轮开始比赛
    this->m_Index++;
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示最终结果
    this->showScore();
    //保存文件
    this->saveRecord();

    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();

    cout << "本届比赛完毕！" << endl;
    this->pause();
    system("clear");
}

void SpeechManager::speechDraw()
{
    cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
    cout << "----------------------" << endl;
    cout << "抽签后的顺序如下： " << endl;

    if(this->m_Index == 1)
    {
        //第一轮比赛
        random_shuffle(v1.begin(), v1.end());
        for(vector<int>::iterator it=v1.begin(); it!=v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        //第二轮比赛
        random_shuffle(v2.begin(), v2.end());
        for(vector<int>::iterator it=v2.begin(); it!=v2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
    this->pause();
}

void SpeechManager::speechContest()
{
    cout << "----------第" << this->m_Index <<"轮比赛正式开始-----------" << endl;

    multimap<double, int, greater<double>> groupScore; //准备临时容器 存放小组成绩
    int num = 0; //记录人员个数 6个人一组

    vector<int>v_Src; //比赛选手容器
    if(this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }

    //遍历
    for(vector<int>::iterator it=v_Src.begin(); it!=v_Src.end(); it++)
    {
        num ++;

        //评委打分
        deque<double>d;
        for(int i=0; i<10; i++)
        {
            double score = (rand() % 401 +600) / 10.f;
            //cout << score << " ";
            d.push_back(score);
        }
        //cout << endl;

        sort(d.begin(), d.end(), greater<double>());
        d.pop_front(); //去除最高分
        d.pop_back(); //去除最低分

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size(); //平均分

        //打印平均分
        //cout << "编号： " << *it << "  姓名： " << this->m_Speaker[*it].m_Name << "  获取平均分： " << avg << endl;

        //将平均分放入到map容器中
        this->m_Speaker[*it].m_Score[this->m_Index-1] = avg;
        //将打分数据 放入到临时小组容器中
        groupScore.insert(make_pair(avg, *it)); //key是得分， value是具体选手编号
        //每6人取出前三名
        if(num % 6 == 0)
        {
            cout << "第" << num/6 << "小组比赛名次： " << endl;
            for(multimap<double, int, greater<double>>::iterator it=groupScore.begin(); it!=groupScore.end(); it++)
            {
                cout << "编号： " << it->second << "姓名： " << this->m_Speaker[it->second].m_Name << "成绩： " 
                << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
            }

            int count = 0;
            for(multimap<double, int, greater<double>>::iterator it=groupScore.begin(); it!=groupScore.end() && count<3; it++, count++)
            {
                if(this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVictory.push_back((*it).second);
                }
                
            }
            groupScore.clear();
            cout << endl;
        }
    }

    cout << "----------------第" << this->m_Index << "轮比赛完毕！-----------" << endl;
    this->pause();
}

void SpeechManager::showScore()
{
    cout << "----------------第" << this->m_Index << "轮晋级选手如下：------------------- " << endl;
    vector<int>v;
    if(this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = vVictory;
    }
    
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++)
    {
        cout << "选手编号： " << *it << "姓名： " << this->m_Speaker[*it].m_Name << "得分： " << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;

    }
    cout << endl;
    this->pause();
}

void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);
    for(vector<int>::iterator it=vVictory.begin(); it!=vVictory.end(); it++)
    {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;
    ofs.close();
    cout << "记录已经保存" << endl;
    this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in);
    if(!ifs.is_open())
    {
        this->fileIsEmpty = true;
        //cout << "文件不存在" << endl;
        return;
    }
    
    //文件为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        //cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch);
    string data;
    int index = 1;  //第几届

    while(ifs >> data)
    {
        vector<string>v;
        int pos = -1; //查到逗号位置的变量
        int start = 0; 
        while(true)
        {
            pos = data.find(",", start);
            if(pos == -1)
            {
                //没有找到的情况
                break;
            }
            string temp = data.substr(start, pos-start);
            //cout << temp << endl;
            v.push_back(temp);
            start = pos+1;
        }
        this->m_Record.insert(make_pair(index, v));
        index++;
    }
    ifs.close();
}

void SpeechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
    else
    {
        for(map<int, vector<string>>::iterator it=m_Record.begin(); it!=m_Record.end(); it++)
        {
            cout << "------第" << it->first << "届比赛------" << endl; 
            cout << "冠军编号： " << it->second[0] << "  分数： " << it->second[1] << endl;
            cout << "亚军编号： " << it->second[2] << "  分数： " << it->second[3] << endl;
            cout << "季军编号： " << it->second[4] << "  分数： " << it->second[5] << endl;
        }       
    }
    
    this->pause();
    system("clear");
}

void SpeechManager::clearRecord()
{
    cout << "确认清空？" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;

    int select = 0;
    cin >> select;

    if(select == 1)
    {
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        this->initSpeech();
        this->createSpeaker();
        this->loadRecord();
        cout << "清空成功！" << endl;
    }
    this->pause();
    system("clear");
}

//析构函数
SpeechManager::~SpeechManager()
{

}

