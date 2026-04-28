#include <iostream>
#include "my_string.h"

int main(){
    MyString mystr("aab");
    
    mystr+="aba";
    mystr.printContent();
    std::cout << mystr.inStr("baba")<<std::endl;
    std::cout << (mystr<"aaaba") <<std::endl;
    std::cout << (mystr>"aaaba")<<std::endl;
    std::cout << (mystr=="aaaba")<<std::endl;
    std::cout << (mystr=="aababa")<<std::endl;
    std::cout << mystr.getLen() << std::endl;


    return  0;
}