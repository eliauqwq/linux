# AOV图和拓扑排序
在用图数据结构解决问题的时候，我们经常能够遇到一类问题，例如工程的推进问题，只有先订购好水泥等材料，
我们才能够开始修筑地基，只有将地基修好，我们才能在此基础上修建高楼。这类任务之间的依赖关系可以使用
有向图来表示，其中A->B就表示了B是依赖于A点的，只有完成A之后才能完成B，类似这样的图我们一般称之为
AOV网(Activity-on-Vertex graph)。

**例如**
```
A ----> B ----> C
  \
   \
    ---> D ---->
```
这就是一个很简单的AOV网，其中的有向边代表着各顶点之间的依赖关系。

## AOV图的应用及其原理
既然AOV能表示各任务之间的依赖关系，那我们便能够利用这个特点，让AOV网帮我们归纳出一个能够正确且便捷完成所有任务的路线，这个过程称之为***拓扑排序***。

在给出拓扑排序的思路以及具体实现前，我们先来了解一下AOV图具备什么先决条件。

> AOV网都是DAG，Direct-Acyclic-Graph,有向无环图

也就是说，从AOV图中任一点出发，绝对不可能再次回到这一点，否则就会形成依赖闭环，那么这个工程就无法真正被完成。

既然知道AOV图必然是有向无权图，那么其子图也不会包含环。

了解以上这些基本的原理，接下来我们正式了解解决拓扑排序的一种方法——Kahn算法。

## Kahn算法思路
Kahn算法主要依靠以下步骤解决拓扑排序问题：

1.首先找出图中入度为0的点，将这些点填入到最终序列中去。

2.将入度为0的点的出边从图中删去，同时更新其他点的入度。

3.再次循环剩下的点，发现入度为0的点重复以上的操作直到整个图中顶点被送入最终序列。

4.如果某次遍历发现不存在入度为0的点，那么该图不是有向无环图，退出并报错。

有一些帮助理解的小细节：
- **入度为0代表这个点没有任何依赖，也就是说不需要任何先决条件，这个时候就可以直接填入最终序列了。**
- **为什么有向无环图中必然存在入度为0的点，这是因为如果不存在这种点，那一定能找出一条路径使得从一点回到该点，这是最重要的。**

经过Kahn算法排序之后，最终序列的顺序也不一定完全相同，可能存在些许差别。排序只用保证**如果序列中的端点之间存在边相连，那么起点一定在终点之前。**

## Kahn算法实现
### 一、图的存储方式

我们之前已经了解到，Kahn算法会频繁涉及到图中各顶点的入度以及出边，因而图的存储方式我们选择邻接表来表示。同时为了更便捷的获取图的数据，我们设计两个邻接表，一个是入边表，一个是出边表，存储顶点的入边和出边。

类基本设计如下：
```
/*定义一个边*/
struct Edge
{
    size_t other; //边的另一端点
    int weight;//边的权重
    struct Edge* next;//该点的下一条边

    /*构造函数*/
    Edge(size_t _other,int _weight=1)
        :other(_other)
        ,weight(_weight)
        ,next(nullptr)
        {}
};

template<class V>
class Graph
{
private:
    vector<V> vertex;//顶点集合
    map<V,size_t> index;//下标
    vector<Edge*> from_table; //入边邻接表
    vector<Edge*> to_table;//出边领接表
public:
    /*构造函数*/
    Graph(vector<V> arr)
    {
        /*填入点集*/
        for(auto e: arr)
        {
            vertex.push_back(e);
        }
        /*初始化下标*/
        for(int i=0;i<vertex.size();i++)
        {
            index.insert({vertex[i],i});
        }
        /*初始化领接表*/
        to_table.resize(vertex.size(),nullptr);
        from_table.resize(vertex.size(),nullptr);
    }
```
添加边的时候也需要同时更新入边和出边表：
```
    /*添加边(默认有向)*/
    void addEdge(V key1,V key2,int weight=1)
    {
        size_t st = Getindex(key1);
        size_t ed = Getindex(key2);

        /*更新入边表*/
        if(from_table[ed] == nullptr)
        {
            from_table[ed] = new Edge(st);
        }
        else
        {
            Edge* end = from_table[ed];
            while(end->next != nullptr)
            {
                end = end->next;
            }
            end->next = new Edge(st);
        }

        /*更新出边表*/
        if(to_table[st] == nullptr)
        {
            to_table[st] = new Edge(ed);
        }
        else
        {
            Edge* end = to_table[st];
            while(end->next !=nullptr)
                end = end->next;
            end->next = new Edge(ed);
        }
    }
```

### 二、Kahn本身实现
首先我们需要一个函数，来获得存储各店入度的数组
```
    /*Kahn辅助函数，构建入度数组*/
    void Getcount(vector<int> &count)
    {
        for(size_t i = 0;i < vertex.size();i++)
        {
            Edge* cur = from_table[i];
            while(cur != nullptr)
            {
                count[i] ++;
                cur = cur->next;
            }
        }
    }
```

还有一个切去入度为0点出边并更新剩余点入度的函数：
```
    /*更新入度数组*/
    void Modcount(size_t out,vector<int> &count)
    {
        Edge* cur = to_table[out];
        while(cur != nullptr)
        {
            count[cur->other]--;
            cur = cur->next;
        }
    }
```

剩下就是Kahn本体了，我们设置一个旗帜值，每次循环将其置为false，只有找到入度为0的店在将其置真，否则表示存在环，退出程序并报错。
```
/*Kahn算法实现拓朴排序*/
    void Kahn()
    {
        /*首先声明入度数组*/
        vector<int> count;
        count.resize(vertex.size(),0);
        Getcount(count);

        /*定义最终排序队列*/
        queue<size_t> result;

        /*定义访问数组*/
        vector<int> visited(vertex.size(),0);

        /*开始迭代*/
        bool run = true;
        while(run)
        {
            run = false;
            for(size_t i =0;i<count.size();i++)
            {
                if(count[i] == 0&&visited[i]== 0)
                {
                    run =true;

                    result.push(i);//入队
                    visited[i] = 1;

                    Modcount(i,count);
                }
            }
        }
        
        if(result.size()!=vertex.size())
        {
            cout<<"图中存在环！"<<endl;
        }
        else
        {
            while(!result.empty())
            {
                cout<<vertex[result.front()]<<endl;
                result.pop();
            }
        }
    }
```

