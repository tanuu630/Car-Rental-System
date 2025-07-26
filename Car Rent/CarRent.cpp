#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Car {
    int id;
    string brand;
    string model;
    float pricePerDay;
    bool isAvailable;
};

struct Rental {
    int carId;
    string customerName;
    int days;
    float totalCost;
};

vector<Car> cars = {
    {1, "Toyota", "Fortuner", 1500, true},
    {2, "Hyundai", "Creta", 1000, true},
    {3, "Tata", "Nexon", 800, true},
    {4, "Mahindra", "Thar", 1800, true}
};

vector<Rental> rented;

void showAvailableCars() {
    cout << "\n--- Available Cars ---\n";
    for (auto &car : cars) {
        if (car.isAvailable) {
            cout << "ID: " << car.id
                 << " | Brand: " << car.brand
                 << " | Model: " << car.model
                 << " | Price/Day: Rs. " << car.pricePerDay << "\n";
        }
    }
}

void rentCar() {
    showAvailableCars();
    int choice;
    cout << "\nEnter Car ID to Rent: ";
    cin >> choice;
    bool found = false;
    for (auto &car : cars) {
        if (car.id == choice && car.isAvailable) {
            string name;
            int days;
            cout << "Enter your name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter number of days: ";
            cin >> days;

            car.isAvailable = false;
            float cost = car.pricePerDay * days;

            rented.push_back({car.id, name, days, cost});

            cout << "\n✅ Car rented successfully!\n";
            cout << "--- Invoice ---\n";
            cout << "Customer Name: " << name << "\n";
            cout << "Car: " << car.brand << " " << car.model << "\n";
            cout << "Days: " << days << "\n";
            cout << fixed << setprecision(2);
            cout << "Total Cost: Rs. " << cost << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "❌ Car not available or invalid ID!\n";
    }
}

void returnCar() {
    int carId;
    cout << "\nEnter Car ID to Return: ";
    cin >> carId;
    bool found = false;
    for (auto &car : cars) {
        if (car.id == carId && !car.isAvailable) {
            car.isAvailable = true;
            for (auto it = rented.begin(); it != rented.end(); ++it) {
                if (it->carId == carId) {
                    cout << "\n✅ Car returned successfully!\n";
                    rented.erase(it);
                    found = true;
                    break;
                }
            }
            break;
        }
    }
    if (!found) {
        cout << "❌ Car is not currently rented or invalid ID!\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n========= Car Rental System =========\n";
        cout << "1. Show Available Cars\n";
        cout << "2. Rent a Car\n";
        cout << "3. Return a Car\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showAvailableCars();
                break;
            case 2:
                rentCar();
                break;
            case 3:
                returnCar();
                break;
            case 4:
                cout << "🚗 Thank you for using CarRent!\n";
                break;
            default:
                cout << "❗ Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}

//g++ CarRent.cpp -o CarRent
//./CarRent