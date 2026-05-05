#include <iostream>
#include <string>
class Sorter{
private:
    std::string method;
public:
    Sorter(std::string method):method(method){};
    void sort(int* arr,int size){
        if(method=="quick"){
            //퀵 정렬
        }
        else if(method=="merge"){
            //병합 정렬
        }
        else if(method=="bubble"){
            //버블 정렬
        }
    }
};

int main(){
    int arr[] = {5,3,2,1,4};
    Sorter s1("bubble");
    Sorter s2("quick");
    Sorter s3("merge");
    
    s1.sort(arr,5);
    s2.sort(arr,5);
    s3.sort(arr,5);

    return 0;
}