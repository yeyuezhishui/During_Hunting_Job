#include <iostream>
using namespace std;
const int N = 10;

int heap[N];
int ans[N];
void make_heap(int len);
void adjust(int node,int len);
void heap_sort(int len);


int main(void)
{
    int i = 0;
    for(i = 0; i< N; i++)
    {
        cin >> heap[i];
    }
    make_heap(i);
    for(i = 0; i< N; i++)
    {
        cout << heap[i];
    }
    cout << endl;
    heap_sort(i);
    for(i = 0; i< N; i++)
    {
        cout << ans[i];
    }
    return 0;
}


/****************
 构建堆，从第一个非叶子节点开始调整
 ***************/
void make_heap(int len)
{
    int first_notleaf = (len-1)/2;  //第一个非叶子节点的计算公式
    for(int i = first_notleaf; i>=0; i--)
    {
        adjust(i,len);
    }
}


/****************
调整堆，调整的结果是让node为根节点的子树
满足大根堆要求。循环调用的思想不是递归，而是向下迭代
 ***************/
void adjust(int node,int len)
{
    int left = 2*node+1;    //任一节点左孩子的计算公式
    int right = 2*node+2;   //任一节点右孩子的计算公式
    int max = node;
    if(left<len && heap[left]>heap[max])
    {
        max = left;
    }
    if(right<len && heap[right]>heap[max])
    {
        max = right;
    }
    if(max != node) //需要向下迭代调整的情况
    {
        swap(heap[node],heap[max]);
        adjust(max,len);
    }
}


/****************
 排序操作，每次交换当前根节点和最后一个叶子节点
 ***************/
void heap_sort(int len)
{
    for(int i = 0; i< len; i++)
    {
        ans[i] = heap[0];   //根节点取出后放在数组尾部
        swap(heap[0],heap[len-i-1]); //原本尾部的节点交换到根节点位置
        adjust(0,len-i-1);  //重新从根节点开始调整
    }
}
