#include "../Header/manager.h"
#include <iomanip> // For setw()

using namespace std;

list<Dish> Manager::getMenu() {
    return menu;
}

void Manager::setNumTable(int _numTable) {
    numTable = _numTable;
}

int Manager::getNumTable() {
    return numTable;
}

void Manager::addDish() {
    Dish newDish;

    cout << "Enter name of dish you want: ";
    string _name;
    cin.ignore();
    getline(cin, _name); // Allow spaces in the name
    newDish.setName(_name);

    cout << "Enter price of dish you want: ";
    int _price;
    cin >> _price;
    newDish.setPrice(_price);

    menu.push_back(newDish);
}

void Manager::editDish(int ID_input) {
    bool found = false;
    for (auto &i : menu) {
        if (i.getID() == ID_input) {
            found = true;
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
            cout << "\t\t\t\t\tData found " << endl << endl;
            cout << "ID" << "\t\tName" << "\t\tPrice" << endl;
            cout << i.getID() << "\t\t" << i.getName() << "\t\t" << i.getPrice() << endl;
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;

            cout << "\n\t\t\tPlease re-enter Price of dish you want to change: ";
            int _price;
            cin >> _price;
            i.setPrice(_price);
            return;
        }
    }
    if (!found) {
        cout << "Dish with ID " << ID_input << " not found!" << endl;
    }
}

void Manager::deleteDish(int ID_input) {
    list<Dish>::iterator it;
    bool found = false;
    for (it = menu.begin(); it != menu.end(); ++it) {
        if (it->getID() == ID_input) {
            found = true;
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
            cout << "\t\t\t\t\tData found " << endl << endl;
            cout << "ID" << "\t\tName" << "\t\tPrice" << endl;
            cout << it->getID() << "\t\t" << it->getName() << "\t\t" << it->getPrice() << endl;
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;

            cout << "\n\t\t\tAre you sure you want to delete this item?" << endl;
            int ans = 0;
            do {
                cout << "\t\t\t1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "\t\t\tPlease Enter Your Choice: ";
                cin >> ans;
                if (ans == 2) return;
            } while (ans != 1);

            menu.erase(it);
            return;
        }
    }
    if (!found) {
        cout << "Dish with ID " << ID_input << " not found!" << endl;
    }
}

void Manager::showMenu() {
    int count = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\tList of your ordered dishes" << endl << endl;
    cout << "No" << "\t\tID" << "\t\tName" << "\t\tPrice" << endl;
    for (auto &i : menu) {
        count++;
        cout << setw(3) << count << "\t\t" 
             << setw(3) << i.getID() << "\t\t"
             << setw(10) << i.getName() << "\t\t"
             << setw(6) << i.getPrice() << endl;
    }
}
