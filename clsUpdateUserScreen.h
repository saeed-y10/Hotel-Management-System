#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{

private:

	static int _ReadPermissions()
	{
		int Permissions = 0;

		char Answer = 'N';

		cout << "\nDo You Want To Give Full Access? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return clsUser::enPermissions::pAll;
		}

		cout << "\nDo You Want To Give Access To:\n";

		cout << "\nShow Rooms List? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions = clsUser::enPermissions::pListRooms;
		}

		cout << "\nShow Availabel Rooms List? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions = clsUser::enPermissions::pListAvailableRooms;
		}

		cout << "\nShow Busy Rooms List? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions = clsUser::enPermissions::pListBusyRooms;
		}

		cout << "\nSearch Customers and Rooms? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pSearch;
		}

		cout << "\nCheck In Room? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pCheckInRoom;
		}

		cout << "\nCheck Out Room? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pCheckOutRoom;
		}

		cout << "\nManage Rooms? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageRooms;
		}

		cout << "\nManage Users? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter First Name   : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name    : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "Enter Email        : ";
		User.Email = clsInputValidate::ReadString();

		cout << "Enter Phone Number : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "Enter Password     : ";
		User.Password = clsInputValidate::ReadString();

		if (User.Username == "Admin")
		{
			User.Permissions = clsUser::enPermissions::pAll;
		}

		else
		{
			cout << "\nRead Permissions:\n";
			User.Permissions = _ReadPermissions();
		}

	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:\n";
		cout << "________________________________________\n";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUsername    : " << User.Username;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n________________________________________\n\n";
	}

public:
	
	static void ShowUpdateUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t  Update User Screen";

		_DrawScreenHeader(Title);

		string Username;

		cout << "\nEnter Username? ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not Found, Enter Another One: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);

		_PrintUser(User);

		char Answer = 'N';

		cout << "Are You Sure To Update This User? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			cout << "\nUpdate User:\n";
			cout << "________________________________________\n";

			_ReadUserInfo(User);

			cout << "________________________________________\n";

			clsUser::enSaveResult SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResult::svSucceeded:
			{
				cout << "\nUser Updated, Successfully.\n";
				_PrintUser(User);
				break;
			}

			case clsUser::enSaveResult::svEmptyFaild:
			{
				cout << "\nError User was not Updated Because it's Empty.\n";
				break;
			}
			}

		}
	}

};

