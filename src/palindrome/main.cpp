#include <iostream>
#include <string>
#include <cassert>

int ExpandToBoundary(const char* s, int left, int right) {
    int from = left;
    int to = right;
    int len = 0;
    while(from >= 0 && s[to] != '\0') {
        if(s[from] != s[to]) {
            break;
        }

        len++;
        from--;
        to++;
    }

    return len;
}

// O(n^2)
std::string GetMaxPalindromeSubstring(const char* s) {
    if(s == nullptr || s[0] == '\0') {
        return "";
    }

    int start_index = 0;
    int end_index = 0;
    int max_length = 0;
    for(int i = 0;s[i] != '\0'; i++) {
        int sub_len1 = ExpandToBoundary(s, i, i); // i#i
        sub_len1 = sub_len1 * 2 - 1;

        int sub_len2 = ExpandToBoundary(s, i, i + 1); // i i+1
        sub_len2 = sub_len2 * 2;

        if(sub_len1 > max_length) {
            max_length = sub_len1;
            start_index = i - (max_length - 1) / 2;
            end_index = i + (max_length - 1) / 2;
        }
        if(sub_len2 > max_length) {
            max_length = sub_len2;
            start_index = i - max_length / 2 + 1;
            end_index = i + max_length / 2;
        }
    }

    std::string ret(s);
    return ret.substr(start_index, max_length);
}

int main() {
    #define TEST(a, b) \
        { \
            std::cout<< "测试 " << a <<" 的最长回文串是 " << b << "..." <<std::endl; \
            std::string s(a); \
            std::string ret = GetMaxPalindromeSubstring(s.c_str()); \
            if(ret != b) { \
                std::cout<< "测试失败！" << "最长回文子串为: "<<ret << std::endl; \
            } \
            assert(ret == b); \
            std::cout<< "测试成功" <<std::endl; \
        }


    std::cout << "开始最长回文子串测试..." << std::endl;
    try {
        TEST("abcdcbx", "bcdcb");
        TEST("sdklfjjfslkd", "fjjf");
        TEST("aaaaa", "aaaaa");
        TEST("ab", "a");
        TEST("a", "a");
        TEST("", "");

        std::cout << "所有测试通过！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}



