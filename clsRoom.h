#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsCustomer.h"
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsRoom
{

private:

	enum enMode
	{
		eEmpty = 0,
		eUpdate = 1,
		eAddNew = 2,
	};

	enMode _Mode;
	short _Number;
	float _Price;
	bool _Available;
	bool _MarkForDelete;

	static string _ConvertRoomObjectToLine(clsRoom &Room, string Seperator = "#//#")
	{
		string Line = "";

		if (Room.IsAvailable())
			Room.Customer = clsCustomer();

		if (!Room.IsAvailable() && !Room.Customer.IsReservationActive())
		{
			Room.CheckOut();

			Room._Available = true;
			Room.Customer = clsCustomer();
		}

		Line += to_string(Room.IsAvailable()) + Seperator;
		Line += to_string(Room.Number()) + Seperator;
		Line += to_string(Room.Price) + Seperator;
		Line += Room.Customer.FirstName + Seperator;
		Line += Room.Customer.LastName + Seperator;
		Line += Room.Customer.Gender + Seperator;
		Line += Room.Customer.DateOfBirth.ToString() + Seperator;
		Line += Room.Customer.Phone + Seperator;
		Line += Room.Customer.GetCheckInDate().ToString() + Seperator;
		Line += to_string(Room.Customer.BookingDays);

		return Line;
	}

	static clsRoom _ConvertLineToRoomObject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);

		clsRoom Room = clsRoom(enMode::eUpdate, stoi(vLine[0]), stoi(vLine[1]), stof(vLine[2]));

		clsDate CheckInDate = clsDate(vLine[8]);
		short BookingDays = stoi(vLine[9]);

		if (Room.IsAvailable())
			Room.Customer = clsCustomer();

		else
			Room.Customer = clsCustomer(vLine[3], vLine[4], vLine[5], clsDate(vLine[6]), vLine[7], BookingDays, CheckInDate);

		if (!Room.IsAvailable() && !Room.Customer.IsReservationActive())
		{
			Room.CheckOut();
		}

		return Room;
	}

	static vector<clsRoom> _LoadRoomsDataFromFile(string FileName = "Rooms.txt")
	{
		vector<clsRoom> vRooms;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

				if (!Room.IsAvailable() && !Room.Customer.IsReservationActive())
				{
					Room.CheckOut();

					Room.Save();
				}

				vRooms.push_back(Room);
			}

			File.close();
		}

		return vRooms;
	}

	static void _SaveRoomsDataToFile(vector<clsRoom> &vRooms, string FileName = "Rooms.txt")
	{
		fstream File;

		File.open(FileName, ios::out);

		if (File.is_open())
		{
			string Line;

			for (clsRoom &Room : vRooms)
			{
				if (Room._MarkForDelete == false)
				{
					if (!Room.IsAvailable() && !Room.Customer.IsReservationActive())
					{
						Room.CheckOut();

						Room._Available = true;

						Room.Customer = clsCustomer();
					}

					Line = _ConvertRoomObjectToLine(Room);

					File << Line << endl;
				}
			}

			File.close();
		}

	}

	static void _AddDataLineToFile(string DataLine, string FileName)
	{
		fstream File;

		File.open(FileName, ios::out | ios::app);

		if (File.is_open())
		{
			File << DataLine << endl;

			File.close();
		}

	}

	static clsRoom _GetEmptyRoomObject()
	{
		return clsRoom(enMode::eEmpty, 0, 0);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertRoomObjectToLine(*this), "Rooms.txt");
	}

	void _Update()
	{
		vector<clsRoom> vRooms = _LoadRoomsDataFromFile();

		for (clsRoom &Room : vRooms)
		{
			if (Room.Number() == Number())
			{
				Room = *this;

				_SaveRoomsDataToFile(vRooms);
			}

		}
	}

