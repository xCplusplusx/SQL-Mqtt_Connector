#include "SmartHomeServer.h"
#include <iostream>
#include <mqtt_client_cpp.hpp>
using namespace std;

int main() {

	SQL User_one("root", ""); //The User and the Password 
	MQTT User_two("Client", "/home/data", "The Adress of your Client", /* Port as a Int*/); //Please fill in your Data
	cout << User_one.getDataInt("h", 1, 1) << endl;
	//Sleep(6000);
	//cout << getDatabaseInt("h", 1, 1) << endl;


}