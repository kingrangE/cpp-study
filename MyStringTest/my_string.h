class MyString{
    char *content;
    int str_length;
    public:
        MyString(char c);
        MyString(const char *str);
        MyString(const MyString& str);
        ~MyString();
        MyString& operator+=(const char *str); // 문자열 뒤에 다른 문자열 붙이기
        bool operator==(const char *str); // 문자열이 같은지 비교하기
        bool operator>(const char *str); // 문자열 크기 비교하기
        bool operator<(const char *str); // 문자열 크기 비교하기
        bool inStr(const char *str); // 문자열 내에 포함되어 있는 문자열 구하기
        int getLen() const;
        void printContent();
};
