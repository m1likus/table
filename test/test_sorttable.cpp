#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
#include "sortTable.h"

TEST(SortTable, create_an_empty_table)
{
    SortTable<int, int> a;
    EXPECT_EQ(a.size(), 0);
}

TEST(SortTable, create_table_is_positive_length)
{
    int s = 100;
    SortTable<int, int> a(s);
    EXPECT_EQ(a.size(), s);
}

TEST(SortTable, create_copied_table)
{
    int s = 100;
    SortTable<int, int> a(s);

    SortTable<int, int> b = a;
    EXPECT_EQ(a.size(), b.size());
}

TEST(SortTable, assign_table)
{
    int s1 = 5;
    int s2 = 100;
    SortTable<int, int> a(s1);
    SortTable<int, int> b(s2);

    b = a;
    EXPECT_EQ(a.size(), b.size());
}


TEST(SortTable, get_data_by_key)
{
    int key = 4;
    int data = 10;
    SortTable<int, int> a;
    a.insert(key, data);
    a.insert(key + 1, data + 1);
    a.insert(key - 1, data - 1);

    EXPECT_EQ(a[key], data);
}
TEST(SortTable, set_data_by_key)
{
    int key = 4;
    int data = 10;
    SortTable<int, int> a;
    a[key] = data;
    a.insert(key + 1, data + 1);
    a.insert(key - 1, data - 1);

    EXPECT_EQ(a[key], data);
}

TEST(SortTable, insert) {
    SortTable <int, int> a;
    a.insert(1, 1);
    a.insert(7, 7);
    a.insert(3, 3);
    a.insert(6, 6);
    a.insert(10, 10);
    EXPECT_EQ(*a.insert(3, 3), 3);
}

TEST(SortTable, find_by_an_existing_key)
{
    vector<int> key = { 2,5,3,6,4 };//23456
    vector<int> data = { 1,2,3,4,5 };//13524
    SortTable<int, int> a;
    for (int i = 0; i < 5; i++) {
        a[key[i]] = data[i];
    }
    int pos1 = 2;
    int pos2 = 1;
    EXPECT_EQ(*(a.begin() + pos2), *a.find(key[pos1]));
}

TEST(SortTable, remove_true)
{
    int key = 4;
    int data = 10;
    SortTable<int, int> a;
    a.insert(key, data);
    bool x = a.remove(key);
    EXPECT_EQ(x, true);
}

TEST(SortTable, remove_false)
{
    int key = 4;
    int data = 10;
    SortTable<int, int> a;
    a.insert(key, data);
    bool x = a.remove(key + 1);
    EXPECT_EQ(x, false);
}