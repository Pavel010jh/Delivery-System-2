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

	// Методы
	void addAddress(const Address& newAddress);
	void addToHistory(std::shared_ptr<Order> order);

	// Геттеры
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
