#pragma once
#include <string>
using namespace std;

class Address {
public:

	// Êîíñòðóêòîðû
	Address() = default;
	Address(const string& street, const string& city, const string& postalCode);
	
	// Êîíñòðóêòîð êîïèðîâàíèÿ
	Address(const Address& other);

	// Îïåðàòîð ïðèñâàèâàíèÿ
	Address& operator=(const Address& other);

	// Ìåòîäû äëÿ ðàáîòû ñî ñòðîêàìè
	std::string getFullAddress() const;
	bool contains(const std::string& searchText) const;
	std::string toUpperCase() const;
	std::string getCityDistrict() const;

	// Ãåòòåðû
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
