#include "Main.h"

int main()
{
	Client::LoginInterface ^Interface = gcnew Client::LoginInterface();
	Interface->ShowDialog()

	return 0;
}