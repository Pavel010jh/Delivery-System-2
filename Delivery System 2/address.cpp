#include "address.h"
#include <algorithm>
#include <cctype>
#include <sstream>

// Конструктор
Address::Address(const string& street, const string& city, const string& postalCode)
	:m_street(street), m_city(city), m_postalCode(postalCode) {
}

// Конструктор копирования
Address::Address(const Address& other)
    : m_street(other.m_street), m_city(other.m_city), m_postalCode(other.m_postalCode) {
}

// Оператор присваивания
Address& Address::operator=(const Address& other) {
    if (this != &other) {
        m_street = other.m_street;
        m_city = other.m_city;
        m_postalCode = other.m_postalCode;
    }
    return *this;
}

// Полный адрес одной строкой
string Address::getFullAddress() const {
	return m_street + ", " + m_city + ", " + m_postalCode;
}

// Поиск текста в адресе
bool Address::contains(const std::string& searchText) const {
    std::string fullAddress = getFullAddress();
    return fullAddress.find(searchText) != std::string::npos;
}

// Адрес в верхнем регистре
std::string Address::toUpperCase() const {
    std::string result = getFullAddress();
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Извлечение района из названия улицы (простая имитация)
std::string Address::getCityDistrict() const {
    if (m_street.find("Центр") != std::string::npos) {
        return "Центральный район";
    }
    else if (m_street.find("Север") != std::string::npos) {
        return "Северный район";
    }
    else if (m_street.find("Юг") != std::string::npos) {
        return "Южный район";
    }
    else {
        return "Неизвестный район";
    }
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