#pragma once
#include <string>
using namespace std;

class Parcel {
public:
	// Êîíñòðóêòîðû
	Parcel(const string& description, double weight, double lenght, double width, double height, double estimatedValue);
	
	// Êîíñòðóêòîð êîïèðîâàíèÿ
	Parcel(const Parcel& other);

	// Îïåðàòîð ïðèñâàèâàíèÿ
	Parcel& operator=(const Parcel& other);

	// Ìåòîäû äëÿ ðàáîòû ñî ñòðîêàìè
	std::string getFullDescription() const;
	std::string getSizeCategory() const;
	bool descriptionContains(const std::string& keyword) const;

	// Ìåòîäû
	double calculateVolume() const;

	// Ïåðåãðóçêà îïåðàòîðîâ
	bool operator==(const Parcel& other) const;
	Parcel operator+(const Parcel& other) const; // Îáúåäèíåíèå ïîñûëîê

	// Ãåòòåðû
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