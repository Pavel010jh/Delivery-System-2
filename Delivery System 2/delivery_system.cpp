#include "delivery_system.h"

// Инициализация статической переменной
int DeliverySystem::m_orderCounter = 0;

// Конструктор
DeliverySystem::DeliverySystem() {}

// Деструктор
DeliverySystem::~DeliverySystem() {
	for (auto order : m_allOrders) delete order;
	for (auto client : m_allClients) delete client;
	for (auto courier : m_allCouriers) delete courier;
	for (auto warehouse : m_allWarehouses) delete warehouse;
	for (auto tariff : m_availableTariffs) delete tariff;
}

// Создание нового заказа
Order* DeliverySystem::createOrder(Client* sender, Client* receiver, const Address& from, const Address& to, const Parcel& parcel, Tariff* tariff)
{
	string trackingNumber = "TRK" + to_string(++m_orderCounter);
	Order* newOrder = new Order(trackingNumber, from, to, parcel, tariff);

	m_allOrders.push_back(newOrder);
	if (sender) sender->addToHistory(newOrder);

	return newOrder;
}

// Поиск заказов по статусу
vector<Order*> DeliverySystem::findOrdersByStatus(OrderStatus status) const {
	vector<Order*> result;
	for (auto order : m_allOrders) {
		if (order->getStatus() == status) {
			result.push_back(order);
		}
	}
	return result;
}

// Добавление клиента в систему
void DeliverySystem::addClient(Client* client) {
	m_allClients.push_back(client);
}

// Добавление курьера в систему
void DeliverySystem::addCourier(Courier* courier) {
	m_allCouriers.push_back(courier);
}

// Добавление тарифа в систему
void DeliverySystem::addTariff(Tariff* tariff) {
	m_availableTariffs.push_back(tariff);
}