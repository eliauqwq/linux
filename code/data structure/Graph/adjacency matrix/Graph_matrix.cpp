#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph
{
    vector<int> vertex;//顶点集合
    map<size_t,int> tag;//点及其下表的对应关系
    vector<vector<int>> matrix;//领接矩阵

public:
    Graph(int *arr,int arrsize)
    {
        size_t index = 0;
        for(int i = 0 ;i<arrsize;i++)
        {
            vertex.push_back(arr[i]);
            tag.insert(pair<size_t,int>(index++,arr[i]));
        }
        int n = vertex.size();
        matrix.resize(n,vector<int>(n,INT_MAX));
        
    }

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

    void addEdge(int value1,int value2,int weight = 1)//添加无向边,默认无权，如果有权则输入
    {
        size_t tag1 = Gettag(value1);
        size_t tag2 = Gettag(value2);

        matrix[tag1][tag2] = weight;
        matrix[tag2][tag1] = weight;
    }

    void addDEdge(int value1,int value2,int weight = 1)//添加有向边
    {
        size_t tag1 = Gettag(value1);
        size_t tag2 = Gettag(value2);

        matrix[tag1][tag2] = weight;
    }

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
};

int main()
{
    int arr[] = {2,5,6,8,9,1};
    int arrsize = sizeof(arr)/sizeof(arr[0]);
    Graph ass(arr,arrsize);

    ass.addDEdge(1,5,1);
    ass.addDEdge(1,2,2);
    ass.addDEdge(5,2,-4);
    ass.addDEdge(1,9,5);
    ass.addDEdge(9,8,-1);
    ass.addDEdge(8,6,-2);

    ass.Floyd(5);
}