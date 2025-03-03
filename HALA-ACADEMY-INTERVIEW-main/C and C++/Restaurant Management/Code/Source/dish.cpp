/*
* File: dish.cpp
* Author: Nguyễn Văn Thành
* Date: 10/02/2024
* Description: This file contains all the functions/methods to store dish's information
*/

#include "../Header/dish.h"
#include <iomanip> // For setw()
using namespace std;

// Setters and Getters for Dish class

void Dish::setID(int _ID) {
    ID = _ID;
}

int Dish::getID() const {
    return ID;
}

void Dish::setName(string _name) {
    name = _name;
}

string Dish::getName() const {
    return name;
}

void Dish::setPrice(int _price) {
    price = _price;
}

int Dish::getPrice() const {
    return price;
}

// Methods for setting and displaying data

void Dish::setData() {
    cout << "\t\t\tEnter name of dish: ";
    string _name; 
    cin.ignore(); 
    getline(cin, _name);  // Allow full input including spaces
    setName(_name);

    cout << "\t\t\tEnter price of dish: ";
    int _price; 
    cin >> _price;
    setPrice(_price);
}

void Dish::getData() const {
    cout << "ID" << "\t\t\tName" << "\t\t\tPrice" << endl;
    cout << getID() << "\t\t\t" << getName() << "\t\t\t" << getPrice() << endl;
}
