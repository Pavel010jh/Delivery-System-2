#include "order.h"
#include "courier.h"
#include "tariff.h"
#include <sstream>
#include <iostream>

// Инициализация статических полей
int Order::s_totalOrdersCreated = 0;
double Order::s_totalRevenue = 0.0;

// Конструктор заказа
Order::Order(const std::string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff)
	: m_trackingNumber(trackingNumber), m_status(OrderStatus::CREATED),
	m_finalCost(0.0), m_fromAddress(fromAddress), m_toAddress(toAddress),
	m_parcel(parcel), m_assignedCourier(nullptr), m_chosenTariff(tariff)
{
	calculateFinalCost();
    // Обновляем статические поля
    s_totalOrdersCreated++;
    s_totalRevenue += m_finalCost;
}

// Конструктор копирования
Order::Order(const Order& other)
    : m_trackingNumber(other.m_trackingNumber), m_status(other.m_status),
    m_finalCost(other.m_finalCost), m_fromAddress(other.m_fromAddress),
    m_toAddress(other.m_toAddress), m_parcel(other.m_parcel),
    m_assignedCourier(other.m_assignedCourier), m_chosenTariff(other.m_chosenTariff) {
    s_totalOrdersCreated++;
    s_totalRevenue += m_finalCost;
}

// Оператор присваивания
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        // Вычитаем старую стоимость из общей выручки
        s_totalRevenue -= m_finalCost;
        m_trackingNumber = other.m_trackingNumber;
        m_status = other.m_status;
        m_finalCost = other.m_finalCost;
        m_fromAddress = other.m_fromAddress;
        m_toAddress = other.m_toAddress;
        m_parcel = other.m_parcel;
        m_assignedCourier = other.m_assignedCourier;
        m_chosenTariff = other.m_chosenTariff;
        // Добавляем новую стоимость в общую выручку
        s_totalRevenue += m_finalCost;
    }
    return *this;
}

// Сброс статистики
void Order::resetStatistics() {
    s_totalOrdersCreated = 0;
    s_totalRevenue = 0.0;
}

// Вывод информации о заказе с использованием this
void Order::printOrderInfo() const {
    std::cout << "Информация о заказе (через this):" << std::endl;
    std::cout << "  Трек номер: " << this->m_trackingNumber << std::endl;
    std::cout << "  Статус: " << this->getStatusString() << std::endl;
    std::cout << "  Стоимость: " << this->m_finalCost << " руб." << std::endl;

    if (this->m_assignedCourier) {
        std::cout << "  Курьер: " << this->m_assignedCourier->getName() << std::endl;
    }
}

// Строковое представление статуса
std::string Order::getStatusString() const {
    switch (m_status) {
    case OrderStatus::CREATED: return "Создан";
    case OrderStatus::IN_PROGRESS: return "В процессе доставки";
    case OrderStatus::DELIVERED: return "Доставлен";
    default: return "Неизвестен";
    }
}

// Подробная информация о заказе
std::string Order::getDetailedInfo() const {
    std::stringstream ss;
    ss << "Заказ #" << m_trackingNumber << "\n"
        << "Статус: " << getStatusString() << "\n"
        << "Стоимость: " << m_finalCost << " руб.\n"
        << "От: " << m_fromAddress.getFullAddress() << "\n"
        << "Кому: " << m_toAddress.getFullAddress() << "\n"
        << "Посылка: " << m_parcel.getDescription()
        << " (" << m_parcel.calculateVolume() << " см³)";

    if (m_assignedCourier) {
        ss << "\nКурьер: " << m_assignedCourier->getName();
    }

    return ss.str();
}

// Проверка префикса трек-номера
bool Order::trackingNumberStartsWith(const std::string& prefix) const {
    return m_trackingNumber.find(prefix) == 0;
}

// Обновление статуса заказа
void Order::updateStatus(OrderStatus newStatus) {
	m_status = newStatus;
}

// Назначение курьера на заказ
void Order::assignCourier(std::shared_ptr<Courier> courier) {
	if (courier && courier->assignOrder(std::make_shared<Order>(*this))) {
		m_assignedCourier = courier;
		updateStatus(OrderStatus::IN_PROGRESS);
	}
}

// Расчет итоговой стоимости
void Order::calculateFinalCost() {
	if (m_chosenTariff) {
        // Обновляем общую выручку (вычитаем старую стоимость, добавляем новую)
        s_totalRevenue -= m_finalCost;
		m_finalCost = m_chosenTariff->calculateCost(m_parcel, m_fromAddress, m_toAddress);
        s_totalRevenue += m_finalCost;
	}
}

// Перегрузка оператора < (сравнение по стоимости)
bool Order::operator<(const Order& other) const {
    return m_finalCost < other.m_finalCost;
}

// Перегрузка оператора > (сравнение по стоимости)
bool Order::operator>(const Order& other) const {
    return m_finalCost > other.m_finalCost;
}

// Префиксный инкремент (переход к следующему статусу)
Order& Order::operator++() {
    switch (m_status) {
    case OrderStatus::CREATED:
        m_status = OrderStatus::IN_PROGRESS;
        break;
    case OrderStatus::IN_PROGRESS:
        m_status = OrderStatus::DELIVERED;
        break;
    case OrderStatus::DELIVERED:
        break;
    }
    return *this;
}

// Постфиксный инкремент (переход к следующему статусу)
Order Order::operator++(int) {
    Order temp = *this;
    ++(*this);
    return temp;
}