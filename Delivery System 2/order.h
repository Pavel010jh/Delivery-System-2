#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "address.h"
#include "parcel.h"

using namespace std;

class Courier;
class Tariff;

// Ñòàòóñû çàêàçà
enum class OrderStatus {
	CREATED = 0,
	IN_PROGRESS = 1,
	DELIVERED = 2
};

class Order {
public:
	Order(const std::string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff);

	// Êîíñòðóêòîð êîïèðîâàíèÿ
	Order(const Order& other);

	// Îïåðàòîð ïðèñâàèâàíèÿ
	Order& operator=(const Order& other);

	// Ìåòîäû äëÿ ðàáîòû ñî ñòðîêàìè
	std::string getStatusString() const;
	bool trackingNumberStartsWith(const std::string& prefix) const;

	// Ìåòîäû ñ îáðàáîòêîé èñêëþ÷åíèé
	void updateStatus(OrderStatus newStatus);
	void assignCourier(std::shared_ptr<Courier> courier);
	void calculateFinalCost();
	void validateOrder() const;

	// Ñòàòè÷åñêèå ìåòîäû è ïîëÿ
	static int getTotalOrdersCreated() { return s_totalOrdersCreated; }
	static double getTotalRevenue() { return s_totalRevenue; }
	static void resetStatistics();

	// Èñïîëüçîâàíèå this
	Order* getThisPointer() { return this; }
	const Order* getThisPointer() const { return this; }
	void printOrderInfo() const;

	// Ïåðåãðóçêà îïåðàòîðîâ
	bool operator<(const Order& other) const;
	bool operator>(const Order& other) const;
	Order& operator++();    // Ïðåôèêñíûé èíêðåìåíò
	Order operator++(int);  // Ïîñòôèêñíûé èíêðåìåíò

	// Ãåòòåðû
	std::string getTrackingNumber() const { return m_trackingNumber; }
	OrderStatus getStatus() const { return m_status; }
	double getFinalCost() const { return m_finalCost; }
	std::shared_ptr<Courier> getAssignedCourier() const { return m_assignedCourier; }

private:
	std::string m_trackingNumber;
	OrderStatus m_status;
	double m_finalCost;
	Address m_fromAddress;
	Address m_toAddress;
	Parcel m_parcel;
	std::shared_ptr<Courier> m_assignedCourier;
	Tariff* m_chosenTariff;
	// Ñòàòè÷åñêèå ïîëÿ
	static int s_totalOrdersCreated;
	static double s_totalRevenue;
};

// Ïîëüçîâàòåëüñêèå èñêëþ÷åíèÿ äëÿ Order
class InvalidOrderException : public std::runtime_error {
public:
	InvalidOrderException(const std::string& message) : std::runtime_error(message) {}
};

class OrderStatusException : public std::runtime_error {
public:
	OrderStatusException(const std::string& message) : std::runtime_error(message) {}
};
