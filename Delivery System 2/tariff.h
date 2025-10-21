#pragma once
#include <string>
using namespace std;

class Parcel;
class Address;

class Tariff {
public:
	Tariff(const string& name, double basePrice);

	virtual double calculateCost(const Parcel& parcel, const Address& from, const Address& to) = 0;

	string getName() const { return m_name; }
	double getBasePrice() const { return m_basePrice; }

protected:
	string m_name;
	double m_basePrice;
};

class ExpressTariff : public Tariff {
public:
	ExpressTariff(const string& name, double basePrice);
	double calculateCost(const Parcel& parcel, const Address& from, const Address& to) override;
};

class EconomyTariff : public Tariff {
public:
	EconomyTariff(const string& name, double basePrice);
	double calculateCost(const Parcel& parcel, const Address& from, const Address& to) override;
};