#include<iostream>

using namespace std;

class Line
{
    public:
        int getLength();
        Line(int len);
        Line(const Line &obj);
        ~Line();
    private:
        int *ptr;
};

Line::Line(int len)
{
    cout << "调用构造函数" << endl;
    ptr = new int;
    *ptr = len;
}

Line::Line(const Line &obj)
{
    cout << "调用拷贝构造函数并为指针ptr分配内存" << endl;
    ptr = new int;
    *ptr = *obj.ptr;
}

Line::~Line(void)
{
    cout << "释放内存" << endl;
    delete ptr;
}

int Line::getLength(void)
{
    return *ptr;
}

void display(Line obj)
{
    cout << "size of line: " << obj.getLength() << endl;
}

int main()
{
    Line line(10);
    display(line);
    
    return 0;
}