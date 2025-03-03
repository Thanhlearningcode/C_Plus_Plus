/*
* File: main.cpp
* Author: Nguyễn Văn Thành
* Date: 5/02/2024
* Description: Main file to run the menu for managing students in the school.
*/

#include "Menu.h"
using namespace std;

int main() {
    list<Student> database;
    menu(database);  // Call the menu function to manage the student database

    return 0;
}
