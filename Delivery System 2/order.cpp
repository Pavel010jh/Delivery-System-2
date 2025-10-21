#include "order.h"
#include "courier.h"
#include "tariff.h"

Order::Order(const string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff)
	: m_trackingNumber(trackingNumber), m_status(OrderStatus::CREATED),
	m_finalCost(0.0), m_fromAddress(fromAddress), m_toAddress(toAddress),
	m_parcel(parcel), m_assignedCourier(nullptr), m_chosenTariff(tariff)
{
	calculateFinalCost();
}

void Order::updateStatus(OrderStatus newStatus) {
	m_status = newStatus;
}

void Order::assignCourier(Courier* courier) {
	if (courier && courier->assignOrder(this)) {
		m_assignedCourier = courier;
		updateStatus(OrderStatus::IN_PROGRESS);
	}
}

void Order::calculateFinalCost() {
	if (m_chosenTariff) {
		m_finalCost = m_chosenTariff->calculateCost(m_parcel, m_fromAddress, m_toAddress);
	}
}