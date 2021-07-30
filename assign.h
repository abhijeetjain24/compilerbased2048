#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;
int insert_random_tile();
int print_output(int error_code);//the function to print actual shit to stderr
int assign_value(int value,int x,int y);// returns appropriate error code
int Do_move(int operation,int direction);// 
int set_name(string* name,int x,int y);
int get_value(int x,int y);
int assign_value_1();