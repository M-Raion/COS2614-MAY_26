#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>
#include <QStringList>

class Vehicle {
private:
    QString id;
    QString brand;
    QString model;
    double pricePerDay;
    bool isRented;

public:
    Vehicle(QString id, QString brand, QString model, double price, bool rented = false);
    virtual ~Vehicle() = default;

    // Getters
    QString getId() const;
    QString getBrand() const;
    QString getModel() const;
    double getPricePerDay() const;
    bool getIsRented() const;

    // Setters
    void setId(const QString& newId);
    void setBrand(const QString& newBrand);
    void setModel(const QString& newModel);
    void setPricePerDay(double newPrice);
    void setIsRented(bool rented);

    // Pure virtual function
    virtual QString typeName() const = 0;

    // Virtual display and file formatting functions
    virtual QString toDisplayString() const;
    virtual QString toFileString() const = 0;
};

#endif // VEHICLE_H
