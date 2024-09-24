#include <iostream>
#include <cstring>
using namespace std;

void upperCase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {   
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        } 
        i++;
    }
}
void encode(char *str)
{
    upperCase(str);
    char abc[] = "EFGHIJKLMNOPQRSTUVWXYZABCD";
    char key[] = "abcdefghijklmnopqrstuvwxyz";
    char decoded [strlen(str) + 1];
    int i = 0; 
    int j = 0;
    cout << "Apakodavorvac bary: ";
    while (str[i] != '\0')
    {
        if (str[i] == abc[j])
        {
            decoded[i] = key[j];
            cout<<decoded[i];
            i++;
            j = -1;
        }
        j++;
    }
    decoded[i] = '\0';
    cout<<"\n";
}

int main()
{
    char str[] = "ZEVHYLM";
    encode(str);
}