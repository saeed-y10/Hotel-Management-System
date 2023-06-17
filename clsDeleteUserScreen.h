#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:

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

	static void ShowDeleteUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t  Delete User Screen";

		_DrawScreenHeader(Title);

		string Username;

		cout << "\nEnter Username? ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not Found, Enter Another One: ";
			Username = clsInputValidate::ReadString();
		}

		if (Username == "Admin")
		{
			cout << "\nYou Cannot Delete This User!\n";

			return;
		}

		clsUser User = clsUser::Find(Username);

		_PrintUser(User);

		char Answer = 'N';

		cout << "Are You Sure To Delete This User? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted, Successfully.\n";

				_PrintUser(User);
			}

			else
			{
				cout << "\nError User was not Deleted.\n";
			}
		}
	}

};

