#include <iostream>
#include <string>
class SortStrategy{
public:
    virtual void sort(int* arr,int size)=0;
    virtual ~SortStrategy(){}
};
class QuickSort: public SortStrategy{
public:
    void sort(int* arr, int size) override{
        //퀵 정렬 코드
    }
};
class MergeSort: public SortStrategy{
public:
    void sort(int* arr, int size) override{
        //병합 정렬 코드
    }
};
class BubbleSort: public SortStrategy{
public:
    void sort(int* arr, int size) override{
        //버블 정렬 코드
    }
};
class Sorter{
private:
    SortStrategy* s;
public:
    Sorter(SortStrategy* s):s(s){}
    void sort(int* arr, int size){
        s->sort(arr,size);
    }
};

int main(){
    int arr[] = {5,3,2,1,4};
    
    Sorter s(new QuickSort());
    s.sort(arr,5);

    //근데 갑자기 버블 정렬 써야한다면
    Sorter s2(new BubbleSort());
    s2.sort(arr,5); //그냥 버블 정렬 쓰는 Sort로 생성 (기존 코드 수정 X)

    return 0;
}