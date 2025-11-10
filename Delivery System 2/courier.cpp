#include "courier.h"

// Конструктор
Courier::Courier(int id, const std::string& name, const std::string& phoneNumber, const std::string& vehicleType, bool isAvailable)
	: m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_vehicleType(vehicleType), m_isAvailable(isAvailable) {
}

// Назначение заказа курьеру
bool Courier::assignOrder(std::shared_ptr<Order> order) {
	if (!m_isAvailable) return false;
	m_currentOrders.push_back(order);
	return true;
}