#include<iostream>

using namespace std;

class Line
{
    public:
        double length;

        double getLength(void);
        void setLength(double len);
};

double Line::getLength(void)
{
    return length;
}

void Line::setLength(double len)
{
    length = len;
}

int main()
{
    Line line;
    
    //设置长度
    line.setLength(12.0);
    cout << "length of line： " << line.getLength() << endl;

    line.length = 10.0;
    cout << "length of line： " << line.length << endl;
    
    return 0;
}