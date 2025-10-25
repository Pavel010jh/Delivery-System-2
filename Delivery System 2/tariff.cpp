#include "tariff.h"
#include "parcel.h"
#include "address.h"

// Ѕазовый тариф
Tariff::Tariff(const string& name, double basePrice)
	: m_name(name), m_basePrice(basePrice) {
}

// Ёкспресс тариф - дороже но быстрее
ExpressTariff::ExpressTariff(const string& name, double basePrice)
	: Tariff(name, basePrice) {
}

double ExpressTariff::calculateCost(const Parcel& parcel, const Address& from, const Address& to) {
	return m_basePrice + parcel.calculateVolume() * VOLUME_RATE + parcel.getWeight() * WEIGHT_RATE;
}

// Ёконом тариф - дешевле но медленнее
EconomyTariff::EconomyTariff(const string& name, double basePrice)
	: Tariff(name, basePrice) {
}

double EconomyTariff::calculateCost(const Parcel& parcel, const Address& from, const Address& to) {
	return m_basePrice + parcel.calculateVolume() * VOLUME_RATE + parcel.getWeight() * WEIGHT_RATE;
}