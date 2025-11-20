#include "client.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Êîíñòðóêòîð
Client::Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& email)
	: m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_email(email) {
}

// Êîíñòðóêòîð êîïèðîâàíèÿ (áàçîâûé)
Client::Client(const Client& other)
	: m_id(other.m_id), m_name(other.m_name),
	m_phoneNumber(other.m_phoneNumber), m_email(other.m_email),
	m_addresses(other.m_addresses) {
}

// Îïåðàòîð ïðèñâàèâàíèÿ
Client& Client::operator=(const Client& other) {
	if (this != &other) {
		m_id = other.m_id;
		m_name = other.m_name;
		m_phoneNumber = other.m_phoneNumber;
		m_email = other.m_email;
		m_addresses = other.m_addresses;
	}
	return *this;
}

// Ïîëíàÿ èíôîðìàöèÿ î êëèåíòå
std::string Client::getFullInfo() const {
    std::stringstream ss;
    ss << "ID: " << m_id << ", Èìÿ: " << m_name
        << ", Òåëåôîí: " << getFormattedPhone()
        << ", Email: " << m_email;
    return ss.str();
}

// Ïðîâåðêà äîìåíà email
bool Client::hasEmailDomain(const std::string& domain) const {
    size_t pos = m_email.find('@');
    if (pos == std::string::npos) return false;

    std::string emailDomain = m_email.substr(pos + 1);
    return emailDomain.find(domain) != std::string::npos;
}

// Ôîðìàòèðîâàííûé íîìåð òåëåôîíà
std::string Client::getFormattedPhone() const {
    if (m_phoneNumber.empty()) return "";

    std::string formatted = m_phoneNumber;
    // Ïðîñòîå ôîðìàòèðîâàíèå: +7 (916) 111-22-33
    if (formatted.length() == 11 && formatted[0] == '8') {
        formatted = "+7" + formatted.substr(1);
    }
    return formatted;
}

// Ïîëó÷åíèå àäðåñîâ â âèäå ñòðîê
std::vector<std::string> Client::getAddressLines() const {
    std::vector<std::string> lines;
    for (const auto& address : m_addresses) {
        lines.push_back(address.getFullAddress());
    }
    return lines;
}

// Äîáàâëåíèå àäðåñà êëèåíòó
void Client::addAddress(const Address& newAddress) {
	m_addresses.push_back(newAddress);
}

// Äîáàâëåíèå çàêàçà â èñòîðèþ
void Client::addToHistory(std::shared_ptr<Order> order) {
	m_orderHistory.push_back(order);
}

// Ïåðåãðóçêà îïåðàòîðà ñðàâíåíèÿ ==
bool Client::operator==(const Client& other) const {
	return m_id == other.m_id && m_email == other.m_email;
}

// Ïåðåãðóçêà îïåðàòîðà ñðàâíåíèÿ !=
bool Client::operator!=(const Client& other) const {
	return !(*this == other);
}

// Ïåðåãðóçêà îïåðàòîðà +=
Client& Client::operator+=(const Address& address) {
	addAddress(address);
	return *this;
}