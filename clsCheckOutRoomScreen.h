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

class clsCheckOutRoomScreen : protected clsScreen
{

private:

	static short _ReadRoomNumber()
	{
		cout << "\nEnter Room Number: ";

		return clsInputValidate::ReadNumberbetween<short>(1, SHRT_MAX, "Enter Room Number: ");
	}

	static void _PrintRoomCard(clsRoom Room)
	{
		cout << " _____________________________________________________________________________________________________________________\n\n";

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

		cout << " |" << left << setw(11) << Room.Number();
		cout << "|" << left << setw(10) << Room.Price;
		cout << "|" << left << setw(23) << Room.Customer.FullName();
		cout << "|" << left << setw(6) << Room.Customer.Gender;
		cout << "|" << left << setw(4) << Room.Customer.DateOfBirth.CalculateAgeInYears();
		cout << "|" << left << setw(13) << Room.Customer.GetCheckInDate().ToString();
		cout << "|" << left << setw(14) << Room.Customer.CheckOutDate().ToString();
		cout << "|" << left << setw(12) << Room.Customer.BookingDays;
		cout << "|$" << left << fixed << setw(14) << setprecision(2) << Room.TotalBill() << "|\n";

		cout << " ______________________________________________________________________________________________________________________\n\n";
	}

public:

	static void ShowCheckOutRoomScreen()
	{

		string Title = "\t\t Check-Out Room Screen";

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
			if (!Room.IsAvailable())
			{

				_PrintRoomCard(Room);

				char Answer = 'N';

				cout << "Are You Sure You Want To Unbooking This Room? Y/N? ";
				cin >> Answer;

				if (toupper(Answer) == 'Y')
				{
					if (Room.CheckOut())
					{
						Room.Save();

						cout << "\nRoom Unbooked Successfully.\n";
					}

					else
					{
						cout << "\nRoom Unbooking Failed.\n";
					}
				}

				else
				{
					cout << "\nRoom Unbooking was Canceled.\n";
				}

			}

			else
			{
				cout << "\nSorry The Room is Available.\n";
			}

		}

	}
};

