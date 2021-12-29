#pragma once
#include <string>
#include <mysql.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <thread>
#include <chrono>

#include <mosquittopp.h>
//Verbindung mit der Datenbank
extern class SQL {

private:
	sql::Driver* driver;
	sql::Connection* con;
	std::string _Passwd, _User;
	void _holdon();
	void _connect(std::string User, std::string Passwd);
public:
	SQL(std::string User, std::string Passwd);
	~SQL();
	int getDataInt(std::string, int, int);
};



extern class MQTT : public mosqpp::mosquittopp
{
private:
	const char* host;
	const char* id;
	const char* topic;
	int                port;
	int                keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_publish(int mid);
public:
	MQTT(const char* id, const char* _topic, const char* host, int port);
	~MQTT();
	bool send_message(const char* _message);
};
//Get Befehle 
