#include "VehicleManager.h"
#include "Car.h"
#include "Motorcycle.h"
#include <QFile>
#include <QStringList>

VehicleManager::VehicleManager(const QString& filename) : dataFile(filename) {}

VehicleManager::~VehicleManager() {
    saveToFile(); // Ensure data is saved on exit
    qDeleteAll(vehicles);
}

void VehicleManager::loadFromFile() {
    QFile file(dataFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return; 
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() < 6) continue;

        QString type = parts[0];
        QString id = parts[1];
        QString brand = parts[2];
        QString model = parts[3];
        double price = parts[4].toDouble();
        bool isRented = parts[5].toInt() == 1;

        if (type == "Car" && parts.size() == 8) {
            int doors = parts[6].toInt();
            int seats = parts[7].toInt();
            vehicles.append(new Car(id, brand, model, price, isRented, doors, seats));
        } else if (type == "Motorcycle" && parts.size() == 7) {
            int cc = parts[6].toInt();
            vehicles.append(new Motorcycle(id, brand, model, price, isRented, cc));
        }
    }
    file.close();
}

void VehicleManager::saveToFile() const {
    QFile file(dataFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (Vehicle* v : vehicles) {
            out << v->toFileString() << "\n";
        }
        file.close();
    }
}

bool VehicleManager::addVehicle(Vehicle* v) {
    if (searchById(v->getId()) != nullptr) {
        return false; // ID already exists
    }
    vehicles.append(v);
    return true;
}

Vehicle* VehicleManager::searchById(const QString& id) const {
    for (Vehicle* v : vehicles) {
        if (v->getId() == id) {
            return v;
        }
    }
    return nullptr;
}

void VehicleManager::displayAll(QTextStream& out) const {
    if (vehicles.isEmpty()) {
        out << "\nNo vehicles in the system.\n";
        return;
    }
    for (Vehicle* v : vehicles) {
        out << v->toDisplayString() << "\n";
    }
}

void VehicleManager::displayAvailable(QTextStream& out) const {
    bool found = false;
    for (Vehicle* v : vehicles) {
        if (!v->getIsRented()) {
            out << v->toDisplayString() << "\n";
            found = true;
        }
    }
    if (!found) {
        out << "\nNo vehicles are currently available.\n";
    }
}

bool VehicleManager::rentVehicle(const QString& id, QTextStream& out) {
    Vehicle* v = searchById(id);
    if (!v) {
        out << "\nError: Vehicle not found.\n";
        return false;
    }
    if (v->getIsRented()) {
        out << "\nError: Vehicle is already rented.\n";
        return false;
    }
    v->setIsRented(true);
    out << "\nSuccess: " << v->getBrand() << " " << v->getModel() << " has been rented.\n";
    return true;
}

bool VehicleManager::returnVehicle(const QString& id, QTextStream& out) {
    Vehicle* v = searchById(id);
    if (!v) {
        out << "\nError: Vehicle not found.\n";
        return false;
    }
    if (!v->getIsRented()) {
        out << "\nError: Vehicle is not currently rented.\n";
        return false;
    }
    v->setIsRented(false);
    out << "\nSuccess: " << v->getBrand() << " " << v->getModel() << " has been returned.\n";
    return true;
}
