#include <gtest.h>
#include "table.h"

TEST(Table, create_an_empty_table) 
{
    ASSERT_ANY_THROW();     //ASSERT_ANY_THROW(Table<int,int> a); it doesn't work, mb you know what the reason is (I took it from the translator)
}

TEST(Table, create_table_is_positive_length)
{
    ASSERT_ANY_THROW();
}

TEST(Table, create_copied_table) 
{
    ASSERT_ANY_THROW();
}

TEST(Table, assign_table)
{
    ASSERT_ANY_THROW();
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

TEST(Table, set_data_by_key_2)//I do not know what to call your brilliant implementation (I took it from the translator)
{
    int key = 4;
    int data = 10;
    Table<int, int> a;
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





int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}