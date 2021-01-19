#include<iostream>

using namespace std;

class Box
{
    public:
        double length;
        double getWidth(void);
        void setWidth(double wid);
    private:
        double width;
};

double Box::getWidth(void)
{
    return width;
}

void Box::setWidth(double wid)
{
    width = wid;
}

int main()
{
    Box box;
    
    //设置长度
    box.length = 12.0;
    cout << "length of line： " << box.length << endl;

    //box.width = 10.0;
    box.setWidth(15.0);
    cout << "width of line： " << box.getWidth() << endl;
    
    return 0;
}