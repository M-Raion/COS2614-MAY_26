#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
private:
    int numberOfDoors;
    int numberOfSeats;

public:
    Car(QString id, QString brand, QString model, double price, bool rented, int doors, int seats);
    
    int getDoors() const;
    int getSeats() const;

    QString typeName() const override;
    QString toDisplayString() const override;
    QString toFileString() const override;
};

#endif // CAR_H
