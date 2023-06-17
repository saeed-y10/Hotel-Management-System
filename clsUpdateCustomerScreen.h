#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"

class clsUpdateCustomerScreen : protected clsScreen
{

private:

	static short _ReadRoomNumber()
	{
		cout << "\nEnter Room Number: ";

		return clsInputValidate::ReadNumberbetween<short>(0, SHRT_MAX, "Enter Room Number: ");
	}

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

	static void _PrintRoomCard(clsRoom Room)
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

	static void ShowUpdateCustomerScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRooms))
		{
			return;
		}

		char Answer = 'N';

		string Title = "\t\t Update Customer Screen";

		do
		{
			_DrawScreenHeader(Title);

			short RoomNumber = _ReadRoomNumber();

			if (!clsRoom::IsRoomExist(RoomNumber))
			{
				cout << "\nRoom With Number [" << RoomNumber << "] is not Found.\n";
			}

			else
			{
				clsRoom Room = clsRoom::Find(RoomNumber);

				if (Room.IsAvailable())
				{
					cout << "\nSorry The Room is Available.\n";
				}

				else
				{
					_PrintRoomCard(Room);

					cout << "Are You Sure To Update The Room Price? Y/N? ";
					cin >> Answer;

					if (toupper(Answer) == 'Y')
					{
						Room.Customer = _ReadCustomerInfo();

						clsRoom::enSaveResult SaveResult = Room.Save();

						switch (SaveResult)
						{
						case clsRoom::eSuccessfull:
							cout << "\nRoom Updaed, Successfully.\n";
							break;

						case clsRoom::eEmptyFaild:
							cout << "\nError Room was not Added Because it's Empty.\n";
							break;

						case clsRoom::eRoomExistFaild:
							cout << "\nError Room was not Added Because Room Nuber is Already Exist.\n";
							break;

						default:
							cout << "\nError Room was not Added Because it's Empty.\n";
							break;

						}

					}

					else
					{
						cout << "\nUpdate Canceled.\n";
					}
				}
			}

			cout << "\nDo You Want To Update More Customers? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
	
	}

};

