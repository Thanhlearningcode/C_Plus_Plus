/*
* File: table.h
* Author: Nguyen Van Thanh
* Date: 10/02/2024
* Description: This file is a table header file for storing table information in a restaurant management system.
*/

#ifndef _TABLE_H
#define _TABLE_H

#include <list>
#include "dish.h"

using namespace std;

// Enum for table status
typedef enum {
    Booked,
    Free
} Status;

/*
* Class: Table
* Description: This class contains basic properties and methods for managing a restaurant table.
*/
class Table {
private:
    int tableID;                // Unique ID of the table
    Status status;              // Status of the table (Booked or Free)
    list<Order> orderList;      // List of orders placed at the table
    int totalBill;              // Total bill for the table

public:
    // Constructor
    Table() {
        static int _tableID = 1;
        this->tableID = _tableID;
        _tableID++;
        this->status = Free;
        this->totalBill = 0;
    }

    // Reset the table to its default state
    void resetTable();

    // Setters and getters for table properties
    void setStatus(Status _status);
    Status getStatus();

    void setTableID(int _tableID);
    int getTableID();

    // Manage orders
    void orderDish(int ID_input, list<Dish> menu);
    void cancelDish(int ID_input);
    void changeNum(int ID_input);

    // Display order list
    void printOrderList();

    // Calculate and return the total bill
    int getBill();
};

#endif // _TABLE_H
