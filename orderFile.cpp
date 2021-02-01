#include"orderFile.h"


void string2map(string &s, map<string, string> &m)
{
    string key;
    string value;
    int pos = s.find(":");
    if(pos != -1)
        {
            key = s.substr(0, pos);
            value = s.substr(pos+1, s.size()-pos-1);
            m.insert(make_pair(key, value));
        }
}
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;

    this->m_Size = 0;
    while(ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        string key;
        string value;
        map<string, string> m;
        string2map(date, m);
        string2map(interval, m);
        string2map(stuId, m);
        string2map(stuName, m);
        string2map(roomId, m);
        string2map(status, m);
        this->m_OrderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;    
    }
    ifs.close();
    // for(map<int, map<string, string>>::iterator it=m_OrderData.begin(); it!=m_OrderData.end(); it++)
    // {
    //     cout << "记录条数为 = " << it->first << "value = " << endl;
    //     for(map<string, string>::iterator mit=(*it).second.begin(); mit!=(*it).second.end(); mit++)
    //     {
    //         cout << " key = " << mit->first << " value = " << mit->second << " ";
    //     }
    //     cout << endl;
    // }
}

void OrderFile::updateOrder()
{
    if(this->m_Size == 0)
    {
        return;
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    for(int i=0; i<m_Size; i++)
    {
        ofs << "date:" << this->m_OrderData[i]["date"] << " ";
        ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_OrderData[i]["status"] << endl;
    }
}