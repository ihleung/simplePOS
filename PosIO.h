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
#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
namespace sdds
{
	class PosIO 
	{
	public:
		virtual ~PosIO();
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual std::ofstream& save(std::ofstream& oftr) const = 0;
		virtual std::ifstream& load(std::ifstream& iftr) = 0;

	};
	std::ostream& operator<<(std::ostream& ostr, const PosIO& posIO);
	std::istream& operator>>(std::istream& istr, PosIO& posIO);
	std::ofstream& operator<<(std::ofstream& ofstr, const PosIO& pos);
	std::ifstream& operator>>(std::ifstream& ifstr, PosIO& pos);
}
#endif // !SDDS_POSIO_H_

