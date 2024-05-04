#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
#include "avlTreeTable.h"
#include <numeric>

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
TEST(AvlTreeTable, test_remove2) {
    AvlTreeTable<int, int> a;
    a.insert(200, 0);
    a.insert(100, 0);
    a.insert(300, 0);
    a.insert(50, 0);
    a.insert(150, 0);
    a.insert(250, 0);
    a.insert(350, 0);
    a.insert(125, 0);
    a.insert(175, 0);

    a.remove(200);
    a.remove(350);

}



TEST(AvlTreeTable, test_remove1)
{
    int s = 0;
    int N = 10000;
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
    // TODO: add expect

    vector<int> vec_remove(N);
    std::iota(vec_remove.begin(), vec_remove.end(), 0);
    random_device rd;
    int seed = 0;
    mt19937 g(seed); // rd
    std::shuffle(vec_remove.begin(), vec_remove.end(), g);
    for (int i = 0; i < N; i++) {
        a.remove(vec_remove[i]);
    }
}

TEST(AvlTreeTable, test_remove3)
{
    int N = 10000;
    AvlTreeTable<int, int> a;
    for (int i = 0; i < N; i++) {
        a.insert(i, 20);
    }
    for (int i = 0; i < N; i++) {
        a.remove(i);
    }
}

TEST(AvlTreeTable, test_height) {
    int s = 0;
    int N = 1000;
    vector<bool> b(N);
    AvlTreeTable<int, int> a;
    a.insert(10000, 10000);
    int firstHeight = a.getHeight(), secondHeight = firstHeight;
    int k = N;
    // TODO: SEED!!! =)
    cout << "insert\n";
    while (k != 1) {
        k /= 2;
        for (int i = k; i < N; i += k) {
            if (!b[i]) {
                firstHeight = a.getHeight();
                a.insert(i, 20);
                secondHeight = a.getHeight();
            }
            b[i] = 1;
            //cout << i << " " << a.getHeight() << "\n";
            //cout << "Delta = " << secondHeight - firstHeight << endl;
            EXPECT_LE(std::abs(secondHeight - firstHeight), 1);
        }
    }
    a.insert(0, 20);
    cout << endl;
    cout << a.size();
    cout << endl;
    cout << "remove\n";
    for (int i = 0; i < N; i++) {
        firstHeight = a.getHeight();
        a.remove(i);
        secondHeight = a.getHeight();
        //cout << i << " " << a.getHeight() << "\n";
        //cout << "Delta = " << secondHeight - firstHeight << endl;
        EXPECT_LE(std::abs(secondHeight - firstHeight), 1);
    }
}


TEST(AvlTreeTable, test_height1) {
    AvlTreeTable<int, int> a;
    a.insert(0, 0);
    a.insert(1, 1);
    a.insert(2, 2);
    ASSERT_EQ(a.getHeight(), 1);
}

