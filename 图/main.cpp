//
//  main.cpp
//  图
//
//  Created by 唐昊杰 on 17/12/9.
//  Copyright © 2017年 唐昊杰. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include "Header.h"
using namespace std;

#define UNVISITIED 0
#define VISITIED 1
#define INFINITY 9999999


class UFSets{
private:
    int n;      //等价类中元素的个数
    int *root;  //root[i]表示元素i所在的等价类的代表元编号
    int *next;  //next[i]表示在等价类中i后面的元素的编号
    int *length; //length[i] 表示i所代表的等价类的元素的个数
public:
    UFSets(int size){
        n = size;
        root = new int[n];
        next = new int[n];
        length = new int[n];
        for(int i = 0; i<n; i++){
            root[i] = next[i] = i;
            length[i] = 1;
        }
    }
    
    ~UFSets(){
        delete []root;
        delete []next;
        delete []length;
    }
    int Find(int v){
        return root[v];
    }
    
    void Union(int v, int u){
        if(root[u] == root[v])
            return;
        else if (length[root[v]] < length[root[u]]){
            int rt = root[v];    //获取v所在的等价类的代表元素
            length[root[u]] += length[rt]; //修改u所在等价类的元素个数
            root[rt] = root[u];  //修改v所在等价类的各元素的代表元信息
            for(int j = next[rt]; j != rt; j = next[j])
                root[j] = root[u];
            
            int temp = next[rt];
            next[rt] = next[root[u]];
            next[root[u]] = temp;   //将两个等价类的元素连接起来
            
        }
        else{
            int rt = root[u];    //获取u所在的等价类的代表元素
            length[root[v]] += length[rt]; //修改v所在等价类的元素个数
            root[rt] = root[v];  //修改u所在等价类的各元素的代表元信息
            for(int j = next[rt]; j != rt; j = next[j])
                root[j] = root[v];
            
            int temp = next[rt];
            next[rt] = next[root[v]];
            next[root[v]] = temp;   //将两个等价类的元素连接起来
            
        }
    }
};


template<class T>
class Edge{
public:
    int start,end;
    T weight;
    Edge(){
        start = end = weight = 0;
    }
    Edge(int st,int en,T w){
        start = st;
        end = en;
        weight = w;
    }
    
    bool operator > (Edge oneEdge){
        if(this->weight > oneEdge.weight)
            return true;
        else return false;
    }
    
    bool operator < (Edge oneEdge){
        if(this->weight < oneEdge.weight)
            return true;
        else return false;
    }
    
};

template<class T>
class Graph{          //图类型
public:
    int vertexNum;    //图的顶点数目
    int edgeNum;      //图的边数目
    int *Mark;        //标记某顶点是否被访问过
    
    Graph(int verticesNum){
        vertexNum = verticesNum;
        edgeNum = 0;
        
        Mark = new int[vertexNum];
        for(int i = 0;i<vertexNum;i++)
            Mark[i] = UNVISITIED;    //标志位初始化
    }
    
    ~Graph(){
        delete []Mark;
    }
    
    virtual Edge<T> FirstEdge(int oneVertex) = 0;
    //返回与顶点oneVertex相关联的第一条边
    virtual Edge<T> NextEdge(Edge<T> oneEdge) = 0;
    //返回与边oneEdge有相通起点的下一条边
    virtual void setEdge(int start,int end,T weight) = 0;
    //设置边(start,end)，权重为weight
    virtual void delEdge(int start,int end) = 0;
    //删除边(start,end)
    
    int VerticesNum(){
        return vertexNum;   //返回图的顶点个数
    }
    
    int EdgesNum(){
        return edgeNum;     //返回图的边数
    }
    
    bool IsEdge(Edge<T> oneEdge){
        if(oneEdge.weight>0 && oneEdge.weight<INFINITY &&  oneEdge.start >= 0 && oneEdge.end >=0)
            return true;
        else return false;
    }
    
    int StartVertex(Edge<T> oneEdge){ //返回边oneEdge的起点
        return oneEdge.start;
    }
    
    int EndVertex(Edge<T> oneEdge){   //返回边oneEdge的终点
        return oneEdge.end;
    }
    
