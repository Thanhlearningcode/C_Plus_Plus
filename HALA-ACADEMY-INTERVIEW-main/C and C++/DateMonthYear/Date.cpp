#include "Date.h"
using namespace std;
Date :: Date(int day, int month , int year){
this->day = day;
this->month=month;
this->year= year;
Checkvar();
}

Date& Date ::operator+=(int day1){
day=day+day1;
Checkvar();
return *this;
}

ostream& operator<<(ostream& out, const Date& date) {
    out << date.day << "//" << date.month << "//" << date.year;
    return out;
}

void Date::Checkvar(){
int arr[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // số ngày trong mỗi tháng của một năm không nhuận. Tháng 1 có 31 ngày, tháng 2 có 28 ngày trong năm không nhuận
if (Namnhuan(year)) arr[1] = 29;

    while (day > arr[month - 1]) {
        day = day - arr[month - 1];
        month++;
        if (month > 12) {
            month = 1;
            year++;
            arr[1] =Namnhuan(year) ? 29 : 28; // thang 2 thi nam nhuan thi 29 ngay , khong thi` 28 ngayf
        }
    }

    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = day + arr[month - 1];
    }
}
bool Date::Namnhuan(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); 
}
// Dựa vào các quy tắc trên, năm nhuận là năm:

// Chia hết cho 4 nhưng không chia hết cho 100.
// Hoặc năm chia hết cho 400.

