# 最短路径问题
在加权图中，从给定一点到其他所有点的最短加权路径就是图种最经典的最短路径问题。在本文件中给出三种解决
这个问题的算法以供参考，让我们看看具体的解决思路吧。

## Dijkstra算法
Dijkstra的思路是利用贪心策略，不断寻找离目标点更近的路径。其主要过程如下：
1. 初始化：

    - 将所有顶点的距离初始化为“无穷大”（表示尚未找到路径），起始顶点的距离初始化为 0。
    - 使用一个“优先队列”或“最小堆”来跟踪距离最小的顶点。
2. 选择并“固定”顶点：

    - 从起始顶点开始，在所有未访问顶点中选择距离起点最近的顶点 u。
    - 将该顶点 u的距离视为“确定”，即不会再更新其最短路径。
3. 更新邻接顶点：

    - 对于顶点 u 的每个邻接顶点 v，若从 u 到 v 的路径比之前记录的路径更短，则更新 v 的最短路径距离。
4. 重复步骤 2 和 3，直到所有顶点都“确定”最短路径或优先队列为空。
源代码：
```
 /*Dijkstra算法*/
    void Dijkstra(size_t start)
    {
        /*首先初始化距离容器*/
        vector<int> dist(Getsize(),INT_MAX);
        dist[start] = 0;//与自己的距离化为0

        vector<size_t> visited(Getsize(),false);//初始化访问状态数组

        /*引入最优队列，并转化为最小堆*/
        priority_queue<pair<int,size_t>,vector<pair<int,size_t>>,greater<pair<int,size_t>>> pq;

        /*插入自身*/
        pq.push({dist[start],0});


        while(!pq.empty())
        {
            /*找到最小距离点*/
            int mindist = pq.top().first;
            int u = pq.top().second;
            pq.pop();


            /*判断到该点的最小距离是否已经找到*/
            if(visited[u]) continue;
            visited[u] = true;

            for(size_t v = 0;v < Getsize();v++)
            {
                if(matrix[u][v] != INT_MAX&&!visited[v])
                {
                    if(mindist + matrix[u][v] < dist[v])
                    {
                        dist[v] = mindist + matrix[u][v];
                        pq.push({dist[v],v});
                    }
                }
            }
        }

        for(size_t i=0;i<Getsize();i++)
        {
            if(dist[i] != INT_MAX)
            {
                cout<<"到"<<i<<"点的距离是"<<dist[i]<<endl;
            }
            else
            {
                cout<<"与"<<i<<"点并不联通"<<endl;
            }
        }
    }
```

## Bellman-Ford算法
介绍过Dijkstra算法的时候，我们提到了Dijkstra算法只能解决权值为正的图中的最短路径，假使我们现在需要解决带负权的
图中的最短路径问题，则需要使用另一种单源搜索算法——Bellman-Ford算法。

**Bellman-Ford算法的思路：**
- 1.首先声明一个容器存储最短距离，初始化成无穷大，然后将初始顶点的值设为0。
- 2.遍历所有的边，然后对任意的边`E(u,v)`，如果`u->v`+`dist[u]`的值小于`dist[v]`，那么找到更短的路径，
将`dist[v]`更新为最短路径。
- 3.重复以上的遍历V-1次。
- 4.再次遍历所有边，假如还能找到更短的路径，那么证明给出的图中含有负权环，无法计算最短路径。

>解读：
1. 为什么我们要遍历V-1次？：因为当图中不存在负权环时，对于任一点，到初始顶点的最短距离一定不会超过V-1条边，最坏的情况就是最短路径需要经过其余的所有点。
2. 什么是负权环？：负权环就是指在图中的权值和为负数的回路。当存在负权环时，顶点到其余点的最短距离无法确定，因为可以无限循环负环权，使距离不断下降。
3. 与Dijikstra算法比较；在稠密图中，由于Bellman算法需要不断遍历所有边，因此其效率不如Dijkstra算法，然而其可以处理负权图的特性也使得应用非常广泛。

**Bellman-Ford代码实现(邻接矩阵)**
```
/*Bellman-Ford算法*/
    bool relaxation(size_t start,vector<int> &dist)
    {
        /*初始化距离数组*/
        dist.resize(vertex.size(),INT_MAX);
        dist[start] = 0;

        /*遍历V-1次*/
        for(int i=0;i<vertex.size()-1;i++)
        {
            for(int j=0;j<vertex.size();j++)
            {
                for(int k=0;k<vertex.size();k++)
                {
                    if(dist[j] != INT_MAX&&dist[k]>dist[j]+matrix[j][k]&&matrix[j][k]!=INT_MAX)
                        dist[k] = dist[j] + matrix[j][k];
                }
            }
        }
        /*遍历第V次*/
        for(int i=0;i<vertex.size();i++)
        {
            for(int j = 0;j<vertex.size();j++)
            {
                if(dist[i]!=INT_MAX&&dist[j]>dist[i]+matrix[i][j]&&matrix[i][j]!=INT_MAX)
                    return false;//存在负权环
            }
        }

        return true;
    }

    void BellmanFord(size_t start)
    {
        vector<int> dist;
        if(relaxation(start,dist))
        {
            for(int i=0;i<vertex.size();i++)
            {
                if(dist[i]!=INT_MAX)
                {
                    cout<<"到"<<i<<"点的最短距离是"<<dist[i]<<endl;
                }
                else
                {
                    cout<<"与"<<i<<"点并不相连"<<endl;
                }
            }
        }
        else
        {
            cout<<"图中存在负权环"<<endl;
        }
    }
```

## Floyd-Warshall算法
在求图的最短路径过程中，还存在一种**多源的**求解最短路径的算法——Floyd-Warshall算法。该算法可以处理带负权值
的图。

**Floyd算法的基本思路**
- 1.首先定义一个距离的二维矩阵`dist[n][n]`,其中`n`为顶点的数量，将所有边的权值填入到这个容器当中，默认`dist[i][j]`表示从`i`到`j`的有向边的权值。且`dist[i][i]`默认为0。
- 2.然后遍历所有的顶点，让其作为一个中间结点`k`，判断是否能够使得`i->k->j`的距离比`dist[i][j]`要小，这个过程往往利用三层循环来实现，其中我们把中间结点的循环放在最外面。

**算法实现(还是以邻接矩阵为例)：**
```
    /*Floyd-Warshall算法*/
    void Floyd(size_t start)
    {
        /*直接拷贝邻接矩阵初始化距离数组*/
        vector<vector<int>> dist = matrix;
        for(int i=0;i<vertex.size();i++)
        {
            for(int j = 0;j<vertex.size();j++)
            {
                if(i == j)
                    dist[i][j] = 0;//别忘了把到自身的距离初始化为零
            }
        }

        /*三层遍历*/
        for(int i = 0;i<vertex.size();i++)
        {
            for(int u = 0;u<vertex.size();u++)
            {
                for(int v = 0;v<vertex.size();v++)
                {
                    if(dist[u][i] != INT_MAX&&dist[i][v]!= INT_MAX&&dist[u][v]>dist[u][i]+dist[i][v])
                        dist[u][v] = dist[u][i]+dist[i][v];
                }
            }
        }

        /*输出*/
        for(int i = 0;i<vertex.size();i++)
        {
            if(dist[start][i] != INT_MAX)
            {
                cout<<"到"<<i<<"点的最短距离是"<<dist[start][i]<<endl;
            }
            else
            {
                cout<<"没有到"<<i<<"点的最短距离"<<endl;
            }
        }
    }
```