#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsCustomer : public clsPerson
{

private:

	string _Gender;
	clsDate _DateOfBirth;
	short _BookingDays;
	clsDate _CheckInDate;
	clsDate _CheckOutDate;
	float _TotalBill;

public:

	clsCustomer()
		: clsPerson("Empty", "Empty", "Empty", "Empty")
	{
		_Gender = "Empty";
		_BookingDays = 0;
		_DateOfBirth = clsDate(1, 1, 1);
		_CheckInDate = clsDate(1, 1, 1);
		_CheckOutDate = clsDate(1, 1, 1);
	}

	clsCustomer(string FirstName, string LastName, string Gender, clsDate DateOfBirth, string Phone, short BookingDays, clsDate CheckInDate = clsDate())
		: clsPerson(FirstName, LastName, "Empty", Phone)
	{
		SetGender(Gender);
		_BookingDays = BookingDays;
		_DateOfBirth = DateOfBirth;
		_CheckInDate = CheckInDate;
		_CheckOutDate = clsDate::IncreaceDateByNDays(BookingDays, _CheckInDate);
	}

	void SetGender(string Gender)
	{
		if (clsString::UpperAllLetters(Gender) == "M" || clsString::UpperAllLetters(Gender) == "MALE")
			_Gender = "Male";

		else if (clsString::UpperAllLetters(Gender) == "F" || clsString::UpperAllLetters(Gender) == "FEMALE")
			_Gender = "Female";

		else
			_Gender = "Empty";
	}

	string GetGender()
	{
		return _Gender;
	}
	__declspec(property(get = GetGender, put = SetGender)) string Gender;

	void SetBookingDays(short BookingDays)
	{
		if (clsDate().IsDateBeforeDate2(clsDate::IncreaceDateByNDays(BookingDays, _CheckInDate)))
		{
			_BookingDays = BookingDays;
		}

		return;
	}

	short GetBookingDays()
	{
		return _BookingDays;
	}
	__declspec(property(get = GetBookingDays, put = SetBookingDays)) short BookingDays;

	float TotalBill(float RoomPrice)
	{
		return (float)(BookingDays * RoomPrice);
	}

	void SetDateOfBirth(clsDate DateOfBirth)
	{
		_DateOfBirth = DateOfBirth;
	}

	clsDate GetDateOfBirth()
	{
		return _DateOfBirth;
	}
	__declspec(property(get = GetDateOfBirth, put = SetDateOfBirth)) clsDate DateOfBirth;

	clsDate GetCheckInDate()
	{
		return _CheckInDate;
	}

	clsDate CheckOutDate()
	{
		return _CheckOutDate;
	}

	bool IsReservationActive()
	{
		return clsDate::GetSystemDate().IsDateBeforeDate2(CheckOutDate());
	}

};

