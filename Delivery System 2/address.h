#pragma once
#include <string>
using namespace std;

class Address {
public:

	// Конструкторы
	Address() = default;
	Address(const string& street, const string& city, const string& postalCode);
	
	// Методы
	string getFullAddress() const;

	// Геттеры
	string getStreet() const { return m_street; }
	string getCity() const { return m_city; }
	string getPostalCode() const { return m_postalCode; }

	friend std::ostream& operator<<(std::ostream& os, const Address& address);

	bool operator==(const Address& other) const;
	bool operator!=(const Address& other) const;
	Address operator+(const std::string& additionalInfo) const;
	Address& operator+=(const std::string& additionalInfo);

private:
	string m_street;
	string m_city;
	string m_postalCode;
};
