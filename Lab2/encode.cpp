#include <iostream>
#include <cstring>
using namespace std;

void loweCase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {   
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        } 
        i++;
    }
}
void encode(char *str)
{
    loweCase(str);
    char abc[] = "abcdefghijklmnopqrstuvwxyz";
    char key[] = "EFGHIJKLMNOPQRSTUVWXYZABCD";
    char encoded [strlen(str) + 1];
    int i = 0; 
    int j = 0;
    cout << "Kodavorvac bary: ";
    while (str[i] != '\0')
    {
        if (str[i] == abc[j])
        {
            encoded[i] = key[j];
            cout<<encoded[i];
            i++;
            j = -1;
        }
        j++;
    }
    encoded[i] = '\0';
    cout<<"\n";
}

int main()
{
    char str[] = "VArduhi";
    encode(str);
}