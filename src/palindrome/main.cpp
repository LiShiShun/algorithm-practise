#include <iostream>
#include <string>
#include <cassert>

int ExpandToBoundary(const char* s, int left, int right) {
    int from = left;
    int to = right;
    while(from >= 0 && s[to] != '\0' && s[from] == s[to]) {
        from--;
        to++;
    }

    return to - from - 1;
}

// O(n^2)
std::string GetMaxPalindromeSubstring(const char* s, int len) {
    if(s == nullptr || s[0] == '\0') {
        return "";
    }

    for(int i = 0;s[i] != '\n'; i++) {
        
    }

    return "";
}

// O(n)

int main() {
    return 0;
}



