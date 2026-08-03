#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <QList>
#include <QTextStream>
#include "Vehicle.h"

class VehicleManager {
private:
    QList<Vehicle*> vehicles;
    QString dataFile;

public:
    VehicleManager(const QString& filename);
    ~VehicleManager();

    void loadFromFile();
    void saveToFile() const;

    bool addVehicle(Vehicle* v);
    Vehicle* searchById(const QString& id) const;
    void displayAll(QTextStream& out) const;
    void displayAvailable(QTextStream& out) const;
    bool rentVehicle(const QString& id, QTextStream& out);
    bool returnVehicle(const QString& id, QTextStream& out);
};

#endif // VEHICLEMANAGER_H
