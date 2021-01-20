#include<iostream>

using namespace std;

class Box
{
    protected:
        double width;
};

class SmallBox:Box
{
    public:
        void setSmallWidth(double wid);
        double getSmallWidth(void);
};

double SmallBox::getSmallWidth(void)
{
    return width;
}

void SmallBox::setSmallWidth(double wid)
{
    width = wid;
}

int main()
{
    SmallBox box;
    
    //设置长度
    box.setSmallWidth(15.0);
    cout << "width of line： " << box.getSmallWidth() << endl;
    
    return 0;
}