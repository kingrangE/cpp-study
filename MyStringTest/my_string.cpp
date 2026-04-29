#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(char c){
    contents = new char[1]; // 문자로 생성하므로 길이 1
    contents[0] = c;
    str_length = 1;
    capacity = 1;
}
MyString::MyString(const char *str){
    str_length = strlen(str); // 문자 배열 길이 파악
    capacity = str_length;
    contents = new char[str_length]; // 해당 길이만큼 할당
    for(int i = 0; i<str_length; i++){ // 깊은 복사
        contents[i] = str[i];
    }
}
MyString::MyString(const MyString& str){
    str_length = str.getLen(); // 문자열 길이 복사
    capacity = str_length;
    contents = new char[str_length]; // 해당 길이만큼 할당
    for(int i = 0; i<str_length; i++){ // 깊은 복사
        contents[i] = str.at(i);
    }
}
MyString::~MyString(){
    delete[] contents; 
}
void MyString::printStr(){
    for(int i = 0; i < str_length; i++){ 
        std::cout << contents[i];
    }
} 
void MyString::printlnStr(){
    for(int i = 0; i < str_length; i++){
        std::cout << contents[i];
    }
    std::cout<<std::endl;
}
int MyString::getLen() const{
    return str_length;
} 
int MyString::getCapacity() const{
    return capacity;
}

MyString& MyString::append(const MyString& str){ 
    int tmp_length = str_length; // 기존 길이 저장 
    char *tmp = new char[tmp_length]; // 임시 배열 할당 
    //기존 값 임시 배열에 복사 
    for(int i = 0; i < tmp_length; i++){ 
        tmp[i] = contents[i]; 
    } 

    delete[] contents; // 기존에 있던 배열 메모리 해제 

    str_length += str.getLen(); // 둘이 합쳐야 하므로 더한 크기로 갱신 

    contents = new char[str_length]; // 갱신된 길이만큼 새로운 배열 할당 

    for(int i = 0; i < tmp_length; i++){ // 기존 값 복사 
        contents[i] = tmp[i]; 
    } 
    for(int i = tmp_length; i < str_length; i++){ // 새로운 값 뒤에 복사 
        contents[i] = str.at(i-tmp_length); 
    } 

    delete[] tmp; // 임시 배열 메모리 해제 

    return *this; // 레퍼런스 반환 
}

int MyString::in(const MyString& str){ 
    // 인자로 받은 문자열 길이 측정 
    const int inner_str_length = str.getLen(); 

    // 더 길면 원본 문자열이 포함할 수 없음
    if (inner_str_length > str_length) return -1; 

    // 반복을 위한 각 idx 설정 
    int idx = 0; 
    int inner_idx = 0; 
    
    while(idx<str_length){ 
        if (contents[idx] == str.at(inner_idx)){ 
            //둘이 같으면 둘 다 인덱스 이동 
            idx += 1; 
            inner_idx += 1; 
            if (inner_idx == inner_str_length) return idx-inner_idx; 
        }else{
            //둘이 다르면 
            idx = idx-inner_idx+1; // 매칭 시작된 지점 다음부터 다시 검사 
            inner_idx = 0; // inner_idx 다시 초기화 
        } 
    }
    return -1; // 전부 돌았는데 못 찾으면 false 
}
bool MyString::same(const MyString& str){ 
    // 길이가 다르면 무조건 다르다. 
    if(str.getLen() != str_length) return false; 
    // 반복하며 하나씩 비교한다. 
    for(int i = 0; i < str_length; i++){ 
        if(contents[i] != str.at(i)) return false; // 다르면 종료 
    }
    return true; //모두 통과했다면 일치하는 것이다. 
}
int MyString::compare(const MyString& str){ 
    // 둘이 같은지 먼저 검사 
    if (same(str)) return 0; 
        //둘 중 더 작은 길이 찾기 
    int compare_length = str.getLen(); 
    int MIN_SIZE = std::min(compare_length, str_length); // strlen은 unsigned 정수인 size_t를 반환하므로 int로 형변환해서 맞춰준다. 
    int idx = 0; 
    while(idx < MIN_SIZE){
        if(str.at(idx) < contents[idx]) return 1; // 원본이 더 크면 1
        else if(str.at(idx) > contents[idx]) return -1; // 원본이 더 작으면 -1
        idx += 1;
    }
    //이곳까지 내려왔다면 비교할 수 있는 길이에서는 같은 것이다. 따라서 둘 중 더 긴 것이 더 크다. 
    if (compare_length < str_length) return 1; // 원본이 더 길면 1 
    else return -1; // 원본이 더 짧으면 -1; 
}

