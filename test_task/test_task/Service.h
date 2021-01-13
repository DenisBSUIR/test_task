#pragma once
#include <ctime>
#include <string>

class Service
{
public:
	Service();
	Service(std::string bus_company, tm departure_time, tm arrival_time);
	~Service();

	void set_bus_company(std::string bus_company);
	void set_departure_time(tm departure_time);
	void set_arrival_time(tm arrival_time);
	void set_departure_time_str(std::string departure_time_str);
	void set_arrival_time_str(std::string arrival_time_str);

	std::string get_bus_company();
	tm get_departure_time();
	tm get_arrival_time();
	std::string get_departure_time_str();
	std::string get_arrival_time_str();

private:
	std::string bus_company;
	std::string departure_time_str;
	std::string arrival_time_str;
	tm depatrure_time;
	tm arrival_time;
};

