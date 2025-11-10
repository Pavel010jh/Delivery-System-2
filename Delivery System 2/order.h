#pragma once
#include <string>
#include <memory>
#include "address.h"
#include "parcel.h"

using namespace std;

class Courier;
class Tariff;

// Статусы заказа
enum class OrderStatus {
	CREATED = 0,
	IN_PROGRESS = 1,
	DELIVERED = 2
};

class Order {
public:
	Order(const std::string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff);

	// Методы
	void updateStatus(OrderStatus newStatus);
	void assignCourier(std::shared_ptr<Courier> courier);
	void calculateFinalCost();

	// Геттеры
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
};
