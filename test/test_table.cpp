#include <gtest.h>
#include "table.h"
#include "sortTable.h"
#include "hashTable.h"
//#include "binTreeTable.h"

TEST(Table, create_an_empty_table) 
{
    Table<int, int> a;
    EXPECT_EQ(a.size(), 0);
}

TEST(Table, create_table_is_positive_length)
{
    int s = 100;
    Table<int, int> a(s);
    EXPECT_EQ(a.size(), s);
}

TEST(Table, create_copied_table) 
{
    int s = 100;
    Table<int, int> a(s);

    Table<int, int> b = a;
    EXPECT_EQ(a.size(), b.size());
}

TEST(Table, assign_table)
{
    int s1 = 5;
    int s2 = 100;
    Table<int, int> a(s1);
    Table<int, int> b(s2);

    b = a;
    EXPECT_EQ(a.size(), b.size());
}

TEST(Table, get_data_by_key)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
    a.insert(key, data);
    EXPECT_EQ(a[key], data);
}

TEST(Table, set_data_by_key)
{
    int key = 4;
    int data1 = 10;
    int data2 = 11;
    Table<int, int> a;
    a.insert(key, data1);
    a[key] = data2;
    EXPECT_EQ(a[key], data2);
}

TEST(Table, set_data_by_key_2)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
    int c = 1;
    a[c] = 2;
    a[key] = data;
    EXPECT_EQ(a[key], data);
}

TEST(Table, find_by_an_existing_key)
{
    vector<int> key = { 2,5,3,6,4 };
    vector<int> data = { 1,2,3,4,5 };
    Table<int, int> a;
    for (int i = 0; i < 5; i++) {
        a[key[i]] = data[i];
    }
    int pos = 2;
    EXPECT_EQ(*(a.begin() + pos), *a.find(key[pos]));
}

TEST(Table, find_by_a_non_existing_key)
{
    vector<int> key = { 2,5,3,6,4 };
    vector<int> data = { 1,2,3,4,5 };
    Table<int, int> a;
    for (int i = 0; i < 5; i++) {
        a[key[i]] = data[i];
    }
    int not_key = 7;
    EXPECT_EQ(*a.end(), *a.find(not_key));
}

TEST(Table, insert)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
    a.insert(key, data);
    EXPECT_EQ(a[key], data);
}

TEST(Table, remove_true)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
    a.insert(key, data);
    bool x = a.remove(key);
    EXPECT_EQ(x, true);
}

TEST(Table, remove_false)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
    a.insert(key, data);
    bool x = a.remove(key+1);
    EXPECT_EQ(x, false);
}

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
    a.insert(key-1, data-1);

    EXPECT_EQ(a[key], data);
}
TEST(SortTable, set_data_by_key)
{
    int key = 4;
    int data = 10;
    SortTable<int, int> a;
    a[key] = data;
    a.insert(key+1, data+1);
    a.insert(key-1, data-1);

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


TEST(HashTable, get_data_by_key)
{
    int data = 10;
    HashTable<string, int> a(100);
    a.insert("key", data);
    a.insert("key + 1", data + 1);
    a.insert("key - 1", data - 1);

    EXPECT_EQ(a["key"], data);
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}