MyString& MyString::assign(const MyString& str){
    const int NEW_LENGTH = str.getLen();
    if(NEW_LENGTH > capacity){ // capacity와 비교
        delete[] contents;
        contents = new char[NEW_LENGTH];
        capacity = NEW_LENGTH; // capacity가 더 커졌으므로 갱신
    }

    for(int i = 0; i < NEW_LENGTH; i++){
        contents[i] = str.at(i);
    }

    str_length = NEW_LENGTH;
    return *this;
}

MyString& MyString::insert(const int pos, const char c){
    if(pos<0 || pos > str_length) return *this; // 잘못된 위치에 삽입 시 무시
    const int NEW_LENGTH = str_length + 1; 
    if(capacity < NEW_LENGTH){ // 현재 가진 메모리보다 더 크면 갱신 
        capacity = NEW_LENGTH; 
    } 

    char *new_char = new char[capacity]; 
    for(int i = 0; i < pos; i++){ // 삽입 위치전까지 복사 
        new_char[i] = contents[i]; 
    } 

    new_char[pos] = c; // 삽입 위치에 삽입 

    for(int i = pos+1; i<NEW_LENGTH; i++){ // 삽입 이후 기존 값 다시 복사 
        new_char[i] = contents[i-1]; 
    } 

    delete[] contents; // 기존 배열 메모리 해제 

    contents = new_char; // 새로운 배열로 연결 
    str_length = NEW_LENGTH; 

    return *this; 
}
MyString& MyString::insert(const int pos, const char* str){
    if(pos<0 || pos > str_length) return *this; // 잘못된 위치에 삽입 시 무시
    const int insert_len = strlen(str); 
    const int NEW_LENGTH = str_length + insert_len; 

    if(capacity < NEW_LENGTH){ // 현재 가진 메모리보다 더 크면 갱신 
        capacity = NEW_LENGTH; 
    } 

    char *new_char = new char[capacity]; 

    for(int i = 0; i < pos; i++){ // 삽입 위치전까지 복사 
        new_char[i] = contents[i]; 
    } 

    for(int i = pos; i < pos + insert_len; i++){ // 새로운 문자열 복사 
        new_char[i] = str[i-pos]; 
    } 
    for(int i = pos+insert_len; i<NEW_LENGTH; i++){ // 삽입 이후 기존 값 다시 복사
        new_char[i] = contents[i-insert_len];
    } 

    delete[] contents; // 기존 배열 메모리 해제 
    contents = new_char; // 새로운 배열로 연결 
    str_length = NEW_LENGTH; 

    return *this; 
}
MyString& MyString::insert(const int pos, const MyString& str){ 
    if(pos<0 || pos >= str_length) return *this; // 잘못된 위치에 삽입 시 무시
    const int NEW_LENGTH = str_length + str.getLen(); 
    if(capacity < NEW_LENGTH){ // 현재 가진 메모리보다 더 크면 갱신 
        capacity = NEW_LENGTH; 
    } 
    char *new_char = new char[capacity]; 

    for(int i = 0; i < pos; i++){ // 삽입 위치전까지 복사 
        new_char[i] = contents[i]; 
    } 
    for(int i = pos; i < pos + str.getLen(); i++){ // 새로운 문자열 복사 
        new_char[i] = str.at(i-pos); 
    } 
    for(int i = pos + str.getLen(); i < NEW_LENGTH; i++){ // 삽입 이후 기존 값 다시 복사
        new_char[i] = contents[i-str.getLen()];
    } 
    delete[] contents; // 기존 배열 메모리 해제 
    contents = new_char; // 새로운 배열로 연결 
    str_length = NEW_LENGTH; 

    return *this; 
}
MyString& MyString::join(const char char_array[]){ 
    // 총 길이 계산 
    const int array_length = strlen(char_array); 
    // 자기 자신이 n길이의 배열에서 n-1번 들어가기 때문에 곱연산 
    const int FULL_LENGTH = array_length + (array_length-1) * str_length; 
    // 현재 자신에게 할당된 메모리 크기와 비교하여 할당 진행 
    if(FULL_LENGTH > capacity){ 
        capacity = FULL_LENGTH; //capacity 갱신 
    } 
    char *new_char = new char[capacity]; 

    for(int i = 0; i<array_length-1; i++){ 
        // n길이의 배열일 때, n-1번 반복하도록 
        int start_idx = i*str_length+i; // 반복 중 시작 인덱스 
        new_char[start_idx] = char_array[i]; 
        for(int j = start_idx+1; j < start_idx+1+str_length;j++){ 
            new_char[j] = contents[j-start_idx-1]; 
        } 
    } 

    //위 과정이 모두 끝나면 마지막 char_array값 넣기 
    new_char[FULL_LENGTH-1] = char_array[array_length-1]; //마지막 위치는 당연히 맨 뒤 

    delete[] contents; // 기존 배열 메모리 해제 
    contents = new_char; // 새로운 배열로 연결 
    str_length = FULL_LENGTH; // 길이 갱신 

    return *this; 
}

