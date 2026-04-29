#include <iostream>
#include "my_string.h"



int main(){
    // 현재 unit test C++ 코드 작성 중 대체 예정
    MyString mystr("aab");
    
    mystr+="aba";
    mystr.printlnStr();
    std::cout << mystr.in("baba")<<std::endl;
    std::cout << (mystr<"aaaba") <<std::endl;
    std::cout << (mystr>"aaaba")<<std::endl;
    std::cout << (mystr=="aaaba")<<std::endl;
    std::cout << (mystr=="aababa")<<std::endl;
    std::cout << mystr.getLen() << std::endl;


    return  0;
}