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

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Date.h"
#include "Error.h"

using namespace std;
namespace sdds
{
   
    Date::Date()
    {
       getSystemDate(m_year, m_month, m_day, m_hour, m_minute, dateFlag = false);
    }

    Date::Date(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = 0;
        m_minute = 0;
        dateOnly(true);
        validate();
    }

    Date::Date(int year, int month, int day, int hour, int minute)
    {
        setDate(year, month, day, hour, minute);
        dateFlag = false;
        validate();
    }

    Date& Date::setDate(int year, int month, int day, int hour, int minute)
    {
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = hour;
        m_minute = minute;
        return *this;
    }

    bool Date::validate()
    {
        int value = 0;
        value = daysOfMonth(m_year, m_month);
        m_error.clear();
        if (!(m_year >= MIN_YEAR && m_year <= MAX_YEAR))
        {
            m_error = "Invalid Year";
        }
        else if (!(m_month >= 1 && m_month <= 12))
        {
            m_error = "Invalid Month";
        }
        else if (!(m_day >= 1 && m_day <= value))
        {
            m_error = "Invalid Day";
        }
        else if (!dateFlag)
        {
            if (!(m_hour >= 0 && m_hour <= 23))
            {
                m_error = "Invalid Hour";
            }
            else if (!(m_minute >= 0 && m_minute <= 59))
            {
                m_error = "Invlid Minute";
            }
        }

        return !m_error;
    }

    int Date::setDateValue() const
    {
        return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute);
    }

    bool Date::operator==(const Date& other) const
    {
        return setDateValue() == other.setDateValue();
    }

    bool Date::operator!=(const Date& other) const
    {
        return setDateValue() != other.setDateValue();
    }

    bool Date::operator<(const Date& other) const
    {
        return setDateValue() < other.setDateValue();
    }

    bool Date::operator>(const Date& other) const
    {
        return setDateValue() > other.setDateValue();
    }

    bool Date::operator<=(const Date& other) const
    {
        return setDateValue() <= other.setDateValue();
    }

    bool Date::operator>=(const Date& other) const
    {
        return setDateValue() >= other.setDateValue();
    }

    Date& Date::dateOnly(bool stop)
    {
        dateFlag = stop;
        if (dateFlag)
        {
            m_hour = 0;
            m_minute = 0;
        }  
        return *this;
    }

    Date::operator bool() const
    {
        return !m_error;
    }

    const Error& Date::error() const
    {
        return m_error;
    }

    std::ostream& Date::displayDate(std::ostream& ostr) const
    {
        ostr << m_year << "/" << setw(2) << setfill('0') << m_month << "/" << setw(2) << setfill('0') << m_day;
        if (dateFlag == false)
        {
            ostr << ", " << setw(2) << setfill('0') << m_hour << ":" << setw(2) << setfill('0') << m_minute;
        }
        return ostr;

    }

    std::istream& Date::readDate(istream& istr)
    {
        m_error.clear();
        setDate(0, 0, 0, 0, 0);
       
        if (!(istr >> m_year))
        {
            m_error = "Cannot read year entry";
        }
        else if (!(istr.ignore() >> m_month))
        {
            m_error = "Cannot read month entry";
        }
        else if (!(istr.ignore() >> m_day))
        {
            m_error = "Cannot read day entry";
        }
        else if (!dateFlag)
        {
            if (!(istr.ignore() >> m_hour))
            {
                m_error = "Cannot read hour entry";
            }
            else if (!(istr.ignore() >> m_minute))
            {
                m_error = "Cannot read minute entry";
            }
        }
        else
        {
            m_hour = 0;
            m_minute = 0;
        }

        if (istr)
        {
            validate();
        }

        return istr;
    }

    //Provided by the professor
    /**********************************************************************************/
    void Date::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly)
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int Date::uniqueDateValue(int year, int mon, int day, int hour, int min) const
    {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int Date::daysOfMonth(int year, int month) 
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    /**********************************************************************************/


    std::ostream& operator<<(std::ostream& ostr, const Date& date)
    {
        if (!date)
        {
            ostr << date.error() << "(";
            date.displayDate(ostr);
            ostr << ")";
        }
        else
        {
            date.displayDate(ostr);
        }
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Date& date)
    {
       
        return date.readDate(istr);
    }

}
