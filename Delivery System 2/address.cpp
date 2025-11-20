#include "address.h"
#include <algorithm>
#include <cctype>
#include <sstream>

// Êîíñòðóêòîð
Address::Address(const string& street, const string& city, const string& postalCode)
	:m_street(street), m_city(city), m_postalCode(postalCode) {
}

// Êîíñòðóêòîð êîïèðîâàíèÿ
Address::Address(const Address& other)
    : m_street(other.m_street), m_city(other.m_city), m_postalCode(other.m_postalCode) {
}

// Îïåðàòîð ïðèñâàèâàíèÿ
Address& Address::operator=(const Address& other) {
    if (this != &other) {
        m_street = other.m_street;
        m_city = other.m_city;
        m_postalCode = other.m_postalCode;
    }
    return *this;
}

// Ïîëíûé àäðåñ îäíîé ñòðîêîé
string Address::getFullAddress() const {
	return m_street + ", " + m_city + ", " + m_postalCode;
}

// Ïîèñê òåêñòà â àäðåñå
bool Address::contains(const std::string& searchText) const {
    std::string fullAddress = getFullAddress();
    return fullAddress.find(searchText) != std::string::npos;
}

// Àäðåñ â âåðõíåì ðåãèñòðå
std::string Address::toUpperCase() const {
    std::string result = getFullAddress();
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Èçâëå÷åíèå ðàéîíà èç íàçâàíèÿ óëèöû (ïðîñòàÿ èìèòàöèÿ)
std::string Address::getCityDistrict() const {
    if (m_street.find("Öåíòð") != std::string::npos) {
        return "Öåíòðàëüíûé ðàéîí";
    }
    else if (m_street.find("Ñåâåð") != std::string::npos) {
        return "Ñåâåðíûé ðàéîí";
    }
    else if (m_street.find("Þã") != std::string::npos) {
        return "Þæíûé ðàéîí";
    }
    else {
        return "Íåèçâåñòíûé ðàéîí";
    }
}

// Äðóæåñòâåííàÿ ôóíêöèÿ äëÿ âûâîäà â ïîòîê
std::ostream& operator<<(std::ostream& os, const Address& address) {
    os << address.getFullAddress();
    return os;
}

// Ïåðåãðóçêà îïåðàòîðà ñðàâíåíèÿ ==
bool Address::operator==(const Address& other) const {
    return m_street == other.m_street &&
        m_city == other.m_city &&
        m_postalCode == other.m_postalCode;
}

// Ïåðåãðóçêà îïåðàòîðà ñðàâíåíèÿ !=
bool Address::operator!=(const Address& other) const {
    return !(*this == other);
}

// Ïåðåãðóçêà îïåðàòîðà ñëîæåíèÿ +
Address Address::operator+(const std::string& additionalInfo) const {
    return Address(m_street + " " + additionalInfo, m_city, m_postalCode);
}

// Ïåðåãðóçêà îïåðàòîðà +=
Address& Address::operator+=(const std::string& additionalInfo) {
    m_street += " " + additionalInfo;
    return *this;
}