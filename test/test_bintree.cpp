#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
#include "binTreeTable.h"
#include <numeric>

TEST(BinTreeTable, get_data_by_key_string)
{
    int data = 10;
    BinTreeTable<string, int> a;
    a.insert("key", data);
    a.insert("key + 1", data + 1);
    a.insert("key - 1", data - 1);

    EXPECT_EQ(a["key"], data);
}

TEST(BinTreeTable, get_data_by_key_int)
{
    int data = 10;
    int key = 25;
    BinTreeTable<int, int> a;
    a.insert(key, data);
    a.insert(key + 19, data + 1);
    a.insert(key - 21, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(BinTreeTable, get_data_by_key_float)
{
    int data = 10;
    int key = 25.234;
    BinTreeTable<float, int> a;
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(BinTreeTable, get_data_by_key_double)
{
    int data = 10;
    int key = 25.234;
    BinTreeTable<double, int> a;
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(BinTreeTable, get_data_by_key_vector)
{
    int data = 10;
    vector<int> key1 = { 1,2,3,4,5 };
    vector<int> key2 = { 4,2,4,7,8 };
    vector<int> key3 = { 6,4,6,9,7 };

    BinTreeTable<vector<int>, int> a;
    a.insert(key1, data);
    a.insert(key2, data + 1);
    a.insert(key3, data - 1);

    EXPECT_EQ(a[key1], data);
}

TEST(BinTreeTable, insert) {
    BinTreeTable <string, int> a;
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(*a.insert("3", 3), 3);
}

TEST(BinTreeTable, find_by_an_existing_key)
{
    BinTreeTable <string, int> a;
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(3, *a.find("3"));
}

TEST(BinTreeTable, remove_true)
{
    int data = 10;
    BinTreeTable<string, int> a;
    a.insert("key", data);
    bool x = a.remove("key");
    EXPECT_EQ(x, true);
}

TEST(BinTreeTable, remove_false)
{
    int key = 4;
    int data = 10;
    BinTreeTable<string, int> a;
    a.insert("key", data);
    bool x = a.remove("key + 1");
    EXPECT_EQ(x, false);
}

TEST(BinTreeTable, test_insert_with_iterators)
{
    int N = 1000;
    vector<bool> b(N);
    BinTreeTable<int, int> a;
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

TEST(BinTreeTable, test_insert_1000elements) {
    int N = 1000;
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        b[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    std::shuffle(b.begin(), b.end(), g);

    BinTreeTable<int, int> a;
    for (int i = 0; i < N; i++) {
        ASSERT_NO_THROW(a.insert(b[i], b[i]));
    }
    ASSERT_EQ(a.size(), N);
}

TEST(BinTreeTable, test_remove_1000elements) {
    int N = 1000;
    vector<int> b(N);
    BinTreeTable<int, int> a;
    std::iota(b.begin(), b.end(), 0);

    random_device rd;
    int seed = 3;
    mt19937 g(rd());
    
    std::shuffle(b.begin(), b.end(), g);
    for (int i = 0; i < N; i++)
        a.insert(b[i], b[i]);

    std::shuffle(b.begin(), b.end(), g);
    for (int i = 0; i < N; i++) {
        if (i == 998)
            i = 998;
        EXPECT_EQ(a.remove(b[i]), true);
       
    }

    ASSERT_EQ(a.size(), 0);
}

TEST(BinTreeTable, test_insert_and_remove_while) {
    int binTreeN = 1000;
    int N = 2000;
    vector<int> vec_insert(N);
    vector<int> vec_remove;
    for (int i = 0; i < N; i++) {
        vec_insert[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    std::shuffle(vec_insert.begin(), vec_insert.end(), g);
    BinTreeTable<int, int> a;
    for (int i = 0; i < binTreeN; i++) {
        a.insert(vec_insert[i], vec_insert[i]);
        vec_remove.push_back(vec_insert[i]);
        swap(vec_insert[i], vec_insert[vec_insert.size() - 1]);
        vec_insert.pop_back();
    }
    int startTreeHeight = a.getHeight(), treeHeight = startTreeHeight;
    int count = 0;
    while ((treeHeight - startTreeHeight) < 10) {
        count++;
        std::shuffle(vec_insert.begin(), vec_insert.end(), g);
        std::shuffle(vec_remove.begin(), vec_remove.end(), g);
        for (int i = 0; i < 100; i++) {
            a.insert(vec_insert[i], vec_insert[i]);
            vec_remove.push_back(vec_insert[i]);
            swap(vec_insert[i], vec_insert[vec_insert.size() - 1]);
            vec_insert.pop_back();
        }
        for (int i = 0; i < 100; i++) {
            a.remove(vec_remove[i]);
            vec_insert.push_back(vec_remove[i]);
            swap(vec_remove[i], vec_remove[vec_remove.size() - 1]);
            vec_remove.pop_back();
        }
        treeHeight = a.getHeight();
    }
    cout << "Total cycles of inserting and removing: " << count << endl;
    ASSERT_EQ(a.size(), binTreeN);
}

TEST(BinTreeTable, test_111)
{
    BinTreeTable<int, int> a;
    a.insert(1, 1);

    auto i = a.end();
    --i;
    auto j = a.begin();
    EXPECT_EQ(*i, *j);

}