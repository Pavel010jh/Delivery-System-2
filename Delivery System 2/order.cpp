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
    // Валидация при создании
    validateOrder();
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

// Валидация заказа
void Order::validateOrder() const {
    if (m_trackingNumber.empty()) {
        throw InvalidOrderException("Трек-номер не может быть пустым");
    }

    if (m_trackingNumber.find("TRK") != 0) {
        throw InvalidOrderException("Трек-номер должен начинаться с 'TRK'");
    }

    if (!m_chosenTariff) {
        throw InvalidOrderException("Не выбран тариф для заказа");
    }

    if (m_finalCost < 0) {
        throw InvalidOrderException("Стоимость заказа не может быть отрицательной");
    }
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



// Проверка префикса трек-номера
bool Order::trackingNumberStartsWith(const std::string& prefix) const {
    return m_trackingNumber.find(prefix) == 0;
}

// Обновление статуса заказа с проверками
void Order::updateStatus(OrderStatus newStatus) {
    // Проверка валидности перехода статусов
    if (m_status == OrderStatus::DELIVERED && newStatus != OrderStatus::DELIVERED) {
        throw OrderStatusException("Нельзя изменить статус доставленного заказа");
    }

    if (m_status == OrderStatus::CREATED && newStatus == OrderStatus::DELIVERED) {
        throw OrderStatusException("Нельзя пометить заказ как доставленный без процесса доставки");
    }

    m_status = newStatus;
}

// Назначение курьера на заказ с проверками
void Order::assignCourier(std::shared_ptr<Courier> courier) {
    if (!courier) {
        throw std::invalid_argument("Курьер не может быть пустым");
    }

    if (m_status != OrderStatus::CREATED) {
        throw OrderStatusException("Можно назначать курьера только для созданных заказов");
    }

    if (!courier->getIsAvailable()) {
        throw OrderStatusException("Курьер недоступен для назначения");
    }

    if (courier->assignOrder(std::make_shared<Order>(*this))) {
        m_assignedCourier = courier;
        updateStatus(OrderStatus::IN_PROGRESS);
    }
    else {
        throw OrderStatusException("Не удалось назначить курьера на заказ");
    }
}

// Расчет итоговой стоимости с обработкой ошибок
void Order::calculateFinalCost() {
    try {
        if (m_chosenTariff) {
            // Обновляем общую выручку (вычитаем старую стоимость, добавляем новую)
            s_totalRevenue -= m_finalCost;
            m_finalCost = m_chosenTariff->calculateCost(m_parcel, m_fromAddress, m_toAddress);
            s_totalRevenue += m_finalCost;
            if (m_finalCost < 0) {
                throw std::logic_error("Рассчитанная стоимость не может быть отрицательной");
            }
        }
        else {
            throw std::logic_error("Не выбран тариф для расчета стоимости");
        }
    }
    catch (const std::exception& e) {
        // Восстанавливаем предыдущее значение выручки
        s_totalRevenue += m_finalCost;
        throw InvalidOrderException(std::string("Ошибка расчета стоимости: ") + e.what());
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
    try {
        switch (m_status) {
        case OrderStatus::CREATED:
            updateStatus(OrderStatus::IN_PROGRESS);
            break;
        case OrderStatus::IN_PROGRESS:
            updateStatus(OrderStatus::DELIVERED);
            break;
        case OrderStatus::DELIVERED:
            break;
        }
    }
    catch (const OrderStatusException& e) {
        std::cerr << "Ошибка при изменении статуса: " << e.what() << std::endl;
        throw;
    }
    return *this;
}

// Постфиксный инкремент (переход к следующему статусу)
Order Order::operator++(int) {
    Order temp = *this;
    ++(*this);
    return temp;
}