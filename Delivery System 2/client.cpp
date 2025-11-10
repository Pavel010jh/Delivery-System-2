#include "client.h"

// Конструктор
Client::Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& email)
	: m_id(m_id), m_name(name), m_phoneNumber(phoneNumber), m_email(m_email) {
}

// Добавление адреса клиенту
void Client::addAddress(const Address& newAddress) {
	m_addresses.push_back(newAddress);
}

// Добавление заказа в историю
void Client::addToHistory(std::shared_ptr<Order> order) {
	m_orderHistory.push_back(order);
}