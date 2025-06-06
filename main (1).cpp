#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Date.h"
#include "Incident.h"

Date getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./app_user.exe <command> [arguments...]" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "report_incident") {
        if (argc < 5) {
            std::cerr << "Usage: ./app_user.exe report_incident <area> <type> <description>" << std::endl;
            return 1;
        }

        std::string area = argv[2];
        std::string type = argv[3];
        std::string description = argv[4];

        Date today = getCurrentDate();

        std::ofstream fout("user_reports.txt", std::ios::app);
        if (!fout) {
            std::cerr << "Failed to open user_reports.txt" << std::endl;
            return 1;
        }

        fout << area << " " << type << "\n" << description << "\n"
             << today.getDay() << " " << today.getMonth() << " " << today.getYear() << std::endl;

        fout.close();
        std::cout << "Incident reported successfully!" << std::endl;
    }
    else if (command == "view_reports") {
        std::ifstream fin("incidents.txt");
        if (!fin) {
            std::cerr << "Could not open incidents.txt" << std::endl;
            return 1;
        }

        int count;
        fin >> count;

        std::cout << "Total Incidents: " << count << std::endl;

        for (int i = 0; i < count; ++i) {
        std::string id, area, type, description;
        int day, month, year;

        fin >> id >> area >> type;
        fin.ignore();
        std::getline(fin, description);
        fin >> day >> month >> year;

        Date date(day, month, year);
        Incident incident(id, area, type, description, date);
        incident.print();
        std::cout << std::endl;
    }


        fin.close();
    }
    else if (command == "filter_by_area") {
        if (argc < 3) {
            std::cerr << "Usage: ./app_user.exe filter_by_area <area>" << std::endl;
            return 1;
        }

        std::string targetArea = argv[2];
        std::ifstream fin("incidents.txt");
        if (!fin) {
            std::cerr << "Could not open incidents.txt" << std::endl;
            return 1;
        }

        int count;
        fin >> count;

        for (int i = 0; i < count; ++i) {
            std::string id, area, type, description;
            int day, month, year;

            fin >> id >> area >> type;
            fin.ignore();
            std::getline(fin, description);
            fin >> day >> month >> year;

            Date date(day, month, year);
            Incident incident(id, area, type, description, date);

            if (area == targetArea) {
                incident.print();
                std::cout << std::endl;
            }
        }

        fin.close();
    }
    else if (command == "filter_by_type") {
    if (argc < 3) {
        std::cerr << "Usage: ./app_user.exe filter_by_area <area>" << std::endl;
        return 1;
    }

    std::string targetType = argv[2];
    std::ifstream fin("incidents.txt");
    if (!fin) {
        std::cerr << "Could not open incidents.txt" << std::endl;
        return 1;
    }

    int count;
    fin >> count;

    for (int i = 0; i < count; ++i) {
        std::string id, area, type, description;
        int day, month, year;

        fin >> id >> area >> type;
        fin.ignore();
        std::getline(fin, description);
        fin >> day >> month >> year;

        Date date(day, month, year);
        Incident incident(id, area, type, description, date);

        if (type == targetType) {
            incident.print();
            std::cout << std::endl;
        }
    }

    fin.close();
}

    return 0;
}
