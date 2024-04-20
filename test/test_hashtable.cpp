#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
#include "hashTable.h"

TEST(HashTable, create_table_is_positive_length)
{
    int s = 100;
    HashTable<string, int> a(s);
    EXPECT_EQ(a.size(), s);
}

TEST(HashTable, create_copied_table)
{
    int s = 100;
    HashTable<string, int> a(s);

    HashTable<string, int> b = a;
    EXPECT_EQ(a.size(), b.size());
}

TEST(HashTable, assign_table)
{
    int s1 = 5;
    int s2 = 100;
    HashTable<string, int> a(s1);
    HashTable<string, int> b(s2);

    b = a;
    EXPECT_EQ(a.size(), b.size());
}


TEST(HashTable, get_data_by_key_string)
{
    int data = 10;
    HashTable<string, int> a(100);
    a.insert("key", data);
    a.insert("key + 1", data + 1);
    a.insert("key - 1", data - 1);

    EXPECT_EQ(a["key"], data);
}

TEST(HashTable, get_data_by_key_int)
{
    int data = 10;
    int key = 25;
    HashTable<int, int> a(100);
    a.insert(key, data);
    a.insert(key + 19, data + 1);
    a.insert(key - 21, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(HashTable, get_data_by_key_float)
{
    int data = 10;
    int key = 25.234;
    HashTable<float, int> a(100);
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(HashTable, get_data_by_key_double)
{
    int data = 10;
    int key = 25.234;
    HashTable<double, int> a(100);
    a.insert(key, data);
    a.insert(key + 19.347, data + 1);
    a.insert(key - 21.344, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(HashTable, get_data_by_key_vector)
{
    int data = 10;
    vector<int> key1 = { 1,2,3,4,5 };
    vector<int> key2 = { 4,2,4,7,8 };
    vector<int> key3 = { 6,4,6,9,7 };

    HashTable<vector<int>, int> a(100);
    a.insert(key1, data);
    a.insert(key2, data + 1);
    a.insert(key3, data - 1);

    EXPECT_EQ(a[key1], data);
}

TEST(HashTable, insert) {
    HashTable <string, int> a(100);
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(*a.insert("3", 3), 3);
}

TEST(HashTable, find_by_an_existing_key)
{
    HashTable <string, int> a(100);
    a.insert("1", 1);
    a.insert("7", 7);
    a.insert("3", 3);
    a.insert("6", 6);
    a.insert("10", 10);
    EXPECT_EQ(3, *a.find("3"));
}

TEST(HashTable, remove_true)
{
    int data = 10;
    HashTable<string, int> a(100);
    a.insert("key", data);
    bool x = a.remove("key");
    EXPECT_EQ(x, true);
}

TEST(HashTable, remove_false)
{
    int key = 4;
    int data = 10;
    HashTable<string, int> a(100);
    a.insert("key", data);
    bool x = a.remove("key + 1");
    EXPECT_EQ(x, false);
}

TEST(HashTable, create_table_int_int_is_positive_length)
{
    int s = 100;
    HashTable<int, int> a(s);
    EXPECT_EQ(a.size(), s);
}


TEST(HashTable, test_insert1)
{
    int s = 0;
    int N = 1000;
    HashTable<int, int> a(s);
    for (int i = 0; i < N; i++) {
        a.insert(i, 20);
    }

    for (auto i = a.begin(); i != a.end(); ++i) {
        (*i)++;
    }
    EXPECT_TRUE(a.size() >= 250);
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(a[i], 21);
    }
}
