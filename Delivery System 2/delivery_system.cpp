#include "delivery_system.h"
#include <iostream>
#include <algorithm>

// Инициализация статических переменных
int DeliverySystem::s_globalOrderCount = 0;
const std::string DeliverySystem::s_systemVersion = "2.1.0";

// Инициализация статической переменной
int DeliverySystem::m_orderCounter = 0;

// Конструктор
DeliverySystem::DeliverySystem() {}

// Деструктор
DeliverySystem::~DeliverySystem() {
}

// Вывод информации о системе с использованием this
void DeliverySystem::printSystemInfo() const {
	std::cout << "=== Информация о системе доставки ===" << std::endl;
	std::cout << "Версия системы: " << this->getSystemVersion() << std::endl;
	std::cout << "Всего заказов в системе: " << this->m_allOrders.size() << std::endl;
	std::cout << "Всего клиентов: " << this->m_allClients.size() << std::endl;
	std::cout << "Всего курьеров: " << this->m_allCouriers.size() << std::endl;
	std::cout << "Глобальный счетчик заказов: " << this->getGlobalOrderCount() << std::endl;
}

// Создание нового заказа с обработкой исключений
std::shared_ptr<Order> DeliverySystem::createOrder(std::shared_ptr<Client> sender, std::shared_ptr<Client> receiver, const Address& from, const Address& to, const Parcel& parcel, std::shared_ptr<Tariff> tariff)
{
	try {
		// Валидация входных данных
		validateOrderData(from, to, parcel);

		if (!tariff) {
			throw std::invalid_argument("Тариф не может быть нулевым");
		}
	std::string trackingNumber = "TRK" + std::to_string(++m_orderCounter);
	auto newOrder = std::make_shared<Order>(trackingNumber, from, to, parcel, tariff.get());

	m_allOrders.push_back(newOrder);
	if (sender) sender->addToHistory(newOrder);

	incrementGlobalOrderCount();

	return newOrder;
}
	catch (const InvalidAddressException& e) {
		std::cerr << "Ошибка адреса при создании заказа: " << e.what() << std::endl;
		throw OrderCreationException("Не удалось создать заказ из-за неверного адреса", e);
	}
	catch (const InvalidParcelException& e) {
		std::cerr << "Ошибка посылки при создании заказа: " << e.what() << std::endl;
		throw OrderCreationException("Не удалось создать заказ из-за неверных данных посылки", e);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Неверный аргумент при создании заказа: " << e.what() << std::endl;
		throw OrderCreationException("Неверные параметры заказа", e);
	}
	catch (const std::exception& e) {
		std::cerr << "Неизвестная ошибка при создании заказа: " << e.what() << std::endl;
		throw OrderCreationException("Неизвестная ошибка при создании заказа", e);
	}
}

// Поиск клиента по ID с исключением
std::shared_ptr<Client> DeliverySystem::findClientById(int id) const {
    for (const auto& client : m_allClients) {
        if (client->getId() == id) {
            return client;
        }
    }
    throw ClientNotFoundException("Клиент с ID " + std::to_string(id) + " не найден");
}

// Поиск доступного курьера с исключением
std::shared_ptr<Courier> DeliverySystem::findAvailableCourier() const {
    for (const auto& courier : m_allCouriers) {
        if (courier->getIsAvailable()) {
            return courier;
        }
    }
    throw NoAvailableCourierException("Нет доступных курьеров в системе");
}

// Валидация данных заказа
void DeliverySystem::validateOrderData(const Address& from, const Address& to, const Parcel& parcel) const {
    // Проверка адреса отправителя
    if (from.getStreet().empty() || from.getCity().empty()) {
        throw InvalidAddressException("Адрес отправителя не может быть пустым");
    }

    // Проверка адреса получателя
    if (to.getStreet().empty() || to.getCity().empty()) {
        throw InvalidAddressException("Адрес получателя не может быть пустым");
    }

    // Проверка что адреса разные
    if (from.getStreet() == to.getStreet() && from.getCity() == to.getCity()) {
        throw InvalidAddressException("Адреса отправителя и получателя не могут совпадать");
    }

    // Проверка посылки
    if (parcel.getWeight() <= 0) {
        throw InvalidParcelException("Вес посылки должен быть положительным");
    }

    if (parcel.getWeight() > 100.0) {
        throw InvalidParcelException("Вес посылки не может превышать 100 кг");
    }

    if (parcel.calculateVolume() <= 0) {
        throw InvalidParcelException("Объем посылки должен быть положительным");
    }

    if (parcel.calculateVolume() > 1000000.0) { // 1 м?
        throw InvalidParcelException("Объем посылки не может превышать 1 м?");
    }

    if (parcel.getEstimatedValue() < 0) {
        throw InvalidParcelException("Оценочная стоимость не может быть отрицательной");
    }
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