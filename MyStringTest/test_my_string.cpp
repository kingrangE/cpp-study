#include <iostream>
#include <cstring>
#include "my_string.h"

static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

// 결과가 TRUE가 맞는지 검사
#define ASSERT_TRUE(expr) do { \
    total_tests++; \
    if (expr) { passed_tests++; } \
    else { \  
        failed_tests++; \
        std::cout << "  [FAIL] " << __FILE__ << ":" << __LINE__ \
                  << " - ASSERT_TRUE(" << #expr << ")" << std::endl; \
    } \
} while(0)

// FALSE가 맞는지 검사(TRUE 함수를 반대로 재사용)
#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))

// 두 값이 동일한지 검사
#define ASSERT_EQ(a, b) do { \
    total_tests++; \
    if ((a) == (b)) { passed_tests++; } \
    else { \
        failed_tests++; \
        std::cout << "  [실패] " << __FILE__ << ":" << __LINE__ \
                  << " - ASSERT_EQ(" << #a << ", " << #b << ") => " \
                  << (a) << " != " << (b) << std::endl; \
    } \
} while(0)

// 함수를 실제로 실행하는 부분
#define RUN_TEST(func) do { \
    int before_fail = failed_tests; \
    std::cout << "[RUN ] " << #func << std::endl; \
    func(); \
    if (failed_tests == before_fail) \
        std::cout << "[PASS] " << #func << std::endl; \
    else \
        std::cout << "[FAIL] " << #func << std::endl; \
} while(0)


void test_constructor_char() {
    MyString s('A');
    
    ASSERT_EQ(s.getLen(), 1);
    ASSERT_EQ(s.at(0), 'A');
}

void test_constructor_cstring() {
    MyString s("hello");
    ASSERT_EQ(s.getLen(), 5);
    ASSERT_EQ(s.at(0), 'h');
    ASSERT_EQ(s.at(4), 'o');
}

void test_constructor_empty_string() {
    MyString s("");
    ASSERT_EQ(s.getLen(), 0);
}

void test_copy_constructor() {
    MyString original("abc");
    // 복사 생성자
    MyString copy(original);
    
    // 복사가 잘 되었는지 확인
    ASSERT_EQ(copy.getLen(), 3);
    ASSERT_EQ(copy.at(0), 'a');
    ASSERT_EQ(copy.at(1), 'b');
    ASSERT_EQ(copy.at(2), 'c');
}

void test_copy_constructor_independence() {
    MyString original("abc");
    MyString copy(original);
    original.assign(MyString("xyz"));

    // 복사 본에 영향이 없는지 확인
    ASSERT_EQ(copy.at(0), 'a');
    ASSERT_EQ(copy.getLen(), 3);
}

//getLen
void test_getLen() {
    MyString s1("hi");
    ASSERT_EQ(s1.getLen(), 2);

    MyString s2("hello world");
    ASSERT_EQ(s2.getLen(), 11);
}

// at 
void test_at_valid_index() {
    MyString s("abcde");
    ASSERT_EQ(s.at(0), 'a');
    ASSERT_EQ(s.at(2), 'c');
    ASSERT_EQ(s.at(4), 'e');
}

void test_at_invalid_index() {
    MyString s("abc");
    ASSERT_EQ(s.at(-1), '\0');
    ASSERT_EQ(s.at(10), '\0');
}

// append
void test_append_basic() {
    MyString s("hello");
    s.append(MyString(" world"));
    ASSERT_EQ(s.getLen(), 11);
    ASSERT_EQ(s.at(5), ' ');
    ASSERT_EQ(s.at(6), 'w');
    ASSERT_TRUE(s == "hello world");
}

void test_append_empty() {
    MyString s("abc");
    s.append(MyString(""));
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "abc");
}

void test_append_to_empty() {
    MyString s("");
    s.append(MyString("xyz"));
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "xyz");
}

// assign
void test_assign_shorter_to_longer() {
    MyString s("hi");
    s.assign(MyString("hello world"));
    ASSERT_EQ(s.getLen(), 11);
    ASSERT_TRUE(s == "hello world");
}

void test_assign_longer_to_shorter() {
    MyString s("hello world");
    s.assign(MyString("hi"));
    ASSERT_EQ(s.getLen(), 2);
    ASSERT_TRUE(s == "hi");
}

void test_assign_same_length() {
    MyString s("abc");
    s.assign(MyString("xyz"));
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "xyz");
}

// in
void test_in_found() {
    MyString s("hello world");
    int result = s.in(MyString("world"));
    ASSERT_EQ(result, 6); // "world"는 인덱스 6에서 시작
}

void test_in_found_at_start() {
    MyString s("hello world");
    int result = s.in(MyString("hello"));
    ASSERT_EQ(result, 0);
}

