#include <iostream> 
#include "Service.h"
#include <fstream>
#include <string>
#include <list>
#include "functions.h"
#include <algorithm>

using namespace std;

string input_file = "originial_timetable.txt";
string output_file = "modified_timetable.txt";

int main() {

	ifstream fin(input_file.c_str());
	ofstream fout(output_file.c_str());

	vector<Service> services;

	//Each line converts into Service object
	string str;
	while (fin.good()) {
		getline(fin, str);
		Service service = create_service(str);
		services.push_back(service);
	}

	//Finding efficient services
	sort_timetable(&services);
	
	//Dividing and sorting timetable for file writting
	vector<vector<Service>> divided_timetable(2, vector<Service>());
	divide_timetable(&divided_timetable, &services);
	sort(divided_timetable[0].begin(), divided_timetable[0].end(), comparator);
	sort(divided_timetable[1].begin(), divided_timetable[1].end(), comparator);

	//Output
	for (auto service : divided_timetable[0]) {
		str = service.get_bus_company() + " " + service.get_departure_time_str() + " " + service.get_arrival_time_str();
		fout << str << endl;
	}
	fout << endl;
	for (auto service : divided_timetable[1]) {
		str = service.get_bus_company() + " " + service.get_departure_time_str() + " " + service.get_arrival_time_str();
		fout << str << endl;
	}

	return 0;
}