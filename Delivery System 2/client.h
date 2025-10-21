#pragma once
#include <string>
#include <vector>
#include "address.h"
using namespace std;

class Order;

class Client {
public:
	Client(int id, const string& name, const string& phoneNumber, const string& email);

	void addAddress(const Address& newAddress);
	void addToHistory(Order* order);

	int getId() const { return m_id; }
	string getName() const { return m_name; }
	string getPhoneNumber() const { return m_phoneNumber; }
	string getEmail() const { return m_email; }

private:
	int m_id;
	string m_name;
	string m_phoneNumber;
	string m_email;
	vector<Address> m_addresses;
	vector<Order*> m_orderHistory;
};