void test_in_not_found() {
    MyString s("hello");
    int result = s.in(MyString("xyz"));
    ASSERT_EQ(result, -1);
}

void test_in_longer_than_original() {
    // 검색 문자열이 원본보다 긴 경우
    MyString s("hi");
    int result = s.in(MyString("hello"));
    ASSERT_EQ(result, -1);
}

void test_in_partial_match() {
    // 부분 일치하는 경우
    MyString s("aab");
    int result = s.in(MyString("aac"));
    ASSERT_EQ(result, -1);
}

// same
void test_same_equal() {
    MyString s("hello");
    ASSERT_TRUE(s.same(MyString("hello")));
}

void test_same_different() {
    MyString s("hello");
    ASSERT_FALSE(s.same(MyString("world")));
}

void test_same_different_length() {
    MyString s("hello");
    ASSERT_FALSE(s.same(MyString("hell")));
}

void test_same_same_length_different_content() {
    // 길이는 같지만 내용이 다른 경우
    MyString s("abc");
    ASSERT_FALSE(s.same(MyString("abd")));
}

// compare
void test_compare_equal() {
    MyString s("hello");
    ASSERT_EQ(s.compare(MyString("hello")), 0);
}

void test_compare_greater() {
    // "b" > "a" 이므로 원본이 더 큼 -> 1
    MyString s("b");
    ASSERT_EQ(s.compare(MyString("a")), 1);
}

void test_compare_less() {
    // "a" < "b" 이므로 원본이 더 작음 -> -1
    MyString s("a");
    ASSERT_EQ(s.compare(MyString("b")), -1);
}

void test_compare_prefix_longer() {
    // "abc" vs "ab": 같은 접두사, 원본이 더 김 -> 1
    MyString s("abc");
    ASSERT_EQ(s.compare(MyString("ab")), 1);
}

void test_compare_prefix_shorter() {
    // "ab" vs "abc": 같은 접두사, 원본이 더 짧음 -> -1
    MyString s("ab");
    ASSERT_EQ(s.compare(MyString("abc")), -1);
}

// insert
void test_insert_char_middle() {
    MyString s("abcd");
    s.insert(2, 'X');
    ASSERT_EQ(s.getLen(), 5);
    ASSERT_TRUE(s == "abXcd");
}

void test_insert_char_start() {
    MyString s("abc");
    s.insert(0, 'X');
    ASSERT_EQ(s.getLen(), 4);
    ASSERT_TRUE(s == "Xabc");
}

void test_insert_char_invalid_pos() {
    // 범위 밖 삽입 시 변경 없어야 함
    MyString s("abc");
    s.insert(-1, 'X');
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "abc");

    s.insert(10, 'X');
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "abc");
}

void test_insert_cstring_middle() {
    MyString s("abcd");
    s.insert(2, "XY");
    ASSERT_EQ(s.getLen(), 6);
    ASSERT_TRUE(s == "abXYcd");
}

void test_insert_mystring_middle() {
    MyString s("abcd");
    MyString ins("XY");
    s.insert(2, ins);
    ASSERT_EQ(s.getLen(), 6);
    ASSERT_TRUE(s == "abXYcd");
}

// erase
void test_erase_single_start() {
    MyString s("abcd");
    s.erase(0);
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "bcd");
}

void test_erase_single_middle() {
    MyString s("abcd");
    s.erase(1);
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "acd");
}

void test_erase_single_end() {
    MyString s("abcd");
    s.erase(3);
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "abc");
}

void test_erase_single_invalid() {
    MyString s("abc");
    s.erase(-1);
    ASSERT_EQ(s.getLen(), 3);
    s.erase(5);
    ASSERT_EQ(s.getLen(), 3);
}

void test_erase_count() {
    MyString s("abcdef");
    s.erase(1, 3); // "a" + "ef" = "aef"
    ASSERT_EQ(s.getLen(), 3);
    ASSERT_TRUE(s == "aef");
}

void test_erase_count_from_start() {
    MyString s("abcdef");
    s.erase(0, 2); // "cdef"
    ASSERT_EQ(s.getLen(), 4);
    ASSERT_TRUE(s == "cdef");
}

// replace
void test_replace_single_occurrence() {
    MyString s("hello world");
    s.replace(MyString("world"), MyString("there"));
    ASSERT_TRUE(s == "hello there");
}

void test_replace_no_match() {
    MyString s("hello");
    s.replace(MyString("xyz"), MyString("abc"));
    ASSERT_TRUE(s == "hello");
    ASSERT_EQ(s.getLen(), 5);
}

void test_replace_multiple_occurrences() {
    MyString s("aXaXa");
    s.replace(MyString("X"), MyString("Y"));
    ASSERT_TRUE(s == "aYaYa");
}

// operator+
void test_operator_plus_eq() {
    MyString s("hello");
    s += MyString(" world");
    ASSERT_EQ(s.getLen(), 11);
    ASSERT_TRUE(s == "hello world");
}

