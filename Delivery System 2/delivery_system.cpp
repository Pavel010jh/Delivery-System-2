#include "delivery_system.h"

int DeliverySystem::m_orderCounter = 0;

DeliverySystem::DeliverySystem() {}

DeliverySystem::~DeliverySystem() {
	for (auto order : m_allOrders) delete order;
	for (auto client : m_allClients) delete client;
	for (auto courier : m_allCouriers) delete courier;
	for (auto warehouse : m_allWarehouses) delete warehouse;
	for (auto tariff : m_availableTariffs) delete tariff;
}

Order* DeliverySystem::createOrder(Client* sender, Client* receiver, const Address& from, const Address& to, const Parcel& parcel, Tariff* tariff)
{
	string trackingNumber = "TRK" + to_string(++m_orderCounter);
	Order* newOrder = new Order(trackingNumber, from, to, parcel, tariff);

	m_allOrders.push_back(newOrder);
	if (sender) sender->addToHistory(newOrder);

	return newOrder;
}

vector<Order*> DeliverySystem::findOrdersByStatus(OrderStatus status) const {
	vector<Order*> result;
	for (auto order : m_allOrders) {
		if (order->getStatus() == status) {
			result.push_back(order);
		}
	}
	return result;
}

void DeliverySystem::addClient(Client* client) {
	m_allClients.push_back(client);
}

void DeliverySystem::addCourier(Courier* courier) {
	m_allCouriers.push_back(courier);
}

void DeliverySystem::addTariff(Tariff* tariff) {
	m_availableTariffs.push_back(tariff);
}