#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsAddNewRoomScreen.h"
#include "clsDeleteRoomScreen.h"
#include "clsUpdateRoomPriceScreen.h"
#include "clsUpdateCustomerScreen.h"

class clsManageRoomsScreen : clsScreen
{

private:

	static void _ShowAddNewRoomScreen()
	{
		clsAddNewRoomScreen::ShowAddNewRoomScreen();
	}

	static void _ShowDeleteRoomScreen()
	{
		clsDeleteRoomScreen::ShowDeleteRoomScreen();
	}

	static void _ShowUpdateRoomPriceScreen()
	{
		clsUpdateRoomPriceScreen::ShowUpdateRoomScreen();
	}

	static void _ShowUpdateCustomerScreen()
	{
		clsUpdateCustomerScreen::ShowUpdateCustomerScreen();
	}

	static void _GoBackToManageRoomsMenu()
	{
		cout << "\nPress Any Key To Go Back To Manage Rooms Menu...\n";

		system("pause>0");

		ShowManageRoomsMenu();
	}

	enum enManageRoomsMenuOptions
	{
		eAddNewRoomOption = 1,
		eDeleteRoomOption = 2,
		eUpdateRoomPriceOption = 3,
		eUpdateCustomerOption = 4,
		eBackToMainMenu = 5,
	};

	static enManageRoomsMenuOptions _ReadManageRoomsMenuOption()
	{
		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 5]? ";

		short Option = clsInputValidate::ReadShortNumberBetween(1, 5, "\t\t\t\t     Choose What Do You Want To Do? [1 To 5]? ");

		return (enManageRoomsMenuOptions)Option;
	}


	static void _PerformManageUsersMenuOption(enManageRoomsMenuOptions Option)
	{
		switch (Option)
		{
		
		case enManageRoomsMenuOptions::eAddNewRoomOption:
		{
			_ShowAddNewRoomScreen();

			_GoBackToManageRoomsMenu();

			break;
		}

		case enManageRoomsMenuOptions::eDeleteRoomOption:
		{
			_ShowDeleteRoomScreen();


			_GoBackToManageRoomsMenu();

			break;
		}

		case enManageRoomsMenuOptions::eUpdateCustomerOption:
		{

			_ShowUpdateCustomerScreen();

			_GoBackToManageRoomsMenu();

			break;
		}

		case enManageRoomsMenuOptions::eUpdateRoomPriceOption:
		{
			_ShowUpdateRoomPriceScreen();

			_GoBackToManageRoomsMenu();

			break;
		}
		
		case enManageRoomsMenuOptions::eBackToMainMenu:
		{
			return;

			break;
		}

		default:
		{
			return;

			break;
		}

		}
	}

	static void _ShowManageRoomsMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRooms))
		{
			return;
		}

		string Title = "\t\t Manage Rooms Screen";

		_DrawScreenHeader(Title);

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "           Manage Rooms Menu" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[1] Add New Room." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[2] Delete Room." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[3] Update Room Price" << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[4] Update Customer." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[5] Go Back." << " |\n";

		cout << left << setw(37) << " " << "==============================================\n" << endl;

		_PerformManageUsersMenuOption(_ReadManageRoomsMenuOption());
	}

public:

	static void ShowManageRoomsMenu()
	{
		_ShowManageRoomsMenu();
	}

};

