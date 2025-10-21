#pragma once
#include <string>
#include <vector>
#include "address.h"

using namespace std;

class Order;

class Warehouse {
public:
	Warehouse(int id, const Address& address, const string& phoneNumber);

	void receiveOrder(Order* order);

	int getId() const { return m_id; }
	Address getAddress() const { return m_address; }
	string getPhoneNumber() const { return m_phoneNumber; }

private:
	int m_id;
	Address m_address;
	string m_phoneNumber;
	vector<Order*> m_storedOrders;
};