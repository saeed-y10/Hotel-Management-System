#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login()
	{
		string Username;
		string Password;

		short FaildLoginCount = 0;
		bool LoginFailed = false;

		do
		{
			

			if (LoginFailed)
			{
				FaildLoginCount++;

				if (FaildLoginCount == 5)
				{
					cout << "\nYou Are Locked After 5 Faild Trail(s).\n";

					return false;
				}

				else
				{
					cout << "\nInvalid Username/Password!";
					cout << "\nYou Have " << 5 - FaildLoginCount << " Trail(s) To Login." << "\n";
				}
			}

			cout << "\nUsername : ";
			Username = clsInputValidate::ReadString();

			cout << "Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenu();
		
		return true;
	}

public:
	 
	static bool ShowLoginScreen()
	{
		clsUtil::ResetScreen();

		_DrawScreenHeader("\t\t     Login Screen");

		return _Login();
	}

};

