#include <iostream>
#include <map>

using namespace std;

void test_map1()
{
    map<string,string> dict;
    dict.insert(pair<string,string>("sort","排序"));
    dict.insert(make_pair("insert","插入"));
    dict.insert({"destroy","销毁"});

    for(auto& kv:dict)
    {
        cout << kv.first << ":" << kv.second <<endl;
    }
}

void test_map2()
{
    string arr[]={"橙子","橘子","柠檬","苹果","西瓜","橙子","橙子",
    "柠檬","柠檬","柠檬","柠檬","苹果","苹果","西瓜","橙子"
    };

    map<string,int> count_map;
    for(auto str : arr)
    {
        auto pos=count_map.find(str);
        if(pos==count_map.end())
        {
            count_map.insert(make_pair( str , 1 ));
        }
        else
        {
            pos->second++;
        }
    }

    for(auto kv : count_map)
    {
        cout << kv.first << ':' << kv.second <<endl;
    }
}

void test_map3()
{
    string arr[]={"橙子","橘子","柠檬","苹果","西瓜","橙子","橙子",
    "柠檬","柠檬","柠檬","柠檬","苹果","苹果","西瓜","橙子"
    };

    map<string,int> count_map;
    for(auto str : arr)
    {
        count_map[str]++;//“值”是int类型，可以使用++
    }

    for(auto kv : count_map)
    {
        cout << kv.first << ':' << kv.second <<endl;
    }
}

void test_map4()
{
    string arr[]={"橙子","橘子","柠檬","苹果","西瓜","橙子","橙子",
    "柠檬","柠檬","柠檬","柠檬","苹果","苹果","西瓜","橙子"
    };

    map<string,int> count_map;
    for(auto str : arr)
    {
        count_map[str]++;//“值”是int类型，可以使用++
    }

    for(auto kv : count_map)
    {
        cout << kv.first << ':' << kv.second <<endl;
    }

    count_map.erase("橙子");

    for(auto kv : count_map)
    {
        cout << kv.first << ':' << kv.second <<endl;
    }
}

int main()
{
    //test_map1();
    //test_map2();
    //test_map3();
    test_map4();
    return 0;
}