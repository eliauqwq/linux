# 图的表示方法一——邻接矩阵
图的目录中我们粗略介绍过邻接矩阵这种图表示方法了，现在我们着手尝试实现一波邻接矩阵。

## 一、基本要素
我们前面讲过，图就是点及其连接他们的边的集合。顶点的值我们可以用数组来表示，边我们通过邻接矩阵来表示
而我们的点还要有与之对应的下标，我们应用map来保存下标与值之间的映射。
```
class Graph
{
    vector<int> vertex;//顶点集合
    map<size_t,int> tag;//点及其下表的对应关系
    vector<vector<int>> matrix;//领接矩阵
```
## 二、功能接口
### 1.构造函数
首先，我们要决定怎么构造一个图，因为图本身由顶点和边组成，而边作为一个二维数组，不太好作为参数传入
图当中去，因此，我们把一组数当作顶点的值传进图当中去，然后按照先后顺序一一进行下标赋值，这里为了简便，
我们选择用size_t作为顶点的下标，事实上可以使用模板来写Graph，自定义我们的顶点下标。

再把顶点集合和下标弄好之后，我们将matrix进行一个初始化。这里需要注意的是，我们不能直接使用两层循环来给
以vector为容器的二维数组赋值，当我们试图直接访问matrix[i][j]时，这个位置并没有被实际开辟出来，程序运行
可能会引发内存的泄露，因而我们需要使用vector的resize接口，直接系统初始化我们的matrix。
```
Graph(int *arr,int arrsize)
    {
        size_t index = 0;
        for(int i = 0 ;i<arrsize;i++)
        {
            vertex.push_back(arr[i]);
            tag.insert(pair<size_t,int>(index++,arr[i]));
        }
        int n = vertex.size();
        matrix.resize(n,vector<int>(n,0));
        
    }
```

### 2.添加新边
构造完我们的图之后，我们要开始填充matrix。在这里我们先写一个给定顶点值返回下标的函数，方便我们后续往矩阵中填值。
```
    size_t Gettag(int value)//根据顶点的值确定其下标
    {
        for(auto e : tag)
        {
            if(e.second == value)
                return e.first;
        }

        cout <<"输入的值未找到"<< endl;
        exit(-1);
    }
```
接下来我们利用函数的默认参数，在无权图中我们直接输入两点的值，在加权图中我们
最后补上两点之间的权就行了。
```
    void addEdge(int value1,int value2,int weight = 1)//添加边,默认无权，如果有权则输入
    {
        size_t tag1 = Gettag(value1);
        size_t tag2 = Gettag(value2);

        matrix[tag1][tag2] = weight;
    }
```
### 3.遍历
在图这种数据结构当中，通常存在深度优先遍历(DFS)和广度优先遍历(BFS)这两种优先遍历方式，我们先来
介绍深度优先算法。

- **DFS——Depth-first Search，深度优先遍历**
这种遍历方式的思路是首先设置一个访问记录数组，用于记录每个顶点是否被访问过，
然后利用递归的方式，对一个顶点进行如下的操作：
1. 首先将该点访问数组置为真，确保该点不会被再访问
2. 打印该点的数据
3. 对其领接矩阵进行遍历判断，看与其相连的点是否被访问过，如果发现未被访问过的点，
直接递归这个点。

    当然，我们的图不一定是连通图，无法保证所有的点都具备连通性，因此我们在对初始顶点
    实行DFS之后再检查一下访问记录，看看是否还存在没有被访问到的顶点，将未访问过的再次进行DFS。

    代码实现：
```
    int Getsize()
    {
        return vertex.size();
    }

    /*dfs辅助函数*/
    void dfsunit(size_t v,vector<bool> &visited)
    {
        visited[v] = true;//先将该点对应访问值置已访问
        cout<< tag[v]<< endl;//输出该点的值

        int n = Getsize();
        for(int i=0;i<n;i++)
        {
            //如果这条边存在且另一端没有被访问过
            if(matrix[v][i] != 0&&visited[i] != true)
            {
                dfsunit(i,visited);
            }

        } 
    }

    void DFS()
    {
        /*首先找一个访问数组并初始化*/
        vector<bool> visited(Getsize(),false);
        cout<<"DFS遍历如下："<<endl;
        dfsunit(0,visited);

        for(size_t i = 0;i<Getsize();i++)
        {
            /*遍历检查是否所有顶点已经被遍历到了*/
            if(!visited[i])
            {
                dfsunit(i,visited);
            }
        }
    }
```
-----------
- **BFS——Breadth-First Search，广度优先算法**
这种遍历方法的优先级与DFS不同，其思路和树当中的层序遍历相似，*总是优先搜索与目标顶点距离较近的点*，因此适合用来寻找最短路径。既然提到了层序的概念，那我们用队列就可很容易实现这一过程，不需要用递归的复杂方法：
1. 首先初始顶点入队，然后遍历所有与其相连的点，考虑访问性，满足未被访问的入队。循环完成初始顶点出列。
2. 接下来以队列为空作为循环出口，对每个队列排头作跟初始顶点一样的操作，然后出队。

    代码实现：
```
    void bfsunit(size_t v,vector<bool> &visited,queue<size_t> & mem)
    {
        /*首先对初始顶点置已访问并入队*/
        visited[v] = true;
        mem.push(v);

        /*以队列是否为空来判断是否已经遍历完*/
        while(!mem.empty())
        {
            /*初始顶点打印*/
            cout<<tag[mem.front()]<<endl;

            for(size_t i = 0; i< Getsize();i++)
            {
                if(matrix[mem.front()][i] != 0 &&visited[i] == false)
                {
                    mem.push(i);
                    visited[i] = true;
                }
            }
            mem.pop();
        }
    }

    void BFS()
    {
        vector<bool> visited(Getsize(),false);
        queue<size_t> mem;

        cout<<"BFS遍历如下："<<endl;
        bfsunit(0,visited,mem);

        for(size_t i=0;i<Getsize();i++)
        {
            if(!visited[i])
            {
                bfsunit(i,visited,mem);
            }
        }
    }
```
------
