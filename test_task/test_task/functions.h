#pragma once
#include "Service.h"
#include <string>
#include <vector>

void split(std::vector<std::string>* vec, std::string str, std::string delimiter);

Service create_service(std::string str);

void sort_timetable(std::vector<Service>* services);

void divide_timetable(std::vector<std::vector<Service>>* divided_timetable, std::vector<Service>* source_timetable);

bool comparator(Service& a, Service& b);