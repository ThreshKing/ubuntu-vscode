#include<iostream>

using namespace std;

class Box
{
    public:
        double length;
        double breadth;
        double height;

        double getVolume(void);
        void setLength(double len);
        void setBreadth(double bre);
        void setHeigth(double hei);
};

double Box::getVolume(void)
{
    return length * breadth * height;
}

void Box::setLength(double len)
{
    length = len;
}
void Box::setBreadth(double bre)
{
    breadth = bre;
}
void Box::setHeigth(double hei)
{
    height = hei;
}


int main()
{
    Box Box1;
    Box Box2;
    Box Box3;
    double volume = 0.0;

    Box1.height = 5.0;
    Box1.length = 6.0;
    Box1.breadth = 7.0;

    Box2.height = 10.0;
    Box2.length = 12.0;
    Box2.breadth = 13.0;

    volume = Box1.height * Box1.breadth * Box1.length;
    cout << "Box1的体积： " << volume << endl;

    volume = Box2.height * Box2.breadth * Box2.length;
    cout << "Box2的体积： " << volume << endl;

    Box3.setLength(10.0);
    Box3.setBreadth(12.0);
    Box3.setHeigth(13.0);
    volume = Box3.getVolume();
    cout << "Box3的体积： " << volume << endl;

    return 0;
}