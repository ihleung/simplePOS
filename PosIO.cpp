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
#include "PosIO.h"

using namespace std;

namespace sdds
{
	std::ostream& operator<<(std::ostream& ostr, const PosIO& posIO)
	{
		posIO.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, PosIO& posIO)
	{
		posIO.read(istr);
		return istr;
	}
	std::ofstream& operator<<(std::ofstream& ofstr, const PosIO& pos)
	{
		pos.save(ofstr);
		return ofstr;
	}
	std::ifstream& operator>>(std::ifstream& ifstr, PosIO& pos)
	{
		pos.load(ifstr);
		return ifstr;
	}
	PosIO::~PosIO()
	{

	}
}