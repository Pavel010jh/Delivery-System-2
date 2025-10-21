#include "parcel.h"

Parcel::Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue)
	: m_description(description), m_weight(weight), m_lenght(lenght), m_width(width), m_height(height), m_estimatedValue(estimatedValue) {
}

double Parcel::calculateVolume() const {
	return m_lenght * m_width * m_height;
}