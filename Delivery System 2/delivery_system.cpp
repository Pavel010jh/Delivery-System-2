#include "delivery_system.h"

// Инициализация статической переменной
int DeliverySystem::m_orderCounter = 0;

// Конструктор
DeliverySystem::DeliverySystem() {}

// Деструктор
DeliverySystem::~DeliverySystem() {
}

// Создание нового заказа
std::shared_ptr<Order> DeliverySystem::createOrder(std::shared_ptr<Client> sender, std::shared_ptr<Client> receiver, const Address& from, const Address& to, const Parcel& parcel, std::shared_ptr<Tariff> tariff)
{
	std::string trackingNumber = "TRK" + std::to_string(++m_orderCounter);
	auto newOrder = std::make_shared<Order>(trackingNumber, from, to, parcel, tariff.get());

	m_allOrders.push_back(newOrder);
	if (sender) sender->addToHistory(newOrder);

	return newOrder;
}

// Поиск заказов по статусу
std::vector<std::shared_ptr<Order>> DeliverySystem::findOrdersByStatus(OrderStatus status) const {
	std::vector<std::shared_ptr<Order>> result;
	for (auto order : m_allOrders) {
		if (order->getStatus() == status) {
			result.push_back(order);
		}
	}
	return result;
}

// Добавление клиента в систему
void DeliverySystem::addClient(std::shared_ptr<Client> client) {
	m_allClients.push_back(client);
}

// Добавление курьера в систему
void DeliverySystem::addCourier(std::shared_ptr<Courier> courier) {
	m_allCouriers.push_back(courier);
}

// Добавление тарифа в систему
void DeliverySystem::addTariff(std::shared_ptr<Tariff> tariff) {
	m_availableTariffs.push_back(tariff);
}