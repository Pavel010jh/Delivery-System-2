#include "client.h"

// Конструктор
Client::Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& email)
	: m_id(m_id), m_name(name), m_phoneNumber(phoneNumber), m_email(m_email) {
}

// Конструктор копирования (базовый)
Client::Client(const Client& other)
	: m_id(other.m_id), m_name(other.m_name),
	m_phoneNumber(other.m_phoneNumber), m_email(other.m_email),
	m_addresses(other.m_addresses) {
}

// Добавление адреса клиенту
void Client::addAddress(const Address& newAddress) {
	m_addresses.push_back(newAddress);
}

// Добавление заказа в историю
void Client::addToHistory(std::shared_ptr<Order> order) {
	m_orderHistory.push_back(order);
}

// Перегрузка оператора сравнения ==
bool Client::operator==(const Client& other) const {
	return m_id == other.m_id && m_email == other.m_email;
}

// Перегрузка оператора сравнения !=
bool Client::operator!=(const Client& other) const {
	return !(*this == other);
}

// Перегрузка оператора +=
Client& Client::operator+=(const Address& address) {
	addAddress(address);
	return *this;
}