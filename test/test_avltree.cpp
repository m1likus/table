#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
#include "avlTreeTable.h"

TEST(AvlTreeTable, get_data_by_key_string)
{
    int data = 10;
    AvlTreeTable<string, int> a;
    a.insert("key", data);
    a.insert("key + 1", data + 1);
    a.insert("key - 1", data - 1);

    EXPECT_EQ(a["key"], data);
}

TEST(AvlTreeTable, get_data_by_key_int)
{
    int data = 10;
    int key = 25;
    AvlTreeTable<int, int> a;
    a.insert(key, data);
    a.insert(key + 19, data + 1);
    a.insert(key - 21, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(AvlTreeTable, get_data_by_key_float)
{
    int data = 10;
    int key = 25.234;
    AvlTreeTable<float, int> a;
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(AvlTreeTable, get_data_by_key_double)
{
    int data = 10;
    int key = 25.234;
    AvlTreeTable<double, int> a;
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(AvlTreeTable, get_data_by_key_vector)
{
    int data = 10;
    vector<int> key1 = { 1,2,3,4,5 };
    vector<int> key2 = { 4,2,4,7,8 };
    vector<int> key3 = { 6,4,6,9,7 };

    AvlTreeTable<vector<int>, int> a;
    a.insert(key1, data);
    a.insert(key2, data + 1);
    a.insert(key3, data - 1);

    EXPECT_EQ(a[key1], data);
}

TEST(AvlTreeTable, insert) {
    AvlTreeTable <string, int> a;
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(*a.insert("3", 3), 3);
}

TEST(AvlTreeTable, find_by_an_existing_key)
{
    AvlTreeTable <string, int> a;
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(3, *a.find("3"));
}

TEST(AvlTreeTable, remove_true)
{
    int data = 10;
    AvlTreeTable<string, int> a;
    a.insert("key", data);
    bool x = a.remove("key");
    EXPECT_EQ(x, true);
}

TEST(AvlTreeTable, remove_false)
{
    int key = 4;
    int data = 10;
    AvlTreeTable<string, int> a;
    a.insert("key", data);
    bool x = a.remove("key + 1");
    EXPECT_EQ(x, false);
}

TEST(AvlTreeTable, test_insert1)
{
    int s = 0;
    int N = 1000;
    vector<bool> b(N);
    AvlTreeTable<int, int> a;
    int k = N;
    while (k != 1) {
        k /= 2;
        for (int i = k; i < N; i += k) {
            if (!b[i])
                a.insert(i, 20);
            b[i] = 1;
        }
    }
    a.insert(0, 20);

    for (auto i = a.begin(); i != a.end(); ++i) {
        (*i)++;
    }
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(a[i], 21);
    }
}
//работает
//TEST(AvlTreeTable, getHeight) {
//    AvlTreeTable<int, int> a;
//    a.insert(10,10);
//    a.insert(5, 5);
//    a.insert(15, 15);
//    a.insert(0, 0);
//    a.insert(7, 7);
//    int height = 2;
//    int treeHeight = a.giveHeight();
//    EXPECT_EQ(treeHeight, height);
//}
