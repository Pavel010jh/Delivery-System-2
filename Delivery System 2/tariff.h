#pragma once
#include <string>
using namespace std;

class Parcel;
class Address;

class Tariff {
public:
	Tariff(const string& name, double basePrice);

	// Абстрактный метод расчета стоимости
	virtual double calculateCost(const Parcel& parcel, const Address& from, const Address& to) = 0;

	// Геттеры
	string getName() const { return m_name; }
	double getBasePrice() const { return m_basePrice; }

protected:
	string m_name;
	double m_basePrice;
};

// Экспресс тариф (наследник)
class ExpressTariff : public Tariff {
public:
	ExpressTariff(const string& name, double basePrice);
	double calculateCost(const Parcel& parcel, const Address& from, const Address& to) override;

private:
	static constexpr double VOLUME_RATE = 0.1;
	static constexpr double WEIGHT_RATE = 50.0;
};

// Эконом тариф (наследник)
class EconomyTariff : public Tariff {
public:
	EconomyTariff(const string& name, double basePrice);
	double calculateCost(const Parcel& parcel, const Address& from, const Address& to) override;

private:
	static constexpr double VOLUME_RATE = 0.05;
	static constexpr double WEIGHT_RATE = 30.0;
};