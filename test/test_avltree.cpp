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
    bool x = a.remove1("key");
    EXPECT_EQ(x, true);
}

TEST(AvlTreeTable, remove_false)
{
    int key = 4;
    int data = 10;
    AvlTreeTable<string, int> a;
    a.insert("key", data);
    bool x = a.remove1("key + 1");
    EXPECT_EQ(x, false);
}

//TEST(AvlTreeTable, test_insert1)
//{
//    int s = 0;
//    int N = 1000;
//    vector<bool> b(N);
//    AvlTreeTable<int, int> a;
//    int k = N;
//    while (k != 1) {
//        k /= 2;
//        for (int i = k; i < N; i += k) {
//            if (!b[i])
//                a.insert(i, 20);
//            b[i] = 1;
//        }
//    }
//    a.insert(0, 20);
//
//    for (auto i = a.begin(); i != a.end(); ++i) {
//        (*i)++;
//    }
//    for (int i = 0; i < N; i++) {
//        EXPECT_EQ(a[i], 21);
//    }
//}
//TEST(AvlTreeTable, test_remove1)
//{
//    int s = 0;
//    int N = 1000;
//    vector<bool> b(N);
//    AvlTreeTable<int, int> a;
//    int k = N;
//    while (k != 1) {
//        k /= 2;
//        for (int i = k; i < N; i += k) {
//            if (!b[i])
//                a.insert(i, 20);
//            b[i] = 1;
//        }
//    }
//    a.insert(0, 20);
//
//    for (int i = 0; i < N; i++) {
//        if (i == 94) {
//            i = 94;
//        }
//        a.remove(i);
//    }
//}
//
//TEST(AvlTreeTable, test_insert_and_remove_while) {
//    int avlTreeN = 1000;
//    int N = 2000;
//    vector<int> vec_insert(N);
//    vector<int> vec_remove;
//    for (int i = 0; i < N; i++) {
//        vec_insert[i] = i;
//    }
//    random_device rd;
//    mt19937 g(rd());
//    std::shuffle(vec_insert.begin(), vec_insert.end(), g);
//    AvlTreeTable<int, int> a;
//    for (int i = 0; i < avlTreeN; i++) {
//        a.insert(vec_insert[i], vec_insert[i]);
//        vec_remove.push_back(vec_insert[i]);
//        swap(vec_insert[i], vec_insert[vec_insert.size() - 1]);
//        vec_insert.pop_back();
//    }
//    int startTreeHeight = a.getHeight(), treeHeight = startTreeHeight;
//    int count = 0;
//    while ((treeHeight - startTreeHeight) < 10) {
//        cout << count << " ";
//        count++;
//        std::shuffle(vec_insert.begin(), vec_insert.end(), g);
//        std::shuffle(vec_remove.begin(), vec_remove.end(), g);
//        for (int i = 0; i < 100; i++) {
//            a.insert(vec_insert[i], vec_insert[i]);
//            vec_remove.push_back(vec_insert[i]);
//            swap(vec_insert[i], vec_insert[vec_insert.size() - 1]);
//            vec_insert.pop_back();
//        }
//        for (int i = 0; i < 100; i++) {
//            a.remove(vec_remove[i]);
//            vec_insert.push_back(vec_remove[i]);
//            swap(vec_remove[i], vec_remove[vec_remove.size() - 1]);
//            vec_remove.pop_back();
//        }
//        treeHeight = a.getHeight();
//    }
//    cout << "Total cycles of inserting and removing: " << count << endl;
//    ASSERT_EQ(a.size(), avlTreeN);
//}
//TEST(AvlTreeTable, test_height) {
//    AvlTreeTable<int, int> a;
//    a.insert(0, 0);
//    a.insert(1, 1);
//    a.insert(2, 2);
//    ASSERT_EQ(a.getHeight(), 1);
//}

