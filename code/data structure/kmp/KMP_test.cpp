#include <iostream>
using namespace std;

void GetNext(string str,int* next)
{
    int i=1;//让i作为后缀的末尾
    int j=0;//让j作为前缀的末尾
    next[0]=0;//默认第一位next值等于0

    /*开始遍历*/
    for(i = 1;i < str.size();i++)
    {
        while(j > 0&& str[j] != str[i]) j=next[j-1];//当前缀长度不为一时，让j返回前一位的next值处
        if(str[i]==str[j]) j++;
        next[i] = j;
    }
}

int KMP(string mom,string son)
{
    int * next = (int*)malloc(sizeof(int)*1000);
    GetNext(son,next);

    int j=0;
    for(int i=0;i < mom.size();i++)
    {
        while(j > 0&&mom[i] != son[j]) j=next[j];
        if(mom[i] == son[j]) j++;
        if(j == son.size())
        {
            return i-son.size()+1;
        }
    }
    return -1;
}

int main()
{
    string mom;
    string son;
    cin >> mom;
    cin >> son;

    int result = KMP(mom,son);
    cout << result;
}