#include<iostream>

using namespace std;

class Shape
{
    public:
        virtual int area() = 0; //纯虚函数
        void setWidth(int w)
        {
            width = w;
        }
        void setHeight(int h)
        {
            height = h;
        }
    protected:
        int width;
        int height;
};

class Rectangle: public Shape
{
    public:
        int area()
        {
            return (width*height);
        } 
};

class Triangle: public Shape
{
    public:
        int area()
        {
            return (width*height/2);
        } 
};

int main()
{
    Rectangle rec;
    Triangle tri;

    rec.setWidth(5);
    rec.setHeight(7);
    cout << "Total Rectangle area: " << rec.area() << endl;

    tri.setWidth(5);
    tri.setHeight(7);
    cout << "Total Triangle area: " << tri.area() << endl;

    return 0;
}