/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.cpp
Version 1.3
Author	Ivan Leung
Revision History
-----------------------------------------------------------
Date      Reason
2023/3/21 updated citation and sources information for all related files
2023/3/21 updated the Error.cpp
2023/4/7  updated the Date.h and Date.cpp
2023/4/7  updated the Item.cpp
2023/4/10 updated the PosApp.cpp and PosApp.h
-----------------------------------------------------------*/
#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_

#include "POS.h"
#include "Error.h"

namespace sdds
{
    class Date
    {
        int m_year = 0;
        int m_month = 0;
        int m_day = 0;
        int m_hour = 0;
        int m_minute = 0;
        bool dateFlag = false;
        Error m_error;

       
    public:
        //Provided by the professor
       /**********************************************************************************/
        void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
        int uniqueDateValue(int year, int mon, int day, int hour, int min) const;
        int daysOfMonth(int year, int month);
        /**********************************************************************************/

        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int minute = 0);
        bool validate();
        Date& setDate(int year, int month, int day, int hour, int min);
        int setDateValue() const;
        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator>(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator>=(const Date& other) const;
        Date& dateOnly(bool flag);
        operator bool() const;
        const Error& error() const;
        std::ostream& displayDate(std::ostream& ostr) const;
        std::istream& readDate(std::istream& istr);

    };
    std::ostream& operator<<(std::ostream& ostr, const Date& date);
    std::istream& operator>>(std::istream& istr, Date& date);
}
#endif // !SDDS_DATE_H_

