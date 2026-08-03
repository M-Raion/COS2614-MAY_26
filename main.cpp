#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "VehicleManager.h"
#include "Car.h"
#include "Motorcycle.h"

QTextStream qin(stdin);
QTextStream qout(stdout);

// Helper for strict numeric validation
double readDouble(const QString& prompt) {
    QString input;
    bool ok;
    double val;
    do {
        qout << prompt;
        qout.flush();
        input = qin.readLine().trimmed();
        val = input.toDouble(&ok);
        if (!ok || val < 0) {
            qout << "\nInvalid input. Please enter a valid positive number.\n";
        }
    } while (!ok || val < 0);
    return val;
}

int readInt(const QString& prompt) {
    QString input;
    bool ok;
    int val;
    do {
        qout << prompt;
        qout.flush();
        input = qin.readLine().trimmed();
        val = input.toInt(&ok);
        if (!ok || val < 0) {
            qout << "\nInvalid input. Please enter a valid positive integer.\n";
        }
    } while (!ok || val < 0);
    return val;
}

QString readString(const QString& prompt) {
    QString input;
    do {
        qout << prompt;
        qout.flush();
        input = qin.readLine().trimmed();
        if (input.isEmpty()) {
            qout << "\nInput cannot be empty.\n";
        }
    } while (input.isEmpty());
    return input;
}

void displayMenu() {
    qout << "\n=== Vehicle Rental Management System ===\n";
    qout << "1. Add Vehicle\n";
    qout << "2. Search Vehicle by ID\n";
    qout << "3. Display All Vehicles\n";
    qout << "4. Display Available Vehicles\n";
    qout << "5. Rent Vehicle\n";
    qout << "6. Return Vehicle\n";
    qout << "7. Exit\n";
    qout << "Choose an option: ";
    qout.flush();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    VehicleManager manager("vehicles.txt");
    manager.loadFromFile();

    bool running = true;
    while (running) {
        displayMenu();
        QString choice = qin.readLine().trimmed();

        if (choice == "1") {
            int type = readInt("Enter type (1 for Car, 2 for Motorcycle): ");
            if (type != 1 && type != 2) {
                qout << "\nInvalid type selected.\n";
                continue;
            }

            QString id = readString("Enter ID: ");
            if (manager.searchById(id) != nullptr) {
                qout << "\nError: A vehicle with this ID already exists.\n";
                continue;
            }

            QString brand = readString("Enter Brand: ");
            QString model = readString("Enter Model: ");
            double price = readDouble("Enter Price Per Day: ");

            Vehicle* newVehicle = nullptr;
            if (type == 1) {
                int doors = readInt("Enter number of doors: ");
                int seats = readInt("Enter number of seats: ");
                newVehicle = new Car(id, brand, model, price, false, doors, seats);
            } else {
                int cc = readInt("Enter Engine Capacity (CC): ");
                newVehicle = new Motorcycle(id, brand, model, price, false, cc);
            }

            if (manager.addVehicle(newVehicle)) {
                qout << "\nVehicle added successfully.\n";
            }
        }
        else if (choice == "2") {
            QString id = readString("Enter ID to search: ");
            Vehicle* v = manager.searchById(id);
            if (v) {
                qout << "Found: " << v->toDisplayString() << "\n";
            } else {
                qout << "\nVehicle not found.\n";
            }
        }
        else if (choice == "3") {
            qout << "\n--- All Vehicles ---\n";
            manager.displayAll(qout);
        }
        else if (choice == "4") {
            qout << "\n--- Available Vehicles ---\n";
            manager.displayAvailable(qout);
        }
        else if (choice == "5") {
            QString id = readString("Enter ID to rent: ");
            if (manager.rentVehicle(id, qout)) {
                manager.saveToFile(); // Save state changes
            }
        }
        else if (choice == "6") {
            QString id = readString("Enter ID to return: ");
            if (manager.returnVehicle(id, qout)) {
                manager.saveToFile(); // Save state changes
            }
        }
        else if (choice == "7") {
            qout << "\nSaving data and exiting...\n";
            running = false; // Destructor saves data
        }
        else {
            qout << "\nInvalid option. Please try again.\n";
        }
    }

    return 0; // Exits, triggering VehicleManager destructor
}
