/*
* File: dish.h
* Author: Nguyen Van Thanh
* Date: 10/02/2024
* Description: This file is a dish header file for a program used to store dish information.
*/

#ifndef _DISH_H
#define _DISH_H

#include <iostream>
#include <string>

using namespace std;

/*
* Class: Dish
* Description: This class contains basic properties and methods of a Dish object.
*/
class Dish {
private:
    int ID;
    string name;
    int price;

public:
    Dish() {
        static int _ID = 1;
        this->ID = _ID;
        _ID++;

        this->name = "";
        this->price = 0;
    }

    void setID(int _ID);
    int getID();

    void setName(string _name);
    string getName();

    void setPrice(int _price);
    int getPrice();

    void setData();
    void getData();
};

/*
* Struct: Order
* Description: This struct represents an order, containing a dish and the quantity ordered.
*/
typedef struct {
    int num;
    Dish dish;
} Order;

#endif // _DISH_H
