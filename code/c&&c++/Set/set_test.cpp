#include <iostream>
#include <set>

using namespace std;

void test_set1()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);

    //"排序+除重"
    set<int>:: iterator it=s.begin();
    while(it!=s.end())
    {
        cout<<*it<<' ';
        ++it;
    }
}

void test_set2()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);

    for(auto e : s)
    {
        cout<<e<<' ';
    }
}


void test_set3()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);

    set<int>:: iterator pos1=s.find(3);
    set<int>:: iterator pos2=s.find(7);
    if(pos1!=s.end())
    {
        cout<< "找到了！"<<endl;
    }
    if(pos2!=s.end())
    {
        cout << "找到了!" <<endl;
    }
}

void test_set4()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);

    if(s.count(3))
    {
        cout<<"3在"<<endl;
    }
    if(s.count(7))
    {
        cout<<"7在"<<endl;
    }
}

void test_set5()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);


    for(auto e:s)
    {
        cout<<e<<' ';
    }
    cout<<endl;

    s.erase(3);
    s.erase(7);

    
    for(auto e:s)
    {
        cout<<e<<' ';
    }

}

void test_set6()
{
    set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    s.insert(1);
    s.insert(6);

    for(auto e:s)
    {
        cout<<e<<' ';
    }
    cout<<endl;

    set<int>:: iterator left=s.lower_bound(3);
    set<int>:: iterator right=s.upper_bound(5);
    s.erase(left,right);

    for(auto e:s)
    {
        cout<<e<<' ';
    }
    cout<<endl;


}

int main()
{
    //test_set1();
    //test_set2();
    //test_set3();
    //test_set4();
    //test_set5();
    test_set6();
    return 0;
}