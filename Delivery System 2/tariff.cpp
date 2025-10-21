#include "tariff.h"
#include "parcel.h"
#include "address.h"

Tariff::Tariff(const string& name, double basePrice)
	: m_name(name), m_basePrice(basePrice) {
}

ExpressTariff::ExpressTariff(const string& name, double basePrice)
	: Tariff(name, basePrice) {
}

double ExpressTariff::calculateCost(const Parcel& parcel, const Address& from, const Address& to) {
	return m_basePrice + parcel.calculateVolume() * 0.1 + parcel.getWeight() * 50;
}

EconomyTariff::EconomyTariff(const string& name, double basePrice)
	: Tariff(name, basePrice) {
}

double EconomyTariff::calculateCost(const Parcel& parcel, const Address& from, const Address& to) {
	return m_basePrice + parcel.calculateVolume() * 0.05 + parcel.getWeight() * 30;
}