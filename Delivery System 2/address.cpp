#include "address.h"

// Конструктор
Address::Address(const string& street, const string& city, const string& postalCode)
	:m_street(street), m_city(city), m_postalCode(postalCode) {
}

// Полный адрес одной строкой
string Address::getFullAddress() const {
	return m_street + ", " + m_city + ", " + m_postalCode;
}

// Дружественная функция для вывода в поток
std::ostream& operator<<(std::ostream& os, const Address& address) {
    os << address.getFullAddress();
    return os;
}

// Перегрузка оператора сравнения ==
bool Address::operator==(const Address& other) const {
    return m_street == other.m_street &&
        m_city == other.m_city &&
        m_postalCode == other.m_postalCode;
}

// Перегрузка оператора сравнения !=
bool Address::operator!=(const Address& other) const {
    return !(*this == other);
}

// Перегрузка оператора сложения +
Address Address::operator+(const std::string& additionalInfo) const {
    return Address(m_street + " " + additionalInfo, m_city, m_postalCode);
}

// Перегрузка оператора +=
Address& Address::operator+=(const std::string& additionalInfo) {
    m_street += " " + additionalInfo;
    return *this;
}