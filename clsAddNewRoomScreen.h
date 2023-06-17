#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"

class clsAddNewRoomScreen : protected clsScreen
{

private:

	static float _ReadRoomPrice()
	{
		cout << "\nEnter Room Price: ";

		return clsInputValidate::ReadNumberbetween<float>(0, FLT_MAX, "Enter Room Price: ");
	}

public:


	static void ShowAddNewRoomScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRooms))
		{
			return;
		}

		string Title = "\t\t Add New Room Screen";

		char Answer = 'N';

		do
		{

			_DrawScreenHeader(Title);

			cout << "\nAdding New Room:\n";
			cout << "________________________________________\n";

			cout << "\nEnter Room Number: ";
			short RoomNumber = clsInputValidate::ReadNumberbetween<short>(0, SHRT_MAX, "Enter Room Number: ");

			while (clsRoom::IsRoomExist(RoomNumber))
			{
				cout << "\nRoom Number is Already Used, Enter Another One: ";
				RoomNumber = clsInputValidate::ReadNumberbetween<short>(0, SHRT_MAX, "Enter Room Number: ");
			}

			float RoomPrice = _ReadRoomPrice();

			clsRoom Room = clsRoom::GetNewRoomObject(RoomNumber, RoomPrice);

			clsRoom::enSaveResult SaveResult = Room.Save();

			switch (SaveResult)
			{

			case clsRoom::eSuccessfull:
				cout << "\nRoom Added, Successfully.\n";
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

			cout << "\nDo You Want To Add More Rooms Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
	
	}

};

