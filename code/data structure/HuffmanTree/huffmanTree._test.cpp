#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct huffmanNode
{
    char data ;//结点所存储的字符
    int frep ;//字符出现的频率

    struct huffmanNode* left ;//左子树结点
    struct huffmanNode* right;//右子树结点

    huffmanNode(char _data , int _frep )//叶子结点的创建
        : data(_data),frep(_frep)
        {
            this->left = nullptr;
            this->right = nullptr;
        }


    huffmanNode(char _data,int _frep,huffmanNode* _left,huffmanNode* _right)//内部结点的创建
        :data(_data),
         frep(_frep),
         left(_left),
         right(_right){}
};

/*自定义比较器*/
struct Compare
{
    bool operator()(huffmanNode* first,huffmanNode* second)
    {
        return first->frep > second->frep ;
    }
};

/*生成对应的huffman编码*/
/*
参数一；目标huffman树的根
参数二：目标huffman树已经记录下的编码
参数三：最终我们得到的字符与编码的对应关系map
*/
void PrinthuffmanCode(huffmanNode* root,string str, unordered_map<char,string>& huffmanCode)
{
    /*注意递归终点，传入根节点是空时返回*/
    if(root == nullptr)
    {
        return ;
    }

    /*判断是不是含有字符的叶子节点*/
    if(root->left == NULL&&root->right == NULL)
    {
        huffmanCode[root->data] = str;//传入已经记录好的值
    }

    /*递归给子节点*/
    PrinthuffmanCode(root->left,str+"0",huffmanCode);//走过左子树则记录‘0’
    PrinthuffmanCode(root->right,str+"1",huffmanCode);//走过右子树则记录‘1’
}


/*huffman树整个过程函数*/
void buildhuffmanTree(string text)
{
    /*定义一个map，表示每个字符对应出现的频率*/
    unordered_map<char,int> frep;
    for(char ch : text)
    {
        frep[ch]++;//利用map的[]重载，快速插入frep类型
    }

    /*定义优先队列*/
    priority_queue<huffmanNode*,vector<huffmanNode*>,Compare> qp;
    for(auto pair : frep)
    {
        qp.push(new huffmanNode(pair.first,pair.second));
    }

    /*构建huffman树本体*/
    while(qp.size()!=1)//当队列中只剩一个结点，这个结点就是最终生成huffman树的根
    {
        /*去除最小频率结点1*/
        huffmanNode* left=qp.top();
        qp.pop();
        /*去除最小频率结点2*/
        huffmanNode* right=qp.top();
        qp.pop();

        /*将合成的新结点添加到huffman树中去*/
        int sum=left->frep + right->frep ;
        qp.push(new huffmanNode('\0',sum,left,right));//注意这个新结点只做结构作用，本身无意义
    }

    /*获得huffman树的根结点*/
    huffmanNode* root=qp.top();
    qp.pop();

    /*生成每个字符对应的编码*/
    unordered_map<char,string> huffmanCode;
    PrinthuffmanCode(root,"",huffmanCode);

    /*开始打印huffman编码*/
    cout << "编码对应:" << endl;
    for(auto pair : huffmanCode)
    {
        cout << pair.first << ':' << pair.second <<endl;
    }

    /*最后打印压缩后的字符串*/
    cout << "最终结果" << endl;
    string result;
    for(char ch : text)
    {
        result += huffmanCode[ch];
    }
    cout << result << endl;
}

int main()
{
    string text="ABRBRACADACBBRA" ;
    buildhuffmanTree(text);

    return 0;
}