    int Weight(Edge<T> oneEdge){        //返回边oneEdge的权重
        return oneEdge.weight;
    }
    ///////
    
    
    bool ToplogySort(int *SortArray){
        int n = VerticesNum();
        int * indegree = new int[n];
        int v;
        Edge<T> e;
        for (v = 0; v < n; v++){
            indegree[v] = 0;
            Mark[v] = UNVISITIED;
        }
        for (v = 0; v < n; v++){
            for (e = FirstEdge(v); IsEdge(e); e = NextEdge(e)){
                indegree[e.end]++;
            }
        }
        for (int i = 0; i < n; i++){  //依次确定拓扑序列中的第i个元素
            for (v = 0; v < n; v++){    //找到入度为零且未被访问的边
                if (indegree[v] == 0 && Mark[v] == UNVISITIED){
                    break;
                }
            }
            if (v == n && i != n-1) {     //找不到
                cout << "有向图存在回路" << endl;
                for (int i = 0; i < n; i++){
                    if (Mark[i] == UNVISITIED)
                        cout << i << " ";
                }
                cout << endl;
                return false;
            }
            
            Mark[v] = VISITIED;
            SortArray[i] = v;
            for (e = FirstEdge(v); IsEdge(e); e = NextEdge(e)){
                indegree[e.end]--;
            }
        }
        delete []indegree;
        return true;
    }
    
    void DFS(int v){
        Mark[v] = VISITIED;
        cout<<v<<" ";
        for(Edge<T> e = FirstEdge(v); IsEdge(e) ; e = NextEdge(e)){
            if(Mark[EndVertex(e)] == UNVISITIED)
                DFS(EndVertex(e));
        }
    }
    
    void DFSTraverse(){
        for(int i = 0; i<VerticesNum(); i++)
            Mark[i] = UNVISITIED;
        for(int i = 0; i<VerticesNum(); i++){
            if(Mark[i] == UNVISITIED)
                DFS(i);                //对未访问的顶点调用DFS
        }
    }
    