char MyString::at(const int idx)const{
	if(idx<0 || idx>str_length) return '\0'; //범위 벗어나면 널 문자 반환
    return contents[idx]; // 그게 아니면 해당 위치 문자 반환
}

MyString& MyString::erase(int pos){
	if(pos<0 || pos >= str_length) return *this; // 잘못된 위치에 삽입 시 무시
    const int new_length = str_length-1; // 1개 줄어들 예정
    char *new_str = new char[new_length];

    for(int i = 0; i<pos; i++){ //pos 전까지 복사
    	new_str[i] = contents[i];
    }

    for(int i = pos+1; i < str_length; i++){
    	new_str[i-1] = contents[i];//pos 다음 것부터 끝까지 복사
    }

    delete[] contents; // 기존 배열 메모리 해제
    contents = new_str; // 새로운 배열로 연결
    str_length = new_length; // 길이 갱신

    return *this;
}

MyString& MyString::erase(int pos, int count){
    if(pos<0 || pos >= str_length) return *this; // 잘못된 위치에 삽입 시 무시
    const int new_length = str_length - count; // count개 줄어들 예정
    char *new_str = new char[new_length];

    for(int i = 0; i<pos; i++){ //pos 전까지 복사
    	new_str[i] = contents[i];
    }

    for(int i = pos+count; i < str_length; i++){
    	new_str[i-count] = contents[i];//pos로부터 count 다음 것부터 끝까지 복사
    }

    delete[] contents; // 기존 배열 메모리 해제
    contents = new_str; // 새로운 배열로 연결
    str_length = new_length; // 길이 갱신

    return *this;
}

MyString& MyString::replace(const MyString& target, const MyString& new_str){ 
    //존재 여부 먼저 확인 -> 없으면 그냥 그대로 리턴하면 된다.
    int idx = in(target);
    while(idx!=-1){
    	//idx가 계속 존재하는 동안 진행 (타겟이 겹치는 위치를 찾았다면)
        //타겟을 없애고 new_str을 넣는다.
        erase(idx,target.getLen()); //해당 길이만큼 삭제
        //삭제했으면 추가도 해줘야함.
        insert(idx,new_str);
        idx = in(target);
    }
    //더이상 없으면 나올 것이고 레퍼런스 반환
    return *this;
}

MyString& MyString::operator+=(const MyString& str){
    int tmp_length = str_length; // 기존 길이 저장 
    char *tmp = new char[tmp_length]; // 임시 배열 할당 
    //기존 값 임시 배열에 복사 
    for(int i = 0; i < tmp_length; i++){ 
        tmp[i] = contents[i]; 
    } 

    delete[] contents; // 기존에 있던 배열 메모리 해제 

    str_length += str.str_length; // 둘이 합쳐야 하므로 더한 크기로 갱신 

    contents = new char[str_length]; // 갱신된 길이만큼 새로운 배열 할당 

    for(int i = 0; i < tmp_length; i++){ // 기존 값 복사 
        contents[i] = tmp[i]; 
    } 
    for(int i = tmp_length; i < str_length; i++){ // 새로운 값 뒤에 복사 
        contents[i] = str.contents[i-tmp_length]; 
    } 

    delete[] tmp; // 임시 배열 메모리 해제 

    return *this; // 레퍼런스 반환 
}


bool MyString::operator==(const char *str){
    //길이 다르면 무조건 같을 수 없음
    if (strlen(str) != str_length) return false; 
    //길이 같으면 하나하나 비교
    for(int i=0; i<str_length;i++){
        // 문자 다르면 false 리턴
        if(contents[i] != str[i]) return false;
    }
    return true; //모두 같으면 true
}
bool MyString::operator>(const char *str){
    int idx = 0;
    // 둘 중 더 짧은 것 찾기
    const int MAX_IDX = std::min((int)strlen(str),str_length);
    //문자열 크기 비교
    while(idx < MAX_IDX){
        if (str[idx] > contents[idx]) return false;
        else if(str[idx] < contents[idx]) return true;
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
        if (str[idx] < contents[idx]) return false;
        else if(str[idx] > contents[idx]) return true;
        idx += 1;
    }
    //여기까지 왔으면 일단 존재하는 문자열은 같은 것 -> 더 긴게 큼
    if (strlen(str) <= str_length){
        return false;
    }
    return true;
}