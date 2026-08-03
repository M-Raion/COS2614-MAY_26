#include "Car.h"

Car::Car(QString id, QString brand, QString model, double price, bool rented, int doors, int seats)
    : Vehicle(id, brand, model, price, rented), numberOfDoors(doors), numberOfSeats(seats) {}

int Car::getDoors() const { return numberOfDoors; }
int Car::getSeats() const { return numberOfSeats; }

QString Car::typeName() const {
    return "Car";
}

QString Car::toDisplayString() const {
    return "[Car] " + Vehicle::toDisplayString() + 
           QString(" | Doors: %1 | Seats: %2").arg(numberOfDoors).arg(numberOfSeats);
}

QString Car::toFileString() const {
    return QString("Car|%1|%2|%3|%4|%5|%6|%7")
        .arg(getId(), getBrand(), getModel(), QString::number(getPricePerDay()),
             QString::number(getIsRented()), QString::number(numberOfDoors), QString::number(numberOfSeats));
}
