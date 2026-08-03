#include "Motorcycle.h"

Motorcycle::Motorcycle(QString id, QString brand, QString model, double price, bool rented, int engineCC)
    : Vehicle(id, brand, model, price, rented), engineCapacityCC(engineCC) {}

int Motorcycle::getEngineCapacity() const { return engineCapacityCC; }

QString Motorcycle::typeName() const {
    return "Motorcycle";
}

QString Motorcycle::toDisplayString() const {
    return "[Motorcycle] " + Vehicle::toDisplayString() + 
           QString(" | Engine: %1 CC").arg(engineCapacityCC);
}

QString Motorcycle::toFileString() const {
    return QString("Motorcycle|%1|%2|%3|%4|%5|%6")
        .arg(getId(), getBrand(), getModel(), QString::number(getPricePerDay()),
             QString::number(getIsRented()), QString::number(engineCapacityCC));
}
