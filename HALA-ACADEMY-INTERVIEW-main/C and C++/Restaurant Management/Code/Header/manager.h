/*
* File: manager.h
* Author: Nguyen Van Thanh
* Date: 10/02/2024
* Description: This file is a table header file for managing a restaurant's operations.
*/

#ifndef _MANAGER_H
#define _MANAGER_H

#include "table.h"
#include <list>
using namespace std;

/*
* Class: Manager
* Description: This class contains basic properties and methods for managing a restaurant, including menu items and table settings.
*/
class Manager {
private:
    list<Dish> menu;  // List of dishes in the menu
    int numTable;     // Number of tables in the restaurant

public:
    // Constructor to initialize number of tables to 0
    Manager() {
        this->numTable = 0;
    }

    // Getter for the menu
    list<Dish> getMenu();

    // Setter and getter for the number of tables
    void setNumTable(int _numTable);
    int getNumTable();

    // Method to add a dish to the menu
    void addDish();

    // Method to edit a dish in the menu based on its ID
    void editDish(int ID_input);

    // Method to delete a dish from the menu based on its ID
    void deleteDish(int ID_input);

    // Method to display the menu
    void showMenu();
};

#endif // _MANAGER_H
