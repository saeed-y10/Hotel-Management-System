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

class clsCustomersSearchScreen : protected clsScreen
{

private:

	enum enSearchOption
	{
		eByRoomNumber = 1,
		eByCustomerName = 2,
		eGoBack = 3,
	};

	static short _ReadRoomNumber()
	{
		cout << "\nEnter Room Number: ";

		return clsInputValidate::ReadNumberbetween<short>(1, SHRT_MAX, "Enter Room Number: ");
	}

	static string _ReadName()
	{
		cout << "\nEnter Customer Name: ";

		return clsInputValidate::ReadString();
	}

	static clsRoom _FindByRoomNumber(short Number)
	{
		return clsRoom::Find(Number);
	}

	static vector<clsRoom> _FindByName(string Name)
	{
		return clsRoom::Find(Name);
	}

	static enSearchOption _ReadSearchOption()
	{
		cout << "\n [1] Find By Room Number.";
		cout << "\n [2] Find By Customer Name.";
		cout << "\n [3] Go Back.\n";

		cout << "\n Enter What To Do? ";

		return (enSearchOption)clsInputValidate::ReadNumberbetween<short>(1, 3, " Enter What To Do? ");
	}

	static void _PrintHeader()
	{
		cout << " ______________________________________________________________________________________________________________________\n\n";

		cout << " |" << left << setw(11) << "Room Number";
		cout << "|" << left << setw(10) << "Room Price";
		cout << "|" << left << setw(23) << "Name";
		cout << "|" << left << setw(6) << "Gender";
		cout << "|" << left << setw(4) << "Age";
		cout << "|" << left << setw(13) << "Check In Date";
		cout << "|" << left << setw(14) << "Check Out Date";
		cout << "|" << left << setw(12) << "Booking Days";
		cout << "|" << left << setw(15) << "Total Bill" << "|\n";

		cout << " ______________________________________________________________________________________________________________________\n\n";
	}

	static void _PrintRoomRecordLine(clsRoom Room)
	{
		cout << " |" << left << setw(11) << Room.Number();
		cout << "|" << left << setw(10) << Room.Price;
		cout << "|" << left << setw(23) << Room.Customer.FullName();
		cout << "|" << left << setw(6) << Room.Customer.Gender;
		cout << "|" << left << setw(4) << Room.Customer.DateOfBirth.CalculateAgeInYears();
		cout << "|" << left << setw(13) << Room.Customer.GetCheckInDate().ToString();
		cout << "|" << left << setw(14) << Room.Customer.CheckOutDate().ToString();
		cout << "|" << left << setw(12) << Room.Customer.BookingDays;
		cout << "|$" << left << fixed << setw(14) << setprecision(2) << Room.TotalBill() << "|";
	}

	static void _PrintResults(short Number)
	{
		clsRoom Room = clsRoom::Find(Number);

		if (Room.IsEmpty())
		{
			cout << "\nRoom With Number [" << Number << "] is not Found.\n\n";

			return;
		}

		else if (Room.IsAvailable())
		{
			cout << "\nThe Room is Empty.\n\n";

			return;
		}

		else
		{
			_PrintHeader();

			_PrintRoomRecordLine(Room);
			cout << endl;
		}

		cout << " ______________________________________________________________________________________________________________________\n\n";

		return;
	}

	static void _PrintResults(string Name)
	{
		vector<clsRoom> vRooms = clsRoom::Find(Name);

		if (vRooms.size() == 0)
		{
			cout << "\nCustomer With Name [" + Name + "] is not Found.\n\n";
		}

		else
		{
			_PrintHeader();

			for (clsRoom Room : vRooms)
			{
				_PrintRoomRecordLine(Room);
				cout << endl;
			}

			cout << " _____________________________________________________________________________________________________________________\n\n";
		}

	}

	static void _PerformSearchOption(enSearchOption Option)
	{
		switch (Option)
		{

		case enSearchOption::eByRoomNumber:
		{
			short RoomNumber = _ReadRoomNumber();

			_PrintResults(RoomNumber);

			break;
		}

		case enSearchOption::eByCustomerName:
		{
			string CustomerName = _ReadName();

			_PrintResults(CustomerName);

			break;
		}

		case enSearchOption::eGoBack:
		{
			return;
		}

		default:
			break;
		}
	}

public:

	static void ShowCustomersSearchScreen()
	{
		string Title = "\t\t Customer Search Screen";

		char Answer = 'N';

		do
		{
			_DrawScreenHeader(Title);

			enSearchOption Option = _ReadSearchOption();

			if (Option == enSearchOption::eGoBack)
				break;

			_PerformSearchOption(Option);

			cout << "Do You Want To Search Again? Y/N? ";

			Answer = 'N';

			cin >> Answer;

		}
		while (toupper(Answer) == 'Y');
		
	}

};

