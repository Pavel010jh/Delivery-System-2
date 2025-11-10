#pragma once
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Order;

class Courier {
public:
	Courier(int id, const std::string& name, const std::string& phoneNumber, const std::string& vehicleType, bool isAvailable);

	// Методы
	bool assignOrder(std::shared_ptr<Order> order);

	// Геттеры
	int getId() const { return m_id; }
	std::string getName() const { return m_name; }
	std::string getPhoneNumber() const { return m_phoneNumber; }
	std::string getVehicleType() const { return m_vehicleType; }
	bool getIsAvailable() const { return m_isAvailable; }

private:
	int m_id;
	string m_name;
	string m_phoneNumber;
	string m_vehicleType;
	bool m_isAvailable;
	std::vector<std::shared_ptr<Order>> m_currentOrders;
};
