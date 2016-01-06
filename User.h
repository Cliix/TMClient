#pragma once
#include <Windows.h>
#include <string>

class CUser {
public:
	CUser()
	{

	}

	std::string Username = "";
	std::string Password = "";

	void Login();
private:

};