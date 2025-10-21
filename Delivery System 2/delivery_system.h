#pragma once
#include <vector>
#include "order.h"
#include "client.h"
#include "courier.h"
#include"warehouse.h"
#include "tariff.h"

using namespace std;

class DeliverySystem {
public:
	DeliverySystem();
	~DeliverySystem();

	Order* createOrder(Client* sender, Client* receiver, const Address& from, const Address& to, const Parcel& parcel, Tariff* tariff);

	vector<Order*> findOrdersByStatus(OrderStatus status) const;

	void addClient(Client* client);
	void addCourier(Courier* courier);
	void addTariff(Tariff* tariff);

	vector<Order*> getAllOrders() const { return m_allOrders; }

private:
	vector<Order*> m_allOrders;
	vector<Courier*> m_allCouriers;
	vector<Client*> m_allClients;
	vector<Warehouse*> m_allWarehouses;
	vector<Tariff*> m_availableTariffs;
	static int m_orderCounter;
};