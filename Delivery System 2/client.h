#pragma once
#include <string>
#include <vector>
#include <memory>
#include "address.h"
using namespace std;

class Order;

class Client {
public:
	Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& email);

	Client(const Client& other);

	// Îïåðàòîð ïðèñâàèâàíèÿ
	Client& operator=(const Client& other);

	// Ìåòîäû äëÿ ðàáîòû ñî ñòðîêàìè
	std::string getFullInfo() const;
	bool hasEmailDomain(const std::string& domain) const;
	std::string getFormattedPhone() const;
	std::vector<std::string> getAddressLines() const;

	// Ìåòîäû
	void addAddress(const Address& newAddress);
	void addToHistory(std::shared_ptr<Order> order);

	// Ïåðåãðóçêà îïåðàòîðîâ
	bool operator==(const Client& other) const;
	bool operator!=(const Client& other) const;
	Client& operator+=(const Address& address);

	// Ãåòòåðû
	int getId() const { return m_id; }
	std::string getName() const { return m_name; }
	std::string getPhoneNumber() const { return m_phoneNumber; }
	std::string getEmail() const { return m_email; }

private:
	int m_id;
	std::string m_name;
	std::string m_phoneNumber;
	std::string m_email;
	std::vector<Address> m_addresses;
	std::vector<std::shared_ptr<Order>> m_orderHistory;
};
