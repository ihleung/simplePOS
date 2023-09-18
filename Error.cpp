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
#include <iostream>
#include <cstring>
#include "Error.h"

using namespace std;

namespace sdds
{
	Error::Error()
	{
		errormessagepointer = nullptr;
	}

	Error& Error::operator=(const char* Message)
	{
		if (Message && Message[0] != '\0')
		{
			clear();
			setError(Message);
		}
		else
		{
			clear();
		}
		return *this;
	}

	Error::Error(const char* message)
	{
		setError(message);
	}

	Error::~Error()
	{
		clear();
	}

	Error& Error::operator=(const Error& E)
	{
		if (this != &E)
		{
			clear();
			setError(E.errormessagepointer);
		}
		return *this;
	}

	Error::operator bool() const
	{
		return errormessagepointer != nullptr;
	}

	Error& Error::clear()
	{
		if (errormessagepointer)
		{
			delete[] errormessagepointer;
			errormessagepointer = nullptr;
		}
		return *this;
	}

	Error& Error::setError(const char* errors)
	{
		if (errors)
		{
			errormessagepointer = new char[strlen(errors) + 1];
			strcpy(errormessagepointer, errors);
		}
		else
		{
			errormessagepointer = nullptr;
		}

		return *this;
	}

	Error::Error(const Error& copy)
	{
		setError(copy.errormessagepointer);
	}

	std::ostream& Error::ErrorInput(std::ostream& ostr) const
	{
		if (errormessagepointer)
		{
			ostr << errormessagepointer;
		}
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Error& ErrrorMessage)
	{
		ErrrorMessage.ErrorInput(ostr);
		return ostr;
	}

}

