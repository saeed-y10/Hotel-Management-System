#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsLoginRegisterScreen.h"

class clsManageUsersScreen : protected clsScreen
{

private:
	
	static void _GoBackToManageUsersMenuOption()
	{
		cout << "\nPress Any Key To Go Back To Manage Users Menu...\n";

		system("pause>0");

		ShowManageUsersMenu();
	}

	enum enManageUsersMenuOptions
	{
		eListUsersOption = 1,
		eAddNewUserOption = 2,
		eDeleteUserOption = 3,
		eUpdateUserOption = 4,
		eFindUserOption = 5,
		eLoginRegisterOption = 6,
		eBackToMainMenu = 7,
	};

	static enManageUsersMenuOptions _ReadManageUsersMenuOption()
	{
		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 7]? ";

		short Option = clsInputValidate::ReadShortNumberBetween(1, 7, "\t\t\t\t     Choose What Do You Want To Do? [1 To 7]? ");

		return (enManageUsersMenuOptions)Option;
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions Option)
	{
		switch (Option)
		{
		case enManageUsersMenuOptions::eListUsersOption:
		{
			clsUtil::ResetScreen();

			clsListUsersScreen::ShowListUsersScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eAddNewUserOption:
		{
			clsUtil::ResetScreen();

			clsAddNewUserScreen::ShowAddNewClientScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eDeleteUserOption:
		{
			clsUtil::ResetScreen();

			clsDeleteUserScreen::ShowDeleteUserScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eUpdateUserOption:
		{
			clsUtil::ResetScreen();

			clsUpdateUserScreen::ShowUpdateUserScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eFindUserOption:
		{
			clsUtil::ResetScreen();

			clsFindUserScreen::ShowFindUserScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eLoginRegisterOption:
		{
			clsUtil::ResetScreen();

			clsLoginRegisterScreen::ShowLoginRegisterScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		default:
		{
	     	return;

			break;
		}

		}
	}

	static void _ShowManageUsersMenu()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		clsUtil::ResetScreen();

		_DrawScreenHeader("\t\t   Manage Users Menu");

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "           Manage Users Menu" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[1] List Users." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[2] Add New User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[3] Delete User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[4] Update User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[5] Find User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[6] Login Register." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[7] Go Back." << " |\n";

		cout << left << setw(37) << " " << "==============================================\n" << endl;

		_PerformManageUsersMenuOption(_ReadManageUsersMenuOption());
	}

public:

	static void ShowManageUsersMenu()
	{
		_ShowManageUsersMenu();
	}

};

