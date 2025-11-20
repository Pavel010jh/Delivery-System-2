ï»¿#include "parcel.h"
#include <sstream>
#include <algorithm>

// ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ
Parcel::Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue)
	: m_description(description), m_weight(weight), m_lenght(lenght), m_width(width), m_height(height), m_estimatedValue(estimatedValue) {
}

// ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ ÐºÐ¾Ð¿Ð¸ÑÐ¾Ð²Ð°Ð½Ð¸Ñ
Parcel::Parcel(const Parcel& other)
    : m_description(other.m_description), m_weight(other.m_weight),
    m_lenght(other.m_lenght), m_width(other.m_width),
    m_height(other.m_height), m_estimatedValue(other.m_estimatedValue) {
}

// ÐÐ¿ÐµÑÐ°ÑÐ¾Ñ Ð¿ÑÐ¸ÑÐ²Ð°Ð¸Ð²Ð°Ð½Ð¸Ñ
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

// ÐÐ¾Ð»Ð½Ð¾Ðµ Ð¾Ð¿Ð¸ÑÐ°Ð½Ð¸Ðµ Ð¿Ð¾ÑÑÐ»ÐºÐ¸
std::string Parcel::getFullDescription() const {
    std::stringstream ss;
    ss << m_description << " | ÐÐµÑ: " << m_weight << " ÐºÐ³ | "
        << "ÐÐ±ÑÐµÐ¼: " << calculateVolume() << " ÑÐ¼^3 | "
        << "Ð¡ÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ: " << m_estimatedValue << " ÑÑÐ±.";
    return ss.str();
}

// ÐÐ°ÑÐµÐ³Ð¾ÑÐ¸Ñ ÑÐ°Ð·Ð¼ÐµÑÐ°
std::string Parcel::getSizeCategory() const {
    double volume = calculateVolume();
    if (volume < 1000) return "ÐÐ°Ð»ÐµÐ½ÑÐºÐ°Ñ";
    else if (volume < 5000) return "Ð¡ÑÐµÐ´Ð½ÑÑ";
    else return "ÐÐ¾Ð»ÑÑÐ°Ñ";
}

// ÐÐ¾Ð¸ÑÐº ÐºÐ»ÑÑÐµÐ²Ð¾Ð³Ð¾ ÑÐ»Ð¾Ð²Ð° Ð² Ð¾Ð¿Ð¸ÑÐ°Ð½Ð¸Ð¸
bool Parcel::descriptionContains(const std::string& keyword) const {
    std::string descLower = m_description;
    std::transform(descLower.begin(), descLower.end(), descLower.begin(), ::tolower);

    std::string keywordLower = keyword;
    std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

    return descLower.find(keywordLower) != std::string::npos;
}


// Ð Ð°ÑÑÐµÑ Ð¾Ð±ÑÐµÐ¼Ð° Ð¿Ð¾ÑÑÐ»ÐºÐ¸
double Parcel::calculateVolume() const {
	return m_lenght * m_width * m_height;
}

// ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ° ==
bool Parcel::operator==(const Parcel& other) const {
    return m_description == other.m_description &&
        m_weight == other.m_weight &&
        m_lenght == other.m_lenght &&
        m_width == other.m_width &&
        m_height == other.m_height;
}

// ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ° + (Ð¾Ð±ÑÐµÐ´Ð¸Ð½ÐµÐ½Ð¸Ðµ Ð¿Ð¾ÑÑÐ»Ð¾Ðº)
Parcel Parcel::operator+(const Parcel& other) const {
    std::string newDescription = m_description + " + " + other.m_description;
    double newWeight = m_weight + other.m_weight;
    double newLength = std::max(m_lenght, other.m_lenght);
    double newWidth = std::max(m_width, other.m_width);
    double newHeight = m_height + other.m_height;
    double newValue = m_estimatedValue + other.m_estimatedValue;

    return Parcel(newDescription, newWeight, newLength, newWidth, newHeight, newValue);
}