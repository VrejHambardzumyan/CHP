#include <iostream.h>
using namespace std;

int yndhanurBajanarar(int a, int b)
{
   a = abs(a);
   b = abs(b);
   
    while (a != b)
    {
       while (a < b)
        {   
            b = b - a;
        }
        while (a > b)
        {
            a = a - b;
        }
    }
    cout>>"The number is\n"
    cout>>a;
}

int main()
{
   int A = -6;
   int B = -9;
   yndhanurBajanarar(A , B);
}
