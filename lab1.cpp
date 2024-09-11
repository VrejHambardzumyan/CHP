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
    cout>>"the number is\n"
    cout>>a;
    
}



int main()
{
    yndhanurBajanarar(64,)

}
