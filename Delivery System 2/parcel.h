#pragma once
#include <string>
using namespace std;

class Parcel {
public:
	Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue);

	double calculateVolume() const;

	string getDescription() const { return m_description; }
	double getWeight() const { return m_weight; }
	double getLenght() const { return m_lenght; }
	double getWidth() const { return m_width; }
	double getHeight() const { return m_height; }
	double getEstimatedValue() const { return m_estimatedValue; }

private:
	string m_description;
	double m_weight;
	double m_lenght;
	double m_width;
	double m_height;
	double m_estimatedValue;
};