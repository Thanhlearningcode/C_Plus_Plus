#include "../Header/menu.h"
#include <iomanip> // For setw()

using namespace std;

void showMainMenu() {
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t| RESTAURANT MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t 1. Manager" << endl;
    cout << "\t\t\t 2. Staff" << endl;
    cout << "\t\t\t 3. Exit program" << endl;
    cout << "\t\t\t............................" << endl;
    cout << "\t\t\tPlease Enter Your Choice: ";
}

void menuManager(Database &database) {
    int choice;
    while (true) {
        system("cls");
        cout << "\t\t\t-----------------------------" << endl;
        cout << "\t\t\t|       MANAGER WORKING      |" << endl;
        cout << "\t\t\t-----------------------------" << endl;
        cout << "\t\t\t 1. Set up table" << endl;
        cout << "\t\t\t 2. Add dish" << endl;
        cout << "\t\t\t 3. Edit dish" << endl;
        cout << "\t\t\t 4. Delete dish" << endl;
        cout << "\t\t\t 5. List of dishes" << endl;
        cout << "\t\t\t 6. Turn back main menu" << endl;
        cout << "\t\t\t 7. Exit program" << endl;
        cout << "\t\t\t............................" << endl;
        cout << "\t\t\tPlease Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                setupTable(database);
                break;
            case 2:
                addDish(database);
                break;
            case 3:
                editDish(database);
                break;
            case 4:
                deleteDish(database);
                break;
            case 5:
                showMenu(database);
                break;
            case 6:
                return;  // Return to the main menu
            case 7:
                exit(0);
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}

void setupTable(Database &database) {
    int numTables;
    cout << "Enter quantity of table you want to set up: ";
    cin >> numTables;
    database.numTable = numTables;
    database.managerData.setNumTable(numTables);
    database.staffaData.getNumTable(numTables);
    cout << "Table setup completed!" << endl;
}

void addDish(Database &database) {
    cout << "--------------------------------------------- Menu ----------------------------------------------------" << endl;
    database.managerData.showMenu();
    cout << "----------------------------------------- Add dish ------------------------------------------------" << endl;
    database.managerData.addDish();
    cout << "Dish added successfully!" << endl;
}

void editDish(Database &database) {
    int ID_input;
    cout << "Enter ID of Dish you want to edit: ";
    cin >> ID_input;
    database.managerData.editDish(ID_input);
    cout << "Dish updated successfully!" << endl;
}

void deleteDish(Database &database) {
    int ID_input;
    cout << "Enter ID of Dish you want to delete: ";
    cin >> ID_input;
    database.managerData.deleteDish(ID_input);
    cout << "Dish deleted successfully!" << endl;
}

void showMenu(Database &database) {
    cout << "--------------------------------------------- Menu ----------------------------------------------------" << endl;
    database.managerData.showMenu();
}

void menuStaff(Database &database) {
    int choice, _tableID;
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t|       STAFF WORKING       |" << endl;
    cout << "\t\t\t-----------------------------" << endl;

    cout << "\t\t\tHave you booked a table?" << endl;
    cout << "\t\t\t1. Yes" << endl;
    cout << "\t\t\t2. No" << endl;
    cout << "\t\t\tPlease Enter Your Choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\t\t\tPlease Enter Your Table ID: ";
        cin >> _tableID;
        database.staffaData.chooseTable(_tableID);
    } else {
        database.staffaData.displayTable();
        if (database.staffaData.isFull()) {
            cout << "Sorry. There are no tables available." << endl;
            return;
        } else {
            cout << "\t\t\tPlease choose one of these Table IDs: ";
            cin >> _tableID;
            database.staffaData.chooseTable(_tableID);
        }
    }

    orderMenu(database, _tableID);
}

void orderMenu(Database &database, int tableID) {
    int choice;
    while (true) {
        cout << "\t\t\t 1. Add dish" << endl;
        cout << "\t\t\t 2. Cancel dish" << endl;
        cout << "\t\t\t 3. Edit dish" << endl;
        cout << "\t\t\t 4. List of dish" << endl;
        cout << "\t\t\t 5. Pay the bill" << endl;
        cout << "\t\t\t 6. Turn back staff menu" << endl;
        cout << "\t\t\t 7. Turn back main menu" << endl;
        cout << "\t\t\t 8. Exit program" << endl;
        cout << "\t\t\tPlease Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addOrder(database, tableID);
                break;
            case 2:
                cancelOrder(database, tableID);
                break;
            case 3:
                editOrder(database, tableID);
                break;
            case 4:
                showOrder(database, tableID);
                break;
            case 5:
                payBill(database, tableID);
                break;
            case 6:
                return;
            case 7:
                return;
            case 8:
                exit(0);
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}

// You can implement similar helper methods for addOrder, cancelOrder, editOrder, showOrder, and payBill

int main() {
    Database database;
    mainMenu(database);
    return 0;
}
