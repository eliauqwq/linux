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

