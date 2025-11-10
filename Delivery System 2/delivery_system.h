#pragma once
#include <vector>
#include <memory>
#include "order.h"
#include "client.h"
#include "courier.h"
#include"warehouse.h"
#include "tariff.h"

using namespace std;

class DeliverySystem {
public:
	// Конструктор и деструктор
	DeliverySystem();
	~DeliverySystem();

	// Основные методы
	std::shared_ptr<Order> createOrder(std::shared_ptr<Client> sender, std::shared_ptr<Client> receiver, const Address& from, const Address& to, const Parcel& parcel, std::shared_ptr<Tariff> tariff);

	std::vector < std::shared_ptr<Order>> findOrdersByStatus(OrderStatus status) const;

	// Методы добавления сущностей
	void addClient(std::shared_ptr<Client> client);
	void addCourier(std::shared_ptr<Courier> courier);
	void addTariff(std::shared_ptr<Tariff> tariff);

	// Геттеры
	std::vector<std::shared_ptr<Order>> getAllOrders() const { return m_allOrders; }

private:
	std::vector<std::shared_ptr<Order>> m_allOrders;
	std::vector<std::shared_ptr<Courier>> m_allCouriers;
	std::vector<std::shared_ptr<Client>> m_allClients;
	std::vector<std::shared_ptr<Warehouse>> m_allWarehouses;
	std::vector<std::shared_ptr<Tariff>> m_availableTariffs;
	static int m_orderCounter;
};