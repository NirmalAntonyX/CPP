#include<iostream>
#include<vector>

using namespace std;


template <typename T, int dur>
double power (double a, int freq = 1000)
{

    return 1000.0;
}
class A
{
  public:
    virtual int method (int a) {
        return 100;
    }

};
class B: public A
{
   public:
     virtual int method(int a)
     { return 300;
     }
     static int data;
     int meth3 (int b)
     {
         return 200;
     }
};
int B::data = 0;




int main(void)
{
  B *b = new B();
 A *a = reinterpret_cast<A *>(b);
  
   return 1;
}