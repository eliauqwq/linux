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

