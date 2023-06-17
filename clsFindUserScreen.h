#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
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

	static void ShowFindUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t   Find User Screen";

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

		if (!User.IsEmpty())
		{
			cout << "\nUser is Found.\n";
		}

		else
		{
			cout << "\nUser was not Found.\n";
		}

		_PrintUser(User);
	}
};

