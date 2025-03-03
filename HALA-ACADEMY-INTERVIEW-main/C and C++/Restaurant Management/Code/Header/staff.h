/*
* File: staff.h
* Author: Nguyen Van Thanh
* Date: 10/02/2024
* Description: This file is a staff header file for managing tables in a restaurant.
*/

#ifndef _STAFF_H
#define _STAFF_H

#include <vector>
#include "table.h"

using namespace std;

/*
* Class: Staff
* Description: This class is used to manage tables in a restaurant, including displaying tables, checking availability, and handling table selection.
*/
class Staff {
public:
    vector<Table> tableList; // List of tables managed by the staff

    // Constructor
    Staff() {}

    // Sets up a specific number of tables
    void getNumTable(int _numTable);

    // Displays all the tables that have been set up
    void displayTable();

    // Checks if all tables are full
    bool isFull();

    // Allows selection of an empty table by its ID
    void chooseTable(int _tableID);

    // Retrieves information about a specific table, including menu details
    void getTableInfo(int _tableID, int type, list<Dish> menu);
};

#endif // _STAFF_H
