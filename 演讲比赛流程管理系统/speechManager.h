#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include"speaker.h"
#include<fstream>
using namespace std;

//设计演讲比赛管理类
class SpeechManager
{
public:
    //构造函数
    SpeechManager();

    //展示菜单
    void show_Menu();

    //退出系统
    void eixtSystem();

    void pause(); //暂停窗口

    void initSpeech(); //初始化属性
    void createSpeaker(); //创建选手
    void startSpeech(); //开始比赛
    void speechDraw(); //抽签
    void speechContest(); //比赛
    void showScore(); //显示得分
    void saveRecord(); //保存记录
    void loadRecord(); //读取记录
    void showRecord(); //显示记录
    void clearRecord(); //清空
    
    //成员属性
    vector<int>v1; //保存第一轮比赛选手编号容器
    vector<int>v2; //第一轮晋级选手编号容器
    vector<int>vVictory; //胜出前三名选手编号容器
    map<int, Speaker>m_Speaker; //存放编号以及对应具体选手容器
    int m_Index; //存放比赛轮数
    bool fileIsEmpty;
    map<int, vector<string>>m_Record; //存放往届记录的容器


    //析构函数
    ~SpeechManager();
};