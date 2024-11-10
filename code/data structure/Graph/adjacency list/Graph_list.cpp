#include<iostream>
#include<vector>
#include<map>
#include<queue>

using namespace std;

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

    /*根据值返回下标*/
    size_t Getindex(V key)
    {
        for(auto e: index)
        {
            if(e.first == key)
            {
                return e.second;
            }
        }
        return 114514;
    }


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
};

int main()
{
    vector<string> arr;
    arr.push_back("洗衣服");
    arr.push_back("吃饭");
    arr.push_back("睡觉");
    arr.push_back("看电视");
    arr.push_back("写作业");
    arr.push_back("遛狗");

    Graph<string> ass(arr);

    ass.addEdge("洗衣服","吃饭");
    ass.addEdge("洗衣服","写作业");
    ass.addEdge("写作业","看电视");
    ass.addEdge("看电视","睡觉");
    ass.addEdge("吃饭","睡觉");
    ass.addEdge("遛狗","写作业");

    ass.Kahn();
    return 0;
}
