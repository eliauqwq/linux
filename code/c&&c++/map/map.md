# >>>>>>>>STL之“map”
   map是一种STL容器，是以搜索二叉树准确来说是红黑树(平衡搜索二叉树)为底层的一种容器。
其中所存储的元素是关联，也就是所谓“映射”，包含一个“键”--k和一个“值”--v。在map中，我们可以
通过“键”来快速搜索对应的“值”。

# 一.pair类型
上面说到，在map中的元素是一个*pair--关联*。其中包含具有一定关系联合在一起的两个变量，“键”“值”。
这两个变量可以是同一类型，也可以不是。
typedef pair<const K,V>  value_type
而在STL库中就对pair有定义，可以直接使用构造函数来直接创建一个pair

```
template<class T1, class T2>
struct pair {
	typedef T1 fisrt_type;
	typedef T2 second_type;
 
	T1 first;
	T2 second;
	pair() 
		: first(T1())
		, second(T2())
	{}
	pair(const T1& a, const T2& b)
		: first(a)
		, second(b) 
	{}
};
```


# 二.插入--insert接口
我们假定pair的数据类型是<string,string>。
那么对于insert接口，有三种传参方式：

1.直接调用pair的构造函数
```
map<string,string> dict;
dict.insert(pair<string,string>("sort","排序"));
```

2.借用map的接口make_pair()来插入
```
map<string,string> dict;
dict.insert(make_pair("sort","排序"));
```
这里因为make_pair是map的内部接口，因此不需要再声明模板

3.直接使用大括号。这种方法得益于c++11的类型转换
```
map<string,string> dict;
dict.insert({"sort","排序"});
```

# 三.map的遍历和打印
1.map的迭代器
和set的一样，通过::来使用迭代器
`
 map<string,string>:: iterator pos=dict.begin();
`
如果觉得麻烦，直接使用auto类型
`
auto pos=dict.begin();
`

2.既然底层逻辑都是红黑树，那么map也应该有排序+查重的功能
然而由于pair本身并没有“流”的重载函数，因此需要我们手动访问
```
#void test_map1()
{
    map<string,string> dict;
    dict.insert(pair<string,string>("sort","排序"));
    dict.insert(make_pair("insert","插入"));
    dict.insert({"Destroy","销毁"});

    for(auto kv:dict)
    {
        cout << kv.first << ":" << kv.second <<endl;
    }
}
```

# 四、map中的查找
同set一致，map也有count和find两个接口函数
>count返回map中键为目标的pair个数
>find返回map中键为目标的pair迭代器，若找不到返回结束游标end();
这里为了更好体现这两个函数和map的功能，我们设计出一个具体的情景：给定一个string数组，通过map计算每个词条出现的次数。
```
#void test_map2()
{
    string arr[]={"橙子","橘子","柠檬","苹果","西瓜","橙子","橙子",
    "柠檬","柠檬","柠檬","柠檬","苹果","苹果","西瓜"
    }

    map<string,int> count_map;
    for(auto str : arr)
    {
        auto pos=count_map.find(str);
        if(pos==count_map.end())
        {
            count_map.insert(make_pair( arr,1 ));
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
```

上述函数中find和insert函数对map搜索了两次。那么在map中，其实是可以直接使用下标k值来直接访问
对应的pair的。这就得先从insert函数的返回值说起
`
 pair<iterator,bool> insert(const Value_type& val);
`
我们发现居然insert的返回值是一个pair,其中第一个变量是一个迭代器(表示该关联的位置)，一个变量是一个bool类型(表示是否插入成功)。

弄清楚insert接口之后，我们来了解基于此的operator[]
#maped_type& operator[](const K& k)
{
    pair<iterator,bool> res=insert(make_pair(k,maped_type()));

    return res.first->second
}
首先利用insert插入一个默认值得到一个包含目标位置迭代器的pair,然后利用这个pair一步步得到
对应的“值”。

了解这些知识之后，我们对上面的算法进行改进
#void test_map3()
{
    string arr[]={"橙子","橘子","柠檬","苹果","西瓜","橙子","橙子",
    "柠檬","柠檬","柠檬","柠檬","苹果","苹果","西瓜"
    }

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

# 五、map的删除
跟set一样，map的删除(erase)也支持三种删除方式(1.根据迭代器位置 2.根据特定的键值3.根据某迭代器范围)
同样的，也能使用lower_bound、upper_bound来确定一个范围。

# 六、multimap
multimap允许同一个“键”对应不同的“值”，但是值得注意的是，multimap并不支持operator[]重载