public:

	clsRoom(enMode Mode, bool Status, short Number, float Price)
	{
		_Mode = Mode;
		_Number = Number;
		_Price = Price;
		_Available = Status;
		_MarkForDelete = false;
		Customer = clsCustomer();
	}

	clsRoom(enMode Mode, short Number, float Price)
	{
		_Mode = Mode;
		_Number = Number;
		_Price = Price;
		_Available = true;
		_MarkForDelete = false;
	}

	clsCustomer Customer;

	static clsRoom GetNewRoomObject(short RoomNumber, float RoomPrice = 20)
	{
		return clsRoom(enMode::eAddNew, RoomNumber, RoomPrice);
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::eEmpty);
	}

	bool IsAvailable()
	{
		return _Available;
	}

	short Number()
	{
		return _Number;
	}

	void SetPrice(float Price)
	{
		if (Price > 0)
		{
			_Price = Price;
		}
	}

	float GetPrice()
	{
		return _Price;
	}
	__declspec(property(get = GetPrice, put = SetPrice)) float Price;

	bool CheckIn(string FirstName, string LastName, string Gender, clsDate DateOfBirth, string Phone, short BookingDays, clsDate CheckInDate = clsDate::GetSystemDate())
	{
		if (!IsAvailable())
			return false;

		clsDate CheckOutDate = clsDate::IncreaceDateByNDays(BookingDays, CheckInDate);

		if (!clsDate().IsDateBeforeDate2(CheckOutDate))
			return false;

		else
		{
			_Available = false;

			Customer = clsCustomer(FirstName, LastName, Gender, DateOfBirth, Phone, BookingDays, CheckInDate);

			return true;
		}
		
		return false;
	}

	bool CheckOut()
	{
		if (!IsAvailable())
		{
			_Available = true;

			Customer = clsCustomer();

			return true;
		}

		return false;
	}

	static clsRoom Find(short Number)
	{
		fstream File;

		File.open("Rooms.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

				if (Room.Number() == Number)
				{
					return Room;
				}

			}

			File.close();
		}

		return _GetEmptyRoomObject();
	}

	static vector<clsRoom> Find(string Name)
	{
		vector<clsRoom> vRooms;

		fstream File;

		File.open("Rooms.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

					if (Room.Customer.FullName() == Name)
					{
						vRooms.push_back(Room);
					}
			}

			File.close();
		}

		return vRooms;
	}

	static bool IsRoomExist(short Number)
	{
		return (!Find(Number).IsEmpty());
	}

	enum enSaveResult
	{
		eEmptyFaild = 0,
		eRoomExistFaild = 1,
		eRoomNotExistFaild = 2,
		eSuccessfull = 3,
	};

	enSaveResult Save()
	{
		switch (_Mode)
		{

		case enMode::eEmpty:
			return enSaveResult::eEmptyFaild;

		case enMode::eUpdate:
		{
			if (IsRoomExist(Number()))
			{
				_Update();

				return enSaveResult::eSuccessfull;
			}

			else
			{
				return enSaveResult::eRoomNotExistFaild;
			}
		}

		case enMode::eAddNew:
		{
			if (!IsRoomExist(Number()))
			{
				_Mode = enMode::eUpdate;

				_AddNew();

				return enSaveResult::eSuccessfull;
			}

			else
			{
				return enSaveResult::eRoomExistFaild;
			}
		}

		default:
		{
			enSaveResult::eEmptyFaild;
		}

		}

		return enSaveResult::eEmptyFaild;
	}

	bool Delete()
	{
		vector<clsRoom> vRooms = _LoadRoomsDataFromFile();

		for (clsRoom& Room : vRooms)
		{
			if (Room.Number() == Number())
			{
				Room._MarkForDelete = true;

				*this = _GetEmptyRoomObject();

				_SaveRoomsDataToFile(vRooms);

				return true;
			}
		}

		return false;
	}

	bool IsThereAvailableRoom()
	{
		fstream File;

		File.open("Rooms.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

				if (Room.IsAvailable())
				{
					return true;
				}

			}

			File.close();
		}

		return false;
	}

	static vector<clsRoom> GetAvailableRoomsList()
	{
		vector<clsRoom> vRooms;

		fstream File;

		File.open("Rooms.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

				if (Room.IsAvailable())
				{
					vRooms.push_back(Room);
				}

			}

			File.close();
		}

		return vRooms;
	}

	static vector<clsRoom> GetBusyRoomsList()
	{
		vector<clsRoom> vRooms;

		fstream File;

		File.open("Rooms.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsRoom Room = _ConvertLineToRoomObject(Line);

				if (!Room.IsAvailable())
				{
					vRooms.push_back(Room);
				}

			}

			File.close();
		}

		return vRooms;
	}

	static vector<clsRoom> GetRoomsList()
	{
		return _LoadRoomsDataFromFile();
	}

	float TotalBill()
	{
		if (!IsAvailable())
		{
			return (float) (Price * Customer.BookingDays);
		}

		return 0;
	}

	static void Refresh()
	{
		vector<clsRoom> vRooms = _LoadRoomsDataFromFile();

		for (clsRoom& Room : vRooms)
		{
			if (!Room.Customer.IsReservationActive())
			{
				Room._Available = true;
				Room.Customer = clsCustomer();

				Room.Save();
			}
		}

		_SaveRoomsDataToFile(vRooms);
	}

	//bool Refresh()
	//{
	//  _Update();

	//	return true;
	//}

};

