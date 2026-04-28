#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(char c){
    content = new char[1]; // 문자로 생성하므로 길이 1
    content[0] = c;
    str_length = 1;
}
MyString::MyString(const char *str){
    str_length = strlen(str); // 문자 배열 길이 파악
    content = new char[str_length]; // 해당 길이만큼 할당
    for(int i = 0; i<str_length; i++){ // 깊은 복사
        content[i] = str[i];
    }
}
MyString::MyString(const MyString& str){
    str_length = str.str_length; // 문자열 길이 복사
    content = new char[str_length]; // 해당 길이만큼 할당
    for(int i = 0; i<str_length; i++){ // 깊은 복사
        content[i] = str.content[i];
    }
}
MyString::~MyString(){
    delete[] content; 
}
MyString& MyString::operator+=(const char *str){
    int exist_length = str_length;
    char *tmp_str = new char[exist_length]; // 임시 저장 배열
    for(int i = 0; i<exist_length; i++){ // 임시 저장 복사
        tmp_str[i] = content[i];
    }
    str_length += strlen(str);
    delete[] content; 
    content = new char[str_length]; // 새로운 값을 넣기 위해 배열 생성
    for(int i = 0; i<exist_length; i++){ // 임시 저장해둔거 가져오기
        content[i] = tmp_str[i];
    }
    for(int i = exist_length; i<str_length; i++){ // 뒤에 이어붙이기
        content[i] = str[i-exist_length];
    }   
    delete[] tmp_str;

    return *this;
}
bool MyString::operator==(const char *str){
    //길이 다르면 무조건 같을 수 없음
    if (strlen(str) != str_length) return false; 
    //길이 같으면 하나하나 비교
    for(int i=0; i<str_length;i++){
        // 문자 다르면 false 리턴
        if(content[i] != str[i]) return false;
    }
    return true; //모두 같으면 true
}
bool MyString::operator>(const char *str){
    int idx = 0;
    // 둘 중 더 짧은 것 찾기
    const int MAX_IDX = std::min((int)strlen(str),str_length);
    //문자열 크기 비교
    while(idx < MAX_IDX){
        if (str[idx] > content[idx]) return false;
        else if(str[idx] < content[idx]) return true;
        idx += 1;
    }
    //여기까지 왔으면 일단 존재하는 문자열은 같은 것 -> 더 긴게 큼
    if (strlen(str) >= str_length){
        return false;
    }
    return true;
}
bool MyString::operator<(const char *str){
    int idx = 0;
    // 둘 중 더 짧은 것 찾기
    const int MAX_IDX = std::min((int)strlen(str),str_length);
    //문자열 크기 비교
    while(idx < MAX_IDX){
        if (str[idx] < content[idx]) return false;
        else if(str[idx] > content[idx]) return true;
        idx += 1;
    }
    //여기까지 왔으면 일단 존재하는 문자열은 같은 것 -> 더 긴게 큼
    if (strlen(str) <= str_length){
        return false;
    }
    return true;
}
bool MyString::inStr(const char *str){
    //포함 여부 
    int input_length = strlen(str);
    if(input_length > str_length) return false; // 더 길면 애초에 포함 안됨
    bool check = false;
    int idx = 0;
    int inner_idx = 0;
    while(idx<str_length){
        if (content[idx] == str[inner_idx]){
            idx++;
            inner_idx++;
            if(input_length-1 == inner_idx) return true;
        }else{
            idx = idx-inner_idx+1;
            inner_idx=0;
        }
    }
    return false;
}
int MyString::getLen()const{
    return str_length;
}
void MyString::printContent(){
    for(int i = 0; i<str_length;i++){
        std::cout << content[i];
    }
    std::cout << std::endl;
}