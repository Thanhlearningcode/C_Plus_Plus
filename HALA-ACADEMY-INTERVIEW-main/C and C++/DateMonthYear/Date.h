#ifndef _Date_Lib_H_
#define _Date_Lib_H_ // Header 

#include <iostream>
class Date{
    private : 

    int day, month, year; // property of Date

    public :

    Date ( int a=1, int m=1 , int y = 2000);

    Date &operator +=(int day);

    friend std::ostream& operator<<(std::ostream& out, const Date& date);
    private:

    void Checkvar(); // Lệnh này để check ví dụ ngày ko được quá 31 ngày , tháng ko được quá 12 tháng

    bool Namnhuan(int year);





};

#endif // _Date_Lib_H_