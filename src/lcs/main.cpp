#include <algorithm>
#include <iostream>
#include <cassert>

#define MAX_SIZE 128

int lcs(const char* s1, int len1, const char* s2, int len2) {
    int dp[MAX_SIZE][MAX_SIZE] = {0};

    // 0 for empty ""
    for(int i = 0; i < len1; i++) {
        dp[i][0] = 0;
    }
    for(int i = 0; i < len2; i++) {
        dp[0][i] = 0;
    }

    // base 1
    for(int i = 1; i <= len1; i++) {
        for(int j = 1; j <= len2; j++) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }

            // std::cout<<i<<" "<<j<<" "<<dp[i][j]<<std::endl;
        }
    }


    return dp[len1][len2];
}


int main() {
    #define TEST(a, b, c) \
        { \
            std::cout<< "测试 " << a <<" 的最长公共子串是 " << b << "..." <<std::endl; \
            std::string s1(a); \
            std::string s2(b); \
            int ret = lcs(s1.c_str(), s1.size(), s2.c_str(), s2.size()); \
            if(ret != c) { \
                std::cout<< "测试失败！" << "最长公共子串为: "<< ret << std::endl; \
            } \
            assert(ret == c); \
            std::cout<< "测试成功" <<std::endl; \
        }


    std::cout << "开始最长公共子串测试..." << std::endl;
    try {
        TEST("abc", "bc", 2);
        TEST("b", "b", 1);
        TEST("skljfl;", "wioekj", 2);
        TEST("", "", 0);

        std::cout << "所有测试通过！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}



