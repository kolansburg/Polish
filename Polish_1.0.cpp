#include <iostream>
#include <cstring>
#include <conio.h>
using namespace std;
//ifstream cin("whatbase.in");
//ofstream cout("whatbase.out");
const long long LEN = 8000;
const long long MAX = 4000;
class Stack
{
private:
    char st[MAX];
    long long top;
public:
    Stack()
    {
        top = 0;
    }
    void push ( char var )
    {
        st [++top] = var;
    }
    char pop()
    {
        return st[top--];
    }
    long long gettop()
    {
        return top;
    }
};
class express
{
private:
    Stack s;
    char* pStr;
    long long len;
public:
    express(char* ptr)
    {
        pStr = ptr;
        len = strlen(pStr);
    }
    void parse();
    long long solve();
};
void express::parse()
{
    char ch;
    char lastval;
    char lastop;

    for(long long j = 0; j < len; j++)
    {
        ch = pStr[j];
        if(ch == ' ')
            continue;
        if(ch >= '0' && ch <= '9')
            s.push(ch - '0');
        else
            if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
            {
                if(s.gettop() == 1)
                    s.push(ch);
                else
                {
                    lastval = s.pop();
                    lastop = s.pop();
                    if((ch == '*' || ch == '/') && (lastop == '+' || lastop == '-'))
                    {
                        s.push(lastop);
                        s.push(lastval);
                    }
                    else
                    {
                        switch(lastop)
                        {
                            case '+': s.push(s.pop() + lastval); break;
                            case '-': s.push(s.pop() - lastval); break;
                            case '*': s.push(s.pop() * lastval); break;
                            case '/': s.push(s.pop() / lastval); break;
                            default: cout << "\nAnknown operator"; exit(1);
                        }
                    }
                    s.push(ch);
                }
            }
            else
            {
                cout << "\nAnknown simvol";
                exit(1);
            }
    }
}
long long express::solve()
{
    char lastval;

    while(s.gettop() > 1)
    {
        lastval = s.pop();
        switch(s.pop())
        {
            case '+': s.push(s.pop() + lastval); break;
            case '-': s.push(s.pop() - lastval); break;
            case '*': s.push(s.pop() * lastval); break;
            case '/': s.push(s.pop() / lastval); break;
            default: cout << "\nAnknown operator"; exit(1);
        }
    }
    return (long long)(s.pop());
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
    getch();
    return 0;
}
