#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
//ifstream cin("whatbase.in");
//ofstream cout("whatbase.out");
const long long LEN = 8000;
const long long MAX = 4000;
void Oshibka(long long u)
{
    if(u == 0)
    {
        cout << "Delenie na 0";
    }
    if(u == 1)
    {
        cout << "Nepravelinai sintacsis";
    }
    exit(1);
}
class express
{
private:
    pair<long long, char> a[MAX], b[MAX];
    long long len, m, i, jj;
public:
    express(char* ptr)
    {
        len = strlen(ptr);
        m = 0;
        i = 0;
        jj = 0;
        for(long long h = 0; h < 200; h++)
        {
            if((ptr[h] >= 'a' && ptr[h] <= 'z') || (ptr[h] >= 'A' && ptr[h] <= 'Z'))
                Oshibka(1);
            if(ptr[h] >= '0' && ptr[h] <= '9')
            {
                m = m * 10 + (ptr[h] - '0');
            }
            else if(ptr[h] == '-' || ptr[h] == '+' || ptr[h] == '/' || ptr[h] == '*')
            {
                if(!m)
                    Oshibka(1);
                a[i].first = m;
                a[i].second = ptr[h];
                i++;
                m = 0;
            }
        }
        a[i].first = m;
        a[i].second = ' ';
        i++;
    }
    void parse();
    long long solve();
};
void express::parse()
{
    jj = -1;
    for(long long j = 0; j < i; j++)
    {
        jj++;
        b[jj].first = a[j].first;
        if(a[j].second == ' ')
            b[jj].second = ' ';
        else if(j == 0)
        {
            b[jj].second = a[j].second;
        }
        else
        {
            if((a[j].second != '*' && a[j].second != '/') || (b[jj - 1].second != '+' && b[jj - 1].second != '-'))
            {
                switch(b[jj - 1].second)
                {
                    case '+': b[jj - 1].first = (b[jj - 1].first + b[jj].first); break;
                    case '-': b[jj - 1].first = (b[jj - 1].first - b[jj].first); break;
                    case '*': b[jj - 1].first = (b[jj - 1].first * b[jj].first); break;
                    case '/': {if(b[jj].first == 0) Oshibka(0);b[jj - 1].first = (b[jj - 1].first / b[jj].first); break;}
                    default: Oshibka(1);
                }
                b[jj - 1].second = a[j].second;
                jj--;
            }
            else
            {
                b[jj].second = a[j].second;
            }
        }
    }
}
long long express::solve()
{
    while(jj > 0)
    {
        switch(b[jj - 1].second)
        {
            case '+': b[jj - 1].first = b[jj - 1].first + b[jj].first; break;
            case '-': b[jj - 1].first = b[jj - 1].first - b[jj].first; break;
            case '*': b[jj - 1].first = b[jj - 1].first * b[jj].first; break;
            case '/': {if(b[jj].first == 0) Oshibka(0);b[jj - 1].first = (b[jj - 1].first / b[jj].first); break;}
            default: Oshibka(1);
        }
        jj--;
    }
    return b[jj].first;
}
int main()
{
    char ans;
    char String[LEN];
    cout << "Vvedite varagenie bez scoboc";
    do
    {
        cout << "\nVaragenie ";
        cin.getline(String, LEN);
        express* eptr = new express(String);
        eptr->parse();
        cout << "Rezult: " << eptr->solve() << endl;
        delete eptr;
        cout << "Eshe (y/n)? ";
        ans = getch();
        if(ans == 'y')
            cout << "yes";
        else
            cout << "no" << endl;
    }
    while(ans == 'y');
    return 0;
}
