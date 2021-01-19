#include<iostream>

using namespace std;

class Box
{
    private:
        double length;
        double breadth;
        double height;
    public:
        double getVolume(void);
        void setLength(double len);
        void setBreadth(double bre);
        void setHeigth(double hei);
        Box operator+(const Box& b)
        {
            Box box;
            box.length = this->length + b.length;
            box.breadth = this->breadth + b.breadth;
            box.height = this->height + b.height;
            return box;
        }
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

    Box1.setLength(6.0);
    Box1.setBreadth(7.0);
    Box1.setHeigth(5.0);
    volume = Box1.getVolume();
    cout << "Box1的体积： " << volume << endl;

    Box2.setLength(12.0);
    Box2.setBreadth(13.0);
    Box2.setHeigth(10.0);
    volume = Box2.getVolume();
    cout << "Box2的体积： " << volume << endl;

    Box3 = Box1 + Box2;
    volume = Box3.getVolume();
    cout << "Box3的体积： " << volume << endl;

    return 0;
}