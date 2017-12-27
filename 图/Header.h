//
//  Header.h
//  图
//
//  Created by 唐昊杰 on 17/12/13.
//  Copyright © 2017年 唐昊杰. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
using namespace std;

template<class T>
class MinHeap{
private:
    T* heapArray;
    int CurrentSize;
    int MaxSize;
public:
    MinHeap(int size){
        heapArray = new T[size];
        MaxSize = size;
        CurrentSize = 0;
    };
    ~MinHeap(){};
    void BuildHeap(T a[],int na);
    bool Insert(T x);
    void ShiftDown(int i);
    void ShiftUp(int i);
    void DeleteTop();
    void MoveTop();
    void Show();
    bool isEmpty(){
        if(CurrentSize == 0)
            return true;
        else return false;
    }
    T ReturnMin(){
        return heapArray[0];
    }
};

template<class T>
void MinHeap<T>::Show(){
    for(int i=0;i<CurrentSize;i++){
        cout<<heapArray[i]<<" ";
    }
}

template<class T>
void MinHeap<T>::MoveTop(){
    T temp = heapArray[0];
    heapArray[0] = heapArray[CurrentSize - 1];
    heapArray[CurrentSize - 1] = temp;
}

template<class T>
void MinHeap<T>::DeleteTop(){
    MoveTop();
    CurrentSize --;
    int i = 0;
    ShiftDown(i);
}

template<class T>
void MinHeap<T>::ShiftUp(int i){
    while(i>0){
        int parent = (i-1)/2;
        if(heapArray[i] < heapArray[parent]){
            T temp = heapArray[parent];
            heapArray[parent] = heapArray[i];
            heapArray[i] = temp;
            i = parent;
        }
        else break;
    }
}

template<class T>
bool MinHeap<T>::Insert(T x){
    if(CurrentSize+1 > MaxSize){
        cout<<"堆溢出"<<endl;
        return false;
    }
    
    CurrentSize++;
    heapArray[CurrentSize - 1] = x;
    int i = CurrentSize - 1;
    ShiftUp(i);
    return true;
}

template<class T>
void MinHeap<T>::BuildHeap(T a[],int na){
    heapArray = a;
    CurrentSize = na;
    for(int i = (CurrentSize - 2)/2;i >= 0;i--){
        ShiftDown(i);
    }
}

template<class T>
void MinHeap<T>::ShiftDown(int i){
    while(1){
        int leftchild = 2*i + 1;
        int rightchild = 2*i + 2;
        if(leftchild < CurrentSize){
            if(rightchild < CurrentSize && heapArray[leftchild] > heapArray[rightchild]){
                if(heapArray[i] > heapArray[rightchild]){
                    T temp = heapArray[i];
                    heapArray[i] = heapArray[rightchild];
                    heapArray[rightchild] = temp;
                    i = rightchild;
                }
                else break;
            }
            else{
                if(heapArray[i] > heapArray[leftchild]){
                    T temp = heapArray[i];
                    heapArray[i] = heapArray[leftchild];
                    heapArray[leftchild] = temp;
                    i = leftchild;
                }
                else break;
            }
        }
        else break;
    }
}




template<class T>
class MaxHeap
{
private:
    T * heapArray;
    int CurrentSize;
    int MaxSize;
public:
    MaxHeap(int N);
    void BuildHeap();
    bool Insert(T N);
    void RemoveMax();
    void SiftDown(int left);
    void SiftUp(int position);
    bool IsEmpty();
    T GetMax();
};
template<class T>
MaxHeap<T>::MaxHeap(int N)
{
    MaxSize = N;
    heapArray = new T[MaxSize];
    CurrentSize = 0;
}
template<class T>
T MaxHeap<T>::GetMax()
{
    return heapArray[0];
}
template<class T>
bool MaxHeap<T>::IsEmpty()
{
    if(CurrentSize == 0)
        return 1;
    else
        return 0;
}
template<class T>
void MaxHeap<T>::RemoveMax()
{
    if (CurrentSize>0)
    {
        CurrentSize--;
        heapArray[0] = heapArray[CurrentSize];
        SiftDown(0);
    }
    else
    {
        cout<<"∂—ø’"<<endl;
    }
}
template<class T>
void MaxHeap<T>::BuildHeap()
{
    for (int i = CurrentSize/2-1 ; i >=0 ; i--)
    {
        SiftDown(i);
    }
}

template<class T>
void MaxHeap<T>::SiftDown(int left)
{
    int i = left;
    int j = 2*i +1;
    T temp = heapArray[i];
    while (j < CurrentSize)
    {
        if ((j < CurrentSize-1)&&(heapArray[j].weight< heapArray[j+1].weight))
        {
            j++;
        }
        if (temp.weight<heapArray[j].weight)
        {
            heapArray[i] = heapArray[j];
            heapArray[j] = temp;
            i = j;
            j = 2*j + 1;
        }
        else
            break;
    }
    heapArray[i] = temp;
}
template<class T>
void MaxHeap<T>::SiftUp(int position)
{
    int i = position;
    int j = (i-1)/2;
    T temp = heapArray[i];
    while (heapArray[j].weight < heapArray[i].weight)
    {
        temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
        i = j;
        j = (i-1)/2;
    }
    heapArray[i] = temp;
}
template<class T>
bool MaxHeap<T>::Insert(T N)
{
    if (CurrentSize<MaxSize)
    {
        CurrentSize++;
        heapArray[CurrentSize-1] = N;
        SiftUp(CurrentSize-1);
        return 1;
    }
    else
    {
        cout<<"溢出"<<endl;
        return 0;
    }
}
#endif /* Header_h */
