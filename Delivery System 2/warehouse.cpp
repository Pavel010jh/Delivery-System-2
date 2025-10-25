#include "warehouse.h"

// Конструктор
Warehouse::Warehouse(int id, const Address& address, const string& phoneNumber)
	: m_id(id), m_address(address), m_phoneNumber(phoneNumber) {
}

// Прием заказа на склад
void Warehouse::receiveOrder(Order* order) {
	m_storedOrders.push_back(order);
}