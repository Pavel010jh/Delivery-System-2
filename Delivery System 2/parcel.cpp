#include "parcel.h"
#include <sstream>
#include <algorithm>

// Конструктор
Parcel::Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue)
	: m_description(description), m_weight(weight), m_lenght(lenght), m_width(width), m_height(height), m_estimatedValue(estimatedValue) {
}

// Конструктор копирования
Parcel::Parcel(const Parcel& other)
    : m_description(other.m_description), m_weight(other.m_weight),
    m_lenght(other.m_lenght), m_width(other.m_width),
    m_height(other.m_height), m_estimatedValue(other.m_estimatedValue) {
}

// Оператор присваивания
Parcel& Parcel::operator=(const Parcel& other) {
    if (this != &other) {
        m_description = other.m_description;
        m_weight = other.m_weight;
        m_lenght = other.m_lenght;
        m_width = other.m_width;
        m_height = other.m_height;
        m_estimatedValue = other.m_estimatedValue;
    }
    return *this;
}

// Полное описание посылки
std::string Parcel::getFullDescription() const {
    std::stringstream ss;
    ss << m_description << " | Вес: " << m_weight << " кг | "
        << "Объем: " << calculateVolume() << " см^3 | "
        << "Стоимость: " << m_estimatedValue << " руб.";
    return ss.str();
}

// Категория размера
std::string Parcel::getSizeCategory() const {
    double volume = calculateVolume();
    if (volume < 1000) return "Маленькая";
    else if (volume < 5000) return "Средняя";
    else return "Большая";
}

// Поиск ключевого слова в описании
bool Parcel::descriptionContains(const std::string& keyword) const {
    std::string descLower = m_description;
    std::transform(descLower.begin(), descLower.end(), descLower.begin(), ::tolower);

    std::string keywordLower = keyword;
    std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

    return descLower.find(keywordLower) != std::string::npos;
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