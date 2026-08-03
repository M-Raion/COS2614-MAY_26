#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
private:
    int engineCapacityCC;

public:
    Motorcycle(QString id, QString brand, QString model, double price, bool rented, int engineCC);
    
    int getEngineCapacity() const;

    QString typeName() const override;
    QString toDisplayString() const override;
    QString toFileString() const override;
};

#endif // MOTORCYCLE_H
