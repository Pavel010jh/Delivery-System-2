#pragma once
#include <string>
#include "address.h"
#include "parcel.h"

using namespace std;

class Courier;
class Tariff;

enum class OrderStatus {
	CREATED = 0,
	IN_PROGRESS = 1,
	DELIVERED = 2
};

class Order {
public:
	Order(const string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff);

	void updateStatus(OrderStatus newStatus);
	void assignCourier(Courier* courier);
	void calculateFinalCost();

	string getTrackingNumber() const { return m_trackingNumber; }
	OrderStatus getStatus() const { return m_status; }
	double getFinalCost() const { return m_finalCost; }
	Courier* getAssignedCourier() const { return m_assignedCourier; }

private:
	string m_trackingNumber;
	OrderStatus m_status;
	double m_finalCost;
	Address m_fromAddress;
	Address m_toAddress;
	Parcel m_parcel;
	Courier* m_assignedCourier;
	Tariff* m_chosenTariff;
};
