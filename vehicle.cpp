#include "Vehicle.h"

Vehicle::Vehicle(QString id, QString brand, QString model, double price, bool rented)
    : id(id), brand(brand), model(model), pricePerDay(price), isRented(rented) {}

QString Vehicle::getId() const { return id; }
QString Vehicle::getBrand() const { return brand; }
QString Vehicle::getModel() const { return model; }
double Vehicle::getPricePerDay() const { return pricePerDay; }
bool Vehicle::getIsRented() const { return isRented; }

void Vehicle::setId(const QString& newId) { id = newId; }
void Vehicle::setBrand(const QString& newBrand) { brand = newBrand; }
void Vehicle::setModel(const QString& newModel) { model = newModel; }
void Vehicle::setPricePerDay(double newPrice) { pricePerDay = newPrice; }
void Vehicle::setIsRented(bool rented) { isRented = rented; }

QString Vehicle::toDisplayString() const {
    QString status = isRented ? "Rented" : "Available";
    return QString("ID: %1 | Brand: %2 | Model: %3 | Price/Day: R%4 | Status: %5")
        .arg(id, brand, model, QString::number(pricePerDay, 'f', 2), status);
}
