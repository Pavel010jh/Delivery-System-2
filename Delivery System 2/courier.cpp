#include "courier.h"

// Конструктор
Courier::Courier(int id, const string& name, const string& phoneNumber, const string& vehicleType, bool isAvailable)
	: m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_vehicleType(vehicleType), m_isAvailable(isAvailable) {
}

// Назначение заказа курьеру
bool Courier::assignOrder(Order* order) {
	if (!m_isAvailable) return false;
	m_currentOrders.push_back(order);
	return true;
}