    void DFSNoReverse(){
        int i,v,u;
        stack<T> s;
        for(i = 0; i<VerticesNum(); i++)
            Mark[i] = UNVISITIED;
        for(i = 0; i<VerticesNum(); i++){
            if(Mark[i] == UNVISITIED){
                s.push(i);
                cout<<i<<" ";
                Mark[i] = VISITIED;
                while(!s.empty()){
                    v = s.top();
                    s.pop();
                    for(Edge<T> e = FirstEdge(v); IsEdge(e); e  = NextEdge(e)){
                        u = EndVertex(e);
                        if(Mark[u] == UNVISITIED){
                            s.push(u);
                            cout<<u<<" ";
                            Mark[u] = VISITIED;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    int BFS(int v){
        int m = 0;
        queue<T> Q;
        Mark[v] = VISITIED;
        //cout<<v<<" ";
        Q.push(v);
        m++;
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();
            for(Edge<T> e = FirstEdge(u); IsEdge(e); e = NextEdge(e)){
                int k = EndVertex(e);
                if(Mark[k] == UNVISITIED){
                    m++;
                   // cout<<k<<" ";
                    Mark[k] = VISITIED;
                    Q.push(k);
                }
            }
        }
        return m;
    }
    
    void BFSTraverse(){
        int v;
        for(v = 0; v<VerticesNum(); v++)
            Mark[v] = UNVISITIED;
        for(v = 0; v<VerticesNum(); v++){
            if(Mark[v] == UNVISITIED)
                BFS(v);
        }
    }
    
    Edge<T> * Prim(int s){
        int i,j;
        Edge<T> *MST;   //存储最小生成树的边
        T *nearest;     //nearest[i]表示生成树中点到i点的最小边权值
        int *neighbour;  //neighbour[i]生成树中与i点最近的点编号
        int n = VerticesNum();
        
        nearest = new T[n];
        neighbour = new int[n];
        MST = new Edge<T>[n-1];
        for(i = 0; i<n; i++){
            neighbour[i] = s;
     //       cout<<neighbour[i]<<" ";////
            nearest[i] = INFINITY;
        }
     //   cout<<endl;//////
        for(Edge<T> e = FirstEdge(s); IsEdge(e); e = NextEdge(e)){
            i = EndVertex(e);
            nearest[i] = e.weight;
      //      cout<<nearest[i]<<" ";///
        }
      //  cout<<endl; ////

        neighbour[s] = -1;
        for(i = 0; i<n-1; i++){
//            for(int k=0; k<n;k++){
//                cout<<nearest[k];
//                cout<<endl;
//            }
            T min = INFINITY;
            int v = -1;
            for( j = 0; j < n; j++){
                if(nearest[j] < min && neighbour[j] > -1){
                    min = nearest[j];
                    v = j;
                }
            }
            
            if(v >= 0){
                Edge<T> tempEdge(neighbour[v], v, nearest[v]);
                neighbour[v] = -1;
              //  cout<<v;
                MST[i] = tempEdge;
              //  cout<<MST[i].weight;
                for (Edge<T> e = FirstEdge(v); IsEdge(e); e=NextEdge(e)) {
                    int u = e.end;
                    if(neighbour[u] != -1 && nearest[u] > e.weight){
                        neighbour[u] = v;
                       // cout<<u;
                        nearest[u] = e.weight;
                    }
                }
            }
        }
        delete []neighbour;
        delete []nearest;
        return MST;
    }
    
    Edge<T>* Kruskal(){
        int n = VerticesNum();
        UFSets set(n);   //定义n个结点的等价类
        Edge<T> *MST = new Edge<T>[n-1];
        
        MinHeap<Edge<T>> H(EdgesNum());
        Edge<T> edge;
        for(int i = 0; i < VerticesNum(); i++){
            for(edge = FirstEdge(i); IsEdge(edge); edge = NextEdge(edge)){
                if(StartVertex(edge) < EndVertex(edge))
                    H.Insert(edge);
            }
        }
       // H.Show();
   
            
        int edgeNumtemp = 0;
        while(edgeNumtemp < n-1){
            if(!H.isEmpty()){
                edge = H.ReturnMin();
                H.DeleteTop();   //找到权重最小的未处理的边
                int v = edge.start;
                int u = edge.end;
                if(set.Find(v) != set.Find(u)){
                    //判断该边关联的顶点是否在一个联通分量
                    set.Union(v, u);  //合并两顶点所在的等价类
                    MST[edgeNumtemp++] = edge; //将符合条件的边添加到生成树的边集合中
                }
            }
            else{
                cout<<"不存在最小生成树"<<endl;
                break;
            }
        }
        return MST;
    }
   
    void Dijkstra(int s, T D[], int Path[]){
        int n = VerticesNum();
        int i,j;
        for(i = 0; i < n; i++){
            Mark[i] = UNVISITIED;
            D[i] = INFINITY;
            Path[i] = -1;  //标记此时不存在从s到i的路径
        }
        
        Mark[s] = VISITIED;
        D[s] = 0;
        Path[s] = s;
        
        for(Edge<T> e = FirstEdge(s); IsEdge(e); e = NextEdge(e)){
            int endVertex = e.end;
            D[endVertex] = e.weight;
            Path[endVertex] = s;
        }
        
        
        for(i = 0; i < n-1; i++){  //找到一条最短路径
            T min = INFINITY;
            int k;
            for(j = 0; j < n; j++){
                if(Mark[j] == UNVISITIED && min > D[j]){
                    min = D[j];
                    k = j;
                }
            }
            
            //已确定s到k的最短路径
            //cout<<k<<" ";
            Mark[k] = VISITIED;
            //利用k更新到其余未访问顶点的最短特殊路径
            for(Edge<T> e = FirstEdge(k); IsEdge(e); e = NextEdge(e)){
                int endVertex = e.end;
                if(Mark[endVertex] == UNVISITIED && D[endVertex] >(D[k] + e.weight)){
                    D[endVertex] = D[k] + e.weight;
                    Path[endVertex] = k;
                }
            }
        }
    }
    
    void Floyd(T **Adj, int **Path){
        int i,j,v;  //i,j是计数器，v记录相应顶点
        int n = VerticesNum();
        for(i = 0; i < n; i++){      //初始化数组
            for(j = 0; j < n; j++){
                if(i == j){
                    *((int*)Adj + n*i +j) = 0;
                }
                else{
                    *((int*)Adj + n*i +j) = INFINITY;
                }
                *((int*)Path + n*i +j) = i;
            }
        }
        
        for(v = 0; v < n; v++){    //将边(v,u)作为Adj[v][u],v作为path[v][u]的值
            for(Edge<T> e = FirstEdge(v); IsEdge(e); e = NextEdge(e)){
                *((int*)Adj + n*v +e.end) = e.weight;
            }
        }
        
        for(v = 0; v < n; v++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    if(*((int*)Adj + n*i +j) > (*((int*)Adj + n*i +v) + *((int*)Adj + n*v +j))){
                        *((int*)Adj + n*i +j) = *((int*)Adj + n*i +v) + *((int*)Adj + n*v +j);
                        
                        *((int*)Path + n*i +j) = v;
                    }
    }
    
    
    Edge<T>* DestroyCircle(){
        int n = VerticesNum();
        MaxHeap<Edge<T> > q(EdgesNum());
        for (int i =0;i<VerticesNum();i++){
            Mark[i] = 0;
        }
        Edge<T> e;
        Edge<T> * MST = new Edge<T>[n-1];
        for (int i =0;i<n;i++){
            for (e = FirstEdge(i);IsEdge(e);e = NextEdge(e)){
                if (StartVertex(e)<EndVertex(e)){  // 不重复插边
                    q.Insert(e);
                }
            }
        }
        
        while (1){
            if (BFS(0) != n){
                setEdge(e.start,e.end,e.weight);
                if (q.IsEmpty()){
                    break;
                }
            }
            else{
                e = q.GetMax();
                delEdge(e.start,e.end);
                q.RemoveMax();
            }
            for (int i =0;i<VerticesNum();i++){
                Mark[i] = 0;
            }
        }
        int count = 0;
        for (int i =0;i<n;i++){
            for (e = FirstEdge(i);IsEdge(e);e = NextEdge(e)){
                if (StartVertex(e)<EndVertex(e)){
                    MST[count] = e;
                    count++;
                }
            }
        }
        return MST;
    }
};

template<class T>
class AdjGraph:public Graph<T>{
private:
    int **matrix;
public:
    AdjGraph(int verticesNum):Graph<T>(verticesNum){
        int i,j;
        matrix = (T **)new T*[verticesNum]; //申请matrix大小的matrix数组
        for(i = 0; i < verticesNum; i++){  //申请matrix数组行的存储空间
            matrix[i] = new T[verticesNum];
        }
        for(i = 0; i < verticesNum; i++)
            for(j = 0; j < verticesNum; j++)
                matrix[i][j] = 0;    //初始化邻接矩阵的元素
    }
    
    ~AdjGraph(){
        for(int i = 0; i< this->vertexNum; i++)
            delete [] matrix[i];
        delete [] matrix;
    }
    
    Edge<T> FirstEdge(int oneVertex){
        Edge<T> tmpEdge;
        tmpEdge.start = oneVertex;
        for(int i=0; i<this->vertexNum ; i++){
            if(matrix[oneVertex][i] != 0){
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneVertex][i];
                break;
            }
        }
        return tmpEdge;
    }
    
    Edge<T> NextEdge(Edge<T> oneEdge){
        Edge<T> tmpEdge;
        tmpEdge.start = oneEdge.start;
        for(int i = oneEdge.end + 1;i <this->vertexNum;i++){
            if(matrix[oneEdge.start][i] != 0){
                tmpEdge.end = i;
                tmpEdge.weight = matrix[oneEdge.start][i];
                break;
            }
        }
        return tmpEdge;
    }
    
    void setEdge(int start, int end, T weight){
        if(matrix[start][end] == 0 && matrix[end][start]==0 )
            this->edgeNum++;
        matrix[start][end] = weight;
        matrix[end][start] = weight;
    }
    
    void setEdge2(int start, int end, T weight){
        if(matrix[start][end] == 0 )
            this->edgeNum++;
        matrix[start][end] = weight;
    }
    
    void delEdge(int start, int end){
        if(matrix[start][end] != 0  && matrix[end][start] != 0)
            this->edgeNum--;
        matrix[start][end] = 0;
        matrix[end][start] = 0;
    }
    
    void show(){
        for(int i = 0; i < this->vertexNum; i++){
            for (int j = 0; j < this->vertexNum; j++) {
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
int main() {
//    AdjGraph<int> adjgraph(8);
//    adjgraph.setEdge(0, 2, 1);
//    adjgraph.setEdge(0, 1, 1);
//    adjgraph.setEdge(1, 3, 1);
//    adjgraph.setEdge(1, 4, 1);
//    adjgraph.setEdge(3, 7, 1);
//    adjgraph.setEdge(4, 7, 1);
//    adjgraph.setEdge(2, 5, 1);
//    adjgraph.setEdge(2, 6, 1);
//    adjgraph.show();
//    cout<<endl;
//    adjgraph.DFSTraverse();
//    cout<<endl;
//    adjgraph.DFSNoReverse();
//    cout<<endl;
//    adjgraph.BFSTraverse();
//    cout<<endl;
    
    AdjGraph<int> adjgraph1(6);
    adjgraph1.setEdge(0, 2, 1);
    adjgraph1.setEdge(0, 1, 6);
    adjgraph1.setEdge(0, 3, 5);
    adjgraph1.setEdge(1, 2, 5);
    adjgraph1.setEdge(2, 3, 5);      //要多加边
    adjgraph1.setEdge(1, 4, 3);
    adjgraph1.setEdge(2, 4, 6);
    adjgraph1.setEdge(2, 5, 4);
    adjgraph1.setEdge(3, 5, 2);
    adjgraph1.setEdge(4, 5, 6);
    adjgraph1.setEdge(2, 0, 1);
    adjgraph1.setEdge(1, 0, 6);
    adjgraph1.setEdge(3, 0, 5);
    adjgraph1.setEdge(2, 1, 5);
    adjgraph1.setEdge(3, 2, 5);      //要多加边
    adjgraph1.setEdge(4, 1, 3);
    adjgraph1.setEdge(4, 2, 6);
    adjgraph1.setEdge(5, 2, 4);
    adjgraph1.setEdge(5, 3, 2);
    adjgraph1.setEdge(5, 4, 6);
//    for(int i = 0; i<5; i++){
//        cout<<"起点为"<<adjgraph1.Prim(0)[i].start<<" 终点为"<<adjgraph1.Prim(0)[i].end<<" 权值为";
//        cout<<adjgraph1.Prim(0)[i].weight<<endl;
//    }

    cout<<endl;
    for(int i = 0; i<5; i++){
        cout<<"起点为"<<adjgraph1.Kruskal()[i].start<<" 终点为"<<adjgraph1.Kruskal()[i].end<<" 权值为"<<adjgraph1.Kruskal()[i].weight<<endl;
    }
    
    cout<<endl;
    for(int i = 0; i<5; i++){
        cout<<"起点为"<<adjgraph1.DestroyCircle()[i].start<<" 终点为"<<adjgraph1.DestroyCircle()[i].end<<" 权值为"<<adjgraph1.DestroyCircle()[i].weight<<endl;
    }
//
    AdjGraph<int> adjgraph2(6);
    adjgraph2.setEdge2(0, 1, 12);
    adjgraph2.setEdge2(1, 2, 5);
    adjgraph2.setEdge2(0, 2, 10);
    adjgraph2.setEdge2(0, 5, 100);
    adjgraph2.setEdge2(0, 4, 30);
    adjgraph2.setEdge2(2, 3, 50);
    adjgraph2.setEdge2(3, 5, 10);
    adjgraph2.setEdge2(4, 5, 60);
    adjgraph2.setEdge2(4, 3, 20);
    int Path2[6]={0};
    int D2[6]={0};
    adjgraph2.Dijkstra(0, D2, Path2);
    for(int i = 0; i<6; i++){
        cout<<D2[i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i<6; i++){
        cout<<Path2[i]<<" ";
    }

    AdjGraph<int> adjgraph3(3);
    adjgraph3.setEdge2(0, 2, 5);
    adjgraph3.setEdge2(2, 0, 2);
    adjgraph3.setEdge2(2, 1, 13);
    adjgraph3.setEdge2(1, 2, 6);
    adjgraph3.setEdge2(0, 1, 10);
    adjgraph3.setEdge2(1, 0, 9);
    int Adj[3][3]={0};
    int Path3[3][3]={0};
    adjgraph3.Floyd((int **)Adj,(int **)Path3);
    
    cout<<endl<<endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            cout<<Adj[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            cout<<Path3[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
    int SortArray[3]={0};
    if (!adjgraph3.ToplogySort(SortArray))
    {
        cout<<"存在"<< endl;
    }
    else{
        cout<<"不存在"<< endl;
        for(int i=0; i<3; i++){
            cout<<SortArray[i]<<" ";
        }
    }
  
    return 0;
}
