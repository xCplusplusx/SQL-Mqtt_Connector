#include "SmartHomeServer.h"

//Verbindung mit der Datenbank

void SQL::_holdon() {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	start = std::chrono::steady_clock::now();
	while (elapsed.count()<=5) {


		Sleep(10);
		end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); 
		

	}
	con->close();
	

}

SQL::SQL(std::string User, std::string Passwd) {

	_Passwd = Passwd;
	_User = User;
	_connect(User, Passwd);

}

SQL::~SQL() {

	delete con;

}

void SQL::_connect(std::string User, std::string Passwd) {
	

	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", User, Passwd);
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}
	
}

//Get Befehle 

int SQL::getDataInt(std::string Tabelle, int r, int co) {

	sql::Statement* stmt;
	sql::ResultSet* res;
	
	if (con->isValid()) {
		std::cout << "yes" << std::endl;
	}
	else {
		con = driver->connect("tcp://127.0.0.1:3306", _User, _Passwd);
	}
	// ...
	stmt = con->createStatement();
	// ...

	res = stmt->executeQuery("SELECT ID, Username FROM `test`.`test1`");
	while (res->next()) {

		std::cout << res->getInt(1) << " " << res->getString(2) << std::endl;

	}

	delete res;
	delete stmt;
	return 1;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MQTT::MQTT(const char* _id, const char* _topic, const char* _host, int _port) : mosquittopp(_id)
{
	mosqpp::lib_init();        // Mandatory initialization for mosquitto library
	this->keepalive = 60;    // Basic configuration setup for myMosq class
	this->id = _id;
	this->port = _port;
	this->host = _host;
	this->topic = _topic;
	connect_async(host,     // non blocking connection to broker request
		port,
		keepalive);
	loop_start();            // Start thread managing connection / publish / subscribe
};

MQTT::~MQTT() {
	loop_stop();            // Kill the thread
	mosqpp::lib_cleanup();    // Mosquitto library cleanup
}


bool MQTT::send_message(const  char* _message)
{
	// Send message - depending on QoS, mosquitto lib managed re-submission this the thread
	//
	// * NULL : Message Id (int *) this allow to latter get status of each message
	// * topic : topic to be used
	// * lenght of the message
	// * message
	// * qos (0,1,2)
	// * retain (boolean) - indicates if message is retained on broker or not
	// Should return MOSQ_ERR_SUCCESS
	int ret = publish(NULL, this->topic, strlen(_message), _message, 1, false);
	return (ret == MOSQ_ERR_SUCCESS);
}

void MQTT::on_disconnect(int rc) {
	std::cout << ">> myMosq - disconnection(" << rc << ")" << std::endl;
}

void MQTT::on_connect(int rc)
{
	if (rc == 0) {
		std::cout << ">> myMosq - connected with server" << std::endl;
	}
	else {
		std::cout << ">> myMosq - Impossible to connect with server(" << rc << ")" << std::endl;
	}
}

void MQTT::on_publish(int mid)
{
	std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << std::endl;
}