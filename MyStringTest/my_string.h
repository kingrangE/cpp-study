class MyString{
    char *contents;
    int str_length;
    int capacity;
    public:
        MyString(char c);
        MyString(const char *str);
        MyString(const MyString& str);
        ~MyString();
        void printStr(); // 개행 문자 X 
        void printlnStr(); // 개행 문자 O 
        int getLen() const;
        int getCapacity() const;
        MyString& append(const MyString& str); 
        int in(const MyString& str);
        bool same(const MyString& str); 
        int compare(const MyString& str); 
        MyString& assign(const MyString& str);
        MyString& insert(int pos, char c); 
        MyString& insert(int pos, const char *str); 
        MyString& insert(int pos, const MyString& str);
        MyString& join(const char char_array[]);
        char at(int idx) const;
        MyString& erase(int pos); // 특정 위치 값 1개
        MyString& erase(int pos, int count); // 특정 위치와 개수를 동시에
        MyString& replace(const MyString& target, const MyString& new_str); 
        MyString& operator+=(const MyString& str); // 문자열 뒤에 다른 문자열 붙이기
        bool operator==(const char *str); // 문자열이 같은지 비교하기
        bool operator>(const char *str); // 문자열 크기 비교하기
        bool operator<(const char *str); // 문자열 크기 비교하기
};
