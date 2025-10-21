#include "address.h"

Address::Address(const string& street, const string& city, const string& postalCode)
	:m_street(street), m_city(city), m_postalCode(postalCode) {
}

string Address::getFullAddress() const {
	return m_street + ", " + m_city + ", " + m_postalCode;
}