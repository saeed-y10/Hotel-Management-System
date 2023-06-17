#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsRoom.h"

using namespace std;

class clsListRoomsScreen : clsScreen
{

private:

	static string _GetAvailableOrBusy(bool Status)
	{
		return (Status ? "Available" : "Busy");
	}

	static void _PrintRoomRecordLine(clsRoom Room)
	{
		cout << left << setw(19) << " " << "|" << left << setw(20) << Room.Number();
		cout << "|" << left << fixed << setprecision(2) << setw(20) << Room.Price;
		cout << "|" << left << setw(39) << _GetAvailableOrBusy(Room.IsAvailable()) << "|";
	}

public:

	static void ShowListRoomsScreen()
	{
		vector<clsRoom> vRooms = clsRoom::GetRoomsList();

		string Title = "\t\t   Rooms List Screen";
		string SubTitle = "\t\t     (" + to_string(vRooms.size()) + ") Room(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << left << setw(19) << " " << "___________________________________________________________________________________\n\n";
		
		cout << left << setw(19) << " ";
		cout << "|" << left << setw(20) << "Room Number";
		cout << "|" << left << setw(20) << "Room Price";
		cout << "|" << left << setw(39) << "Status" << "|\n";

		cout << left << setw(19) << " " << "___________________________________________________________________________________\n\n";


		if (vRooms.size() == 0)
		{
			cout << left << setw(19) << " " << "|";
			cout << left << setw(81) << "Sorry There Are No Rooms in The System!" << "|\n";
		}

		else
		{
			for (clsRoom Room : vRooms)
			{
				_PrintRoomRecordLine(Room);
				cout << endl;
			}
		}

		cout << left << setw(19) << " " << "___________________________________________________________________________________\n";
	}

};

