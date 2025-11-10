#include "parcel.h"

// Конструктор
Parcel::Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue)
	: m_description(description), m_weight(weight), m_lenght(lenght), m_width(width), m_height(height), m_estimatedValue(estimatedValue) {
}

// Расчет объема посылки
double Parcel::calculateVolume() const {
	return m_lenght * m_width * m_height;
}

// Перегрузка оператора ==
bool Parcel::operator==(const Parcel& other) const {
    return m_description == other.m_description &&
        m_weight == other.m_weight &&
        m_lenght == other.m_lenght &&
        m_width == other.m_width &&
        m_height == other.m_height;
}

// Перегрузка оператора + (объединение посылок)
Parcel Parcel::operator+(const Parcel& other) const {
    std::string newDescription = m_description + " + " + other.m_description;
    double newWeight = m_weight + other.m_weight;
    double newLength = std::max(m_lenght, other.m_lenght);
    double newWidth = std::max(m_width, other.m_width);
    double newHeight = m_height + other.m_height;
    double newValue = m_estimatedValue + other.m_estimatedValue;

    return Parcel(newDescription, newWeight, newLength, newWidth, newHeight, newValue);
}