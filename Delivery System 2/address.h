#pragma once
#include <string>
using namespace std;

class Address {
public:

	Address() = default;
	Address(const string& street, const string& city, const string& postalCode);

	string getFullAddress() const;

	string getStreet() const { return m_street; }
	string getCity() const { return m_city; }
	string getPostalCode() const { return m_postalCode; }
private:
	string m_street;
	string m_city;
	string m_postalCode;
};
