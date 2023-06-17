#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"

class clsUpdateRoomPriceScreen : protected clsScreen
{

private:

	static short _ReadRoomNumber()
	{
		cout << "\nEnter Room Number: ";

		return clsInputValidate::ReadNumberbetween<short>(0, SHRT_MAX, "Enter Room Number: ");
	}

	static float _ReadRoomPrice()
	{
		cout << "\nNew Room Price: ";

		return clsInputValidate::ReadNumberbetween<float>(0, FLT_MAX, "New Room Price: ");
	}

public:

	static void ShowUpdateRoomScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRooms))
		{
			return;
		}

		char Answer = 'N';

		string Title = "\t\t Update Room Price Screen";

		_DrawScreenHeader(Title);

		cout << "\nUpdating Room Price:\n";
		cout << "________________________________________\n";

		short RoomNumber = _ReadRoomNumber();

		if (!clsRoom::IsRoomExist(RoomNumber))
		{
			cout << "\nRoom With Number [" << RoomNumber << "] is not Found.\n";
		}

		else
		{
			float RoomPrice = _ReadRoomPrice();

			cout << "\nAre You Sure To Update The Room Price? Y/N? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				clsRoom Room = clsRoom::Find(RoomNumber);

				Room.Price = RoomPrice;

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

		cout << "\nDo You Want To Update More Rooms Price? Y/N? ";
		cin >> Answer;
	}

};