void test_operator_plus_eq_empty() {
    MyString s("abc");
    s += MyString("");
    ASSERT_TRUE(s == "abc");
}

// operator ==
void test_operator_eq_true() {
    MyString s("hello");
    ASSERT_TRUE(s == "hello");
}

void test_operator_eq_false_content() {
    MyString s("hello");
    ASSERT_FALSE(s == "world");
}

void test_operator_eq_false_length() {
    MyString s("hello");
    ASSERT_FALSE(s == "hell");
}

// operator> / <
void test_operator_greater() {
    MyString s("b");
    ASSERT_TRUE(s > "a");
    ASSERT_FALSE(s > "c");
    ASSERT_FALSE(s > "b"); // 같으면 false
}

void test_operator_less() {
    MyString s("a");
    ASSERT_TRUE(s < "b");
    ASSERT_FALSE(s < "a"); // 같으면 false
}

void test_operator_greater_prefix() {
    // "abc" > "ab" (더 길면 더 큼)
    MyString s("abc");
    ASSERT_TRUE(s > "ab");
}

void test_operator_less_prefix() {
    // "ab" < "abc" (더 짧으면 더 작음)
    MyString s("ab");
    ASSERT_TRUE(s < "abc");
}

// join
void test_join_basic() {
    MyString s("-");
    s.join("abc");
    
    ASSERT_EQ(s.getLen(), 5);
    ASSERT_TRUE(s == "a-b-c");
}

void test_join_multi_char_separator() {
    MyString s(", ");
    s.join("abc");
    
    ASSERT_EQ(s.getLen(), 7);
    ASSERT_TRUE(s == "a, b, c");
}


int main() {

    // 생성자
    RUN_TEST(test_constructor_char);
    RUN_TEST(test_constructor_cstring);
    RUN_TEST(test_constructor_empty_string);
    RUN_TEST(test_copy_constructor);
    RUN_TEST(test_copy_constructor_independence);

    // getLen / at
    RUN_TEST(test_getLen);
    RUN_TEST(test_at_valid_index);
    RUN_TEST(test_at_invalid_index);

    // append
    RUN_TEST(test_append_basic);
    RUN_TEST(test_append_empty);
    RUN_TEST(test_append_to_empty);

    // assign
    RUN_TEST(test_assign_shorter_to_longer);
    RUN_TEST(test_assign_longer_to_shorter);
    RUN_TEST(test_assign_same_length);

    // in
    RUN_TEST(test_in_found);
    RUN_TEST(test_in_found_at_start);
    RUN_TEST(test_in_not_found);
    RUN_TEST(test_in_longer_than_original);
    RUN_TEST(test_in_partial_match);

    // same
    RUN_TEST(test_same_equal);
    RUN_TEST(test_same_different);
    RUN_TEST(test_same_different_length);
    RUN_TEST(test_same_same_length_different_content);

    // compare
    RUN_TEST(test_compare_equal);
    RUN_TEST(test_compare_greater);
    RUN_TEST(test_compare_less);
    RUN_TEST(test_compare_prefix_longer);
    RUN_TEST(test_compare_prefix_shorter);

    // insert
    RUN_TEST(test_insert_char_middle);
    RUN_TEST(test_insert_char_start);
    RUN_TEST(test_insert_char_invalid_pos);
    RUN_TEST(test_insert_cstring_middle);
    RUN_TEST(test_insert_mystring_middle);

    // erase
    RUN_TEST(test_erase_single_start);
    RUN_TEST(test_erase_single_middle);
    RUN_TEST(test_erase_single_end);
    RUN_TEST(test_erase_single_invalid);
    RUN_TEST(test_erase_count);
    RUN_TEST(test_erase_count_from_start);

    // replace
    RUN_TEST(test_replace_single_occurrence);
    RUN_TEST(test_replace_no_match);
    RUN_TEST(test_replace_multiple_occurrences);

    // operator+=
    RUN_TEST(test_operator_plus_eq);
    RUN_TEST(test_operator_plus_eq_empty);

    // operator==
    RUN_TEST(test_operator_eq_true);
    RUN_TEST(test_operator_eq_false_content);
    RUN_TEST(test_operator_eq_false_length);

    // operator> / operator<
    RUN_TEST(test_operator_greater);
    RUN_TEST(test_operator_less);
    RUN_TEST(test_operator_greater_prefix);
    RUN_TEST(test_operator_less_prefix);

    // join
    RUN_TEST(test_join_basic);
    RUN_TEST(test_join_multi_char_separator);

    // 결과 
    std::cout << " 결과: " << passed_tests << "/" << total_tests << std::endl;
    std::cout << " 실패: " << failed_tests << " failed" << std::endl;

    return failed_tests > 0 ? 1 : 0;
}
