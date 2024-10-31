#include <iostream>
#include <map>
#include <vector>

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
        matrix.resize(n,vector<int>(n,0));
        
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

    void addEdge(int value1,int value2,int weight = 1)//添加边,默认无权，如果有权则输入
    {
        size_t tag1 = Gettag(value1);
        size_t tag2 = Gettag(value2);

        matrix[tag1][tag2] = weight;
    }
};

int main()
{
    int arr[] = {2,5,6,8,9,1};
    int arrsize = sizeof(arr)/sizeof(arr[0]);
    Graph ass(arr,arrsize);

    ass.addEdge(2,5);
}