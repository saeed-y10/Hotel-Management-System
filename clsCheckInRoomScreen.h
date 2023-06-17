#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"
#include "clsCustomer.h"

class clsCheckInRoomScreen : protected clsScreen
{

private:

	static clsDate _ReadDate(string Message)
	{
		clsDate Date = clsInputValidate::ReadString();

		while (!Date.IsValid())
		{
			cout << Message;
			clsDate Date = clsInputValidate::ReadString();
		}

		return Date;
	}

	static clsCustomer _ReadCustomerInfo()
	{
		cout << "\nReading Customer Info:\n";
		cout << "________________________________________\n\n";
		
		cout << "First Name            : ";
		string FirstName = clsInputValidate::ReadString();

		cout << "Last Name             : ";
		string LastName = clsInputValidate::ReadString();

		cout << "Gender (M/F)          : ";
		string Gender = clsInputValidate::ReadString();

		cout << "Birth Date (1/12/2020): ";
		clsDate DateOfBirth = _ReadDate("Birth Date (1/12/2020): ");

		cout << "Phone Number          : ";
		string Phone = clsInputValidate::ReadString();

		cout << "Booking Days          : ";
		short BookingDays = clsInputValidate::ReadNumberbetween<short>(1, SHRT_MAX, "Booking Days          : ");

		return clsCustomer(FirstName, LastName, Gender, DateOfBirth, Phone, BookingDays);
	}

	static short _ReadRoomNumber()
	{
		cout << "\nEnter Room Number: ";

		return clsInputValidate::ReadNumberbetween<short>(1, SHRT_MAX, "Enter Room Number: ");
	}

public:

	static void ShowCheckInRoomScreen()
	{

	string Title = "\t\t Check-In Room Screen";

	char Answer = 'N';

	_DrawScreenHeader(Title);

	short RoomNumber = _ReadRoomNumber();

	clsRoom Room = clsRoom::Find(RoomNumber);

	if (Room.IsEmpty())
	{
		cout << "\nRoom With Number [" << RoomNumber << "] is not Found.\n";
		
		return;
	}

	else
	{
		if (Room.IsAvailable())
		{
			clsCustomer Customer = _ReadCustomerInfo();

			if (Room.CheckIn(Customer.FirstName, Customer.LastName, Customer.Gender, Customer.DateOfBirth, Customer.Phone, Customer.BookingDays))
			{
				Room.Save();

				cout << "\nRoom Booked Successfully.\n";
			}

			else
			{
				cout << "\nRoom Booking Failed.\n";
			}

		}

		else
		{
			cout << "\nSorry The Room is Busy.\n";
		}

	}

}

};

