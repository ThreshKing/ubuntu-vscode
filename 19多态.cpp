#include<iostream>

using namespace std;

class Shape
{
    public:
        Shape(int a=0, int b=0)
        {
            width = a;
            height = b;
        }
        virtual int area() = 0; //纯虚函数
    protected:
        int width;
        int height;
};

class Rectangle: public Shape
{
    public:
        Rectangle(int a=0, int b=0): Shape(a,b){}
        int area()
        {
            cout << "Rectangle class area: " << endl;
            return (width*height);
        } 
};

class Triangle: public Shape
{
    public:
        Triangle(int a=0, int b=0): Shape(a,b){}
        int area()
        {
            cout << "Triangle class area: " << endl;
            return (width*height/2);
        } 
};

int main()
{
    Shape *shape;
    Rectangle rec(10,7);
    Triangle tri(10,7);

    shape = &rec;
    shape->area();

    shape = &tri;
    shape->area();

    return 0;
}