#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsListRoomsScreen.h"
#include "clsListAvailableRoomsScreen.h"
#include "clsListBusyRoomsScreen.h"
#include "clsCustomersSearchScreen.h"
#include "clsCheckInRoomScreen.h"
#include "clsCheckOutRoomScreen.h"
#include "clsManageUsersScreen.h"
#include "clsManageRoomsScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	static void _ShowListRoomsScreen()
	{
		clsListRoomsScreen::ShowListRoomsScreen();
	}

	static void _ShowListAvailableRoomsScreen()
	{
		clsListAvailableRoomsScreen::ShowListAvailableRoomsScreen();
	}
	
	static void _ShowListBusyRoomsScreen()
	{
		clsListBusyRoomsScreen::ShowListBusyRoomsScreen();
	}

	static void _ShowCustomersSearchScreen()
	{
		clsCustomersSearchScreen::ShowCustomersSearchScreen();
	}

	static void _ShowCheckInRoomScreen()
	{
		clsCheckInRoomScreen::ShowCheckInRoomScreen();
	}

	static void _ShowCheckOutRoomScreen()
	{
		clsCheckOutRoomScreen::ShowCheckOutRoomScreen();
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowManageRoomsScreen()
	{
		clsManageRoomsScreen::ShowManageRoomsMenu();
	}

	static void _GoBackToMainMenu()
	{
		cout << "\nPress Any Key To Go Back To Main Menu...\n";

		system("pause>0");

		ShowMainMenu();
	}

	enum enMainMenuOptions
	{
		eListRoomsOption = 1,
		eAvailableRoomsOption = 2,
		//eBusyRoomsOption = 3,
		eCustomersSearchOption = 3,
		eCheckInRoomOption = 4,
		eCheckOutRoomOption = 5,
		eManageRoomsOption = 6,
		eManageUsersOption = 7,
		eLogoutOption = 8,
		eExit = 9,
		eRefresh = 10,
	};

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static enMainMenuOptions _ReadMainMenuOption()
	{
		short Option;

		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 10]? ";

		Option = clsInputValidate::ReadShortNumberBetween(1, 10, "\t\t\t\t     Choose What Do You Want To Do? [1 To 10]? ");

		return (enMainMenuOptions)Option;
	}

	static void _PerformMainMenuOption(enMainMenuOptions Option)
	{
		switch (Option)
		{
		case enMainMenuOptions::eListRoomsOption:
		{
			_ShowListRoomsScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eAvailableRoomsOption:
		{
			_ShowListAvailableRoomsScreen();

			_GoBackToMainMenu();

			break;
		}

		/*case enMainMenuOptions::eBusyRoomsOption:
		{
			_ShowListBusyRoomsScreen();

			_GoBackToMainMenu();

			break;
		}*/

		case enMainMenuOptions::eCustomersSearchOption:
		{
			_ShowCustomersSearchScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eCheckInRoomOption:
		{
			_ShowCheckInRoomScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eCheckOutRoomOption:
		{
			_ShowCheckOutRoomScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eManageRoomsOption:
		{
			_ShowManageRoomsScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eManageUsersOption:
		{
			_ShowManageUsersScreen();

			_GoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eLogoutOption:
		{
			_Logout();

			break;
		}

		case enMainMenuOptions::eExit:
		{
			clsUtil::ResetScreen();

			exit(1);

			break;
		}

		case eRefresh:
		{
			cout << "\nDatabase Refreshed Successfully.\n";

			_GoBackToMainMenu();

			break;
		}

		default:
		{
			clsUtil::ResetScreen();

			_Logout();

			break;
		}

		}
	}

public:

	static void ShowMainMenu()
	{
		_DrawScreenHeader("\t\t       Main Menu");

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "                Main Menu" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[1] List Rooms." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[2] List Available Rooms." << "|\n";

		/*cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[3] Busy Rooms." << "|\n";*/

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[3] Customer Search." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[4] Check In Room." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[5] Check Out Room." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[6] Manage Rooms." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[7] Manage Users." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[8] Logout." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[9] Exit." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[10] Refresh." << "|\n";

		cout << left << setw(37) << " " << "==============================================\n\n";

		_PerformMainMenuOption(_ReadMainMenuOption());
	}

};

