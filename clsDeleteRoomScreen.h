#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"

class clsDeleteRoomScreen : protected clsScreen
{

private:



public:

	static void ShowDeleteRoomScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRooms))
		{
			return;
		}

		string Title = "\t\t Delete Room Screen";

		char Answer = 'N';

		_DrawScreenHeader(Title);

		cout << "\nDeleting  Room:\n";
		cout << "________________________________________\n";

		cout << "\nEnter Room Number: ";
		short RoomNumber = clsInputValidate::ReadNumberbetween<short>(0, SHRT_MAX, "Enter Room Number: ");

		if (!clsRoom::IsRoomExist(RoomNumber))
		{
			cout << "\nRoom With Number [" << RoomNumber << "] is not Found.\n";
		}

		else
		{
			clsRoom Room = clsRoom::Find(RoomNumber);

			cout << "\nAre You Sure To Delete The Room? Y/N? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				if (Room.Delete())
				{
					cout << "\nRoom Deleted Successfully.\n";
				}

				else
				{
					cout << "\nRoom Delete Failed.\n";
				}
			}

			else
			{
				cout << "\nRoom Delete Canceled.\n";
			}
		}
	}

};

