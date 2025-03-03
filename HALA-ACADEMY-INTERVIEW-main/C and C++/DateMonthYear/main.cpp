/* Bài tập về nhà Lập trình hướng đối tượng

 Tên  : Nguyễn Văn Thành



*/

#include <iostream>
#include "Date.h"
using namespace std;

int main() {
     int day, month, year, dayADD;

    
     cout << "Ngày giờ ban đầu (dd mm yyyy): ";
     cin >> day >> month >> year;

   
     Date bandau(day, month, year);
    cout << "Ngày ban đầu: " << bandau << endl;

    
    cout << "Cộng thêm: ";
    cin >> dayADD;

    
    Date ketqua = bandau;
    ketqua += dayADD;

    
    cout << "Kết quả sau khi thêm " << dayADD << " ngày là: " << ketqua<< endl;

    return 0;
}
