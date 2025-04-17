#include <algorithm>
#include <iostream>
#include <cassert>

int binarySearch(int a[], int num, int elem) {
    int left = 0, right = num -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == elem) {
            return mid;
        } else if (a[mid] < elem) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}


int main() {
    #define TEST(a, num, elem, result) \
        { \
            std::cout<< "测试 " << elem <<" 的查找结果 " <<std::endl; \
            int ret = binarySearch(a, num, elem); \
            if(ret != result) { \
                std::cout<< "测试失败！" << ret << std::endl; \
            } \
            assert(ret == result); \
            std::cout<< "测试成功" <<std::endl; \
        }


    std::cout << "开始二分查找测试..." << std::endl;
    try {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        TEST(a, 10, 1, 0);
        TEST(a, 10, 2, 1);
        TEST(a, 10, 5, 4);
        TEST(a, 10, 10, 9);
        TEST(a, 10, 11, -1);

        std::cout << "所有测试通过！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}



