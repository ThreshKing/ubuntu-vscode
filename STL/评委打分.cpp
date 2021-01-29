#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<algorithm>
#include<ctime>
using namespace std;

class Person  // 选手类
{
    public:
        Person(string name, int score)
        {
            this->m_Name = name;
            this->m_Score = score;
        }



        string m_Name;
        int m_Score;
};

void createPerson(vector<Person>&v)
{
    string nameSeed = "ABCDE";
    for(int i=0; i<5; i++)
    {
        string name = "选手";
        name +=nameSeed[i];

        int score = 0;

        Person p(name, score);

        v.push_back(p);
    }
}

void setScore(vector<Person>&v)
{
    for(vector<Person>::iterator it=v.begin(); it!=v.end(); it++)
    {
        //将评委的分数放入到deque容器中
        deque<int>d;
        for(int i=0; i<10; i++)
        {
            int score = rand() % 41 + 60;
            d.push_back(score);
        }

        cout << it->m_Name << "打分：" << " ";
        for(deque<int>::iterator dit=d.begin(); dit!=d.end(); dit++)
        {
            cout << *dit << " ";
        }
        cout << endl;

        //排序
        sort(d.begin(), d.end());

        //去除最高分和最低分
        d.pop_back();
        d.pop_front();

        //取平均分
        int sum = 0;
        for(deque<int>::iterator dit=d.begin(); dit!=d.end(); dit++)
        {
            sum += *dit;
        }

        int avg = sum / d.size();

        //将平均分配赋值到选手上
        it->m_Score = avg;
    }
}

void show(vector<Person>&v)
{
    for(vector<Person>::iterator it=v.begin(); it!=v.end(); it++)
    {
        cout << "姓名： " << (*it).m_Name << "     分数： " << (*it).m_Score << endl;
    }
}

int main()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    //1、创建5名选手
    vector<Person>v;
    createPerson(v);

    //2、给5名选手打分
    setScore(v);

    //3、显示最后得分
    show(v);

    return 0;
}
