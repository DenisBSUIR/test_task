#include <iostream>
#include "Service.h"
#include "functions.h"
#include <stdlib.h>
#include <map>

using namespace std;

void split(vector<string>* vec, string str, string delimiter) {
	//string delimiter = " ";

	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos) {
		token = str.substr(0, pos);
		(*vec).push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	(*vec).push_back(str);
}

Service create_service(string str) {
	
	vector<string> service_parts;
	split(&service_parts, str, " ");

	Service service;
	
	service.set_bus_company(service_parts[0]);

	vector<string> time_parts;
	split(&time_parts, service_parts[1], ":");
	tm time;
	time.tm_hour = atoi(time_parts[0].c_str());
	time.tm_min = atoi(time_parts[1].c_str());

	service.set_departure_time(time);
	service.set_departure_time_str(service_parts[1]);

	time_parts.clear();
	split(&time_parts, service_parts[2], ":");
	time.tm_hour = atoi(time_parts[0].c_str());
	time.tm_min = atoi(time_parts[1].c_str());

	service.set_arrival_time(time);
	service.set_arrival_time_str(service_parts[2]);

	return service;
}

void sort_timetable(vector<Service>* services)
{
	vector<Service> servs; 

	//Drop each service longer than one hour
	for (auto service : *services) {
		int hour_diff, min_diff;
		hour_diff = service.get_arrival_time().tm_hour - service.get_departure_time().tm_hour;
		if (hour_diff == 1) {
			min_diff = service.get_departure_time().tm_min - service.get_arrival_time().tm_min;
			if (min_diff >= 0) {
				servs.push_back(service);
			}
		}
		else if (hour_diff < 1) {
			servs.push_back(service);
		}
	}

	services->swap(servs);
	servs.clear();

	//Creating container <index, times> for easier manipulation,
	//where times is <departure_time, arrival_time, travel_time> and presents as time in mins since 00:00
	map<int, vector<int>> service_times;
	int i = 0;
	for (auto service : *services) {
		int departure_time = service.get_departure_time().tm_hour * 60 + service.get_departure_time().tm_min;
		int arrival_time = service.get_arrival_time().tm_hour * 60 + service.get_arrival_time().tm_min;
		if (arrival_time < departure_time) {
			arrival_time += 24 * 60;
		}
		vector<int> vec;
		vec.push_back(departure_time);
		vec.push_back(arrival_time);
		vec.push_back(arrival_time - departure_time);
		service_times.insert(make_pair(i, vec));
		i++;
	}

	enum times {
		dep,
		arrv,
		travel
	};

	for (auto serv : service_times) {
		
		//If after next loop skipped will be still false, that means serv is efficient or unique   
		bool skipped = false;
		for (auto comp : service_times) {
			if (serv == comp) {
				continue;
			}

			//Next, if services not intersects
			if (serv.second[arrv] < comp.second[dep] || comp.second[arrv] < serv.second[dep]) {
				continue;
			}

			//Check same daparture time
			if (serv.second[dep] == comp.second[dep]) {
				string posh = "Posh";
				if (serv.second[travel] > comp.second[travel]) {
					skipped = true;
				}
				else if (serv.second[travel] == comp.second[travel]) {
					if ((*services)[serv.first].get_bus_company() != posh) {
						skipped = true;
					}
				}
			}
			
			//Check other situations
			if (serv.second[dep] < comp.second[dep] && serv.second[arrv] >= comp.second[arrv]) {
				skipped = true;
			}
		}
		if (!skipped) {
			servs.push_back((*services)[serv.first]);
		}
	}

	services->swap(servs);
}

void divide_timetable(vector<vector<Service>>* divided_timetable, vector<Service>* source_timetable)
{
	for (auto service : *source_timetable) {
		if (service.get_bus_company() == "Posh") {
			(*divided_timetable)[0].push_back(service);
		}
		else {
			(*divided_timetable)[1].push_back(service);
		}
	}
}

bool comparator(Service &a, Service &b)
{
	int a_departure_time = a.get_departure_time().tm_hour * 60 + a.get_departure_time().tm_min;
	int b_departure_time = b.get_departure_time().tm_hour * 60 + b.get_departure_time().tm_min;
	
	if (a_departure_time < b_departure_time) {
		return true;
	}

	return false;
}
