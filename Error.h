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
#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_


namespace sdds
{
    class Error
    {
        char* errormessagepointer;

    public:
        ~Error();
        Error(const Error& copy);
        Error& operator=(const Error& N);
        Error();
        Error(const char* message);
        Error& operator=(const char* Message);
        Error& setError(const char* errors);
        operator bool() const;
        Error& clear();
        std::ostream& ErrorInput(std::ostream& ostr) const;

    };
    std::ostream& operator<<(std::ostream& ostr, const Error& ErrrorMessage);
}
#endif // !SDDS_ERROR_H_

