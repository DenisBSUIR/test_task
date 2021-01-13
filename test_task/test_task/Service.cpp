#include "Service.h"

using namespace std;

Service::Service()
{
}

Service::Service(string bus_company, tm depatrure_time, tm arrival_time)
	:bus_company(bus_company), depatrure_time(depatrure_time), arrival_time(arrival_time)
{
}

Service::~Service()
{
}

void Service::set_bus_company(string bus_company)
{
	this->bus_company = bus_company;
}

void Service::set_departure_time(tm departure_time)
{
	this->depatrure_time = departure_time;
}

void Service::set_arrival_time(tm arrival_time)
{
	this->arrival_time = arrival_time;
}

void Service::set_departure_time_str(std::string departure_time_str)
{
	this->departure_time_str = departure_time_str;
}

void Service::set_arrival_time_str(std::string arrival_time_str)
{
	this->arrival_time_str = arrival_time_str;
}

string Service::get_bus_company()
{
	return bus_company;
}

tm Service::get_departure_time()
{
	return depatrure_time;
}

tm Service::get_arrival_time()
{
	return arrival_time;
}

std::string Service::get_departure_time_str()
{
	return departure_time_str;
}

std::string Service::get_arrival_time_str()
{
	return arrival_time_str;
}
