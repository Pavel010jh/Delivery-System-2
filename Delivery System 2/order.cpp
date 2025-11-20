ï»¿#include "order.h"
#include "courier.h"
#include "tariff.h"
#include <sstream>
#include <iostream>

// ÐÐ½Ð¸ÑÐ¸Ð°Ð»Ð¸Ð·Ð°ÑÐ¸Ñ ÑÑÐ°ÑÐ¸ÑÐµÑÐºÐ¸Ñ Ð¿Ð¾Ð»ÐµÐ¹
int Order::s_totalOrdersCreated = 0;
double Order::s_totalRevenue = 0.0;

// ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ Ð·Ð°ÐºÐ°Ð·Ð°
Order::Order(const std::string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff)
	: m_trackingNumber(trackingNumber), m_status(OrderStatus::CREATED),
	m_finalCost(0.0), m_fromAddress(fromAddress), m_toAddress(toAddress),
	m_parcel(parcel), m_assignedCourier(nullptr), m_chosenTariff(tariff)
{
    // ÐÐ°Ð»Ð¸Ð´Ð°ÑÐ¸Ñ Ð¿ÑÐ¸ ÑÐ¾Ð·Ð´Ð°Ð½Ð¸Ð¸
    validateOrder();
	calculateFinalCost();
    // ÐÐ±Ð½Ð¾Ð²Ð»ÑÐµÐ¼ ÑÑÐ°ÑÐ¸ÑÐµÑÐºÐ¸Ðµ Ð¿Ð¾Ð»Ñ
    s_totalOrdersCreated++;
    s_totalRevenue += m_finalCost;
}

// ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ ÐºÐ¾Ð¿Ð¸ÑÐ¾Ð²Ð°Ð½Ð¸Ñ
Order::Order(const Order& other)
    : m_trackingNumber(other.m_trackingNumber), m_status(other.m_status),
    m_finalCost(other.m_finalCost), m_fromAddress(other.m_fromAddress),
    m_toAddress(other.m_toAddress), m_parcel(other.m_parcel),
    m_assignedCourier(other.m_assignedCourier), m_chosenTariff(other.m_chosenTariff) {
    s_totalOrdersCreated++;
    s_totalRevenue += m_finalCost;
}

// ÐÐ¿ÐµÑÐ°ÑÐ¾Ñ Ð¿ÑÐ¸ÑÐ²Ð°Ð¸Ð²Ð°Ð½Ð¸Ñ
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        // ÐÑÑÐ¸ÑÐ°ÐµÐ¼ ÑÑÐ°ÑÑÑ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ Ð¸Ð· Ð¾Ð±ÑÐµÐ¹ Ð²ÑÑÑÑÐºÐ¸
        s_totalRevenue -= m_finalCost;
        m_trackingNumber = other.m_trackingNumber;
        m_status = other.m_status;
        m_finalCost = other.m_finalCost;
        m_fromAddress = other.m_fromAddress;
        m_toAddress = other.m_toAddress;
        m_parcel = other.m_parcel;
        m_assignedCourier = other.m_assignedCourier;
        m_chosenTariff = other.m_chosenTariff;
        // ÐÐ¾Ð±Ð°Ð²Ð»ÑÐµÐ¼ Ð½Ð¾Ð²ÑÑ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ Ð² Ð¾Ð±ÑÑÑ Ð²ÑÑÑÑÐºÑ
        s_totalRevenue += m_finalCost;
    }
    return *this;
}

// ÐÐ°Ð»Ð¸Ð´Ð°ÑÐ¸Ñ Ð·Ð°ÐºÐ°Ð·Ð°
void Order::validateOrder() const {
    if (m_trackingNumber.empty()) {
        throw InvalidOrderException("Ð¢ÑÐµÐº-Ð½Ð¾Ð¼ÐµÑ Ð½Ðµ Ð¼Ð¾Ð¶ÐµÑ Ð±ÑÑÑ Ð¿ÑÑÑÑÐ¼");
    }

    if (m_trackingNumber.find("TRK") != 0) {
        throw InvalidOrderException("Ð¢ÑÐµÐº-Ð½Ð¾Ð¼ÐµÑ Ð´Ð¾Ð»Ð¶ÐµÐ½ Ð½Ð°ÑÐ¸Ð½Ð°ÑÑÑÑ Ñ 'TRK'");
    }

    if (!m_chosenTariff) {
        throw InvalidOrderException("ÐÐµ Ð²ÑÐ±ÑÐ°Ð½ ÑÐ°ÑÐ¸Ñ Ð´Ð»Ñ Ð·Ð°ÐºÐ°Ð·Ð°");
    }

    if (m_finalCost < 0) {
        throw InvalidOrderException("Ð¡ÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ Ð·Ð°ÐºÐ°Ð·Ð° Ð½Ðµ Ð¼Ð¾Ð¶ÐµÑ Ð±ÑÑÑ Ð¾ÑÑÐ¸ÑÐ°ÑÐµÐ»ÑÐ½Ð¾Ð¹");
    }
}

// Ð¡Ð±ÑÐ¾Ñ ÑÑÐ°ÑÐ¸ÑÑÐ¸ÐºÐ¸
void Order::resetStatistics() {
    s_totalOrdersCreated = 0;
    s_totalRevenue = 0.0;
}

// ÐÑÐ²Ð¾Ð´ Ð¸Ð½ÑÐ¾ÑÐ¼Ð°ÑÐ¸Ð¸ Ð¾ Ð·Ð°ÐºÐ°Ð·Ðµ Ñ Ð¸ÑÐ¿Ð¾Ð»ÑÐ·Ð¾Ð²Ð°Ð½Ð¸ÐµÐ¼ this
void Order::printOrderInfo() const {
    std::cout << "ÐÐ½ÑÐ¾ÑÐ¼Ð°ÑÐ¸Ñ Ð¾ Ð·Ð°ÐºÐ°Ð·Ðµ (ÑÐµÑÐµÐ· this):" << std::endl;
    std::cout << "  Ð¢ÑÐµÐº Ð½Ð¾Ð¼ÐµÑ: " << this->m_trackingNumber << std::endl;
    std::cout << "  Ð¡ÑÐ°ÑÑÑ: " << this->getStatusString() << std::endl;
    std::cout << "  Ð¡ÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ: " << this->m_finalCost << " ÑÑÐ±." << std::endl;

    if (this->m_assignedCourier) {
        std::cout << "  ÐÑÑÑÐµÑ: " << this->m_assignedCourier->getName() << std::endl;
    }
}

// Ð¡ÑÑÐ¾ÐºÐ¾Ð²Ð¾Ðµ Ð¿ÑÐµÐ´ÑÑÐ°Ð²Ð»ÐµÐ½Ð¸Ðµ ÑÑÐ°ÑÑÑÐ°
std::string Order::getStatusString() const {
    switch (m_status) {
    case OrderStatus::CREATED: return "Ð¡Ð¾Ð·Ð´Ð°Ð½";
    case OrderStatus::IN_PROGRESS: return "Ð Ð¿ÑÐ¾ÑÐµÑÑÐµ Ð´Ð¾ÑÑÐ°Ð²ÐºÐ¸";
    case OrderStatus::DELIVERED: return "ÐÐ¾ÑÑÐ°Ð²Ð»ÐµÐ½";
    default: return "ÐÐµÐ¸Ð·Ð²ÐµÑÑÐµÐ½";
    }
}



// ÐÑÐ¾Ð²ÐµÑÐºÐ° Ð¿ÑÐµÑÐ¸ÐºÑÐ° ÑÑÐµÐº-Ð½Ð¾Ð¼ÐµÑÐ°
bool Order::trackingNumberStartsWith(const std::string& prefix) const {
    return m_trackingNumber.find(prefix) == 0;
}

// ÐÐ±Ð½Ð¾Ð²Ð»ÐµÐ½Ð¸Ðµ ÑÑÐ°ÑÑÑÐ° Ð·Ð°ÐºÐ°Ð·Ð° Ñ Ð¿ÑÐ¾Ð²ÐµÑÐºÐ°Ð¼Ð¸
void Order::updateStatus(OrderStatus newStatus) {
    // ÐÑÐ¾Ð²ÐµÑÐºÐ° Ð²Ð°Ð»Ð¸Ð´Ð½Ð¾ÑÑÐ¸ Ð¿ÐµÑÐµÑÐ¾Ð´Ð° ÑÑÐ°ÑÑÑÐ¾Ð²
    if (m_status == OrderStatus::DELIVERED && newStatus != OrderStatus::DELIVERED) {
        throw OrderStatusException("ÐÐµÐ»ÑÐ·Ñ Ð¸Ð·Ð¼ÐµÐ½Ð¸ÑÑ ÑÑÐ°ÑÑÑ Ð´Ð¾ÑÑÐ°Ð²Ð»ÐµÐ½Ð½Ð¾Ð³Ð¾ Ð·Ð°ÐºÐ°Ð·Ð°");
    }

    if (m_status == OrderStatus::CREATED && newStatus == OrderStatus::DELIVERED) {
        throw OrderStatusException("ÐÐµÐ»ÑÐ·Ñ Ð¿Ð¾Ð¼ÐµÑÐ¸ÑÑ Ð·Ð°ÐºÐ°Ð· ÐºÐ°Ðº Ð´Ð¾ÑÑÐ°Ð²Ð»ÐµÐ½Ð½ÑÐ¹ Ð±ÐµÐ· Ð¿ÑÐ¾ÑÐµÑÑÐ° Ð´Ð¾ÑÑÐ°Ð²ÐºÐ¸");
    }

    m_status = newStatus;
}

// ÐÐ°Ð·Ð½Ð°ÑÐµÐ½Ð¸Ðµ ÐºÑÑÑÐµÑÐ° Ð½Ð° Ð·Ð°ÐºÐ°Ð· Ñ Ð¿ÑÐ¾Ð²ÐµÑÐºÐ°Ð¼Ð¸
void Order::assignCourier(std::shared_ptr<Courier> courier) {
    if (!courier) {
        throw std::invalid_argument("ÐÑÑÑÐµÑ Ð½Ðµ Ð¼Ð¾Ð¶ÐµÑ Ð±ÑÑÑ Ð¿ÑÑÑÑÐ¼");
    }

    if (m_status != OrderStatus::CREATED) {
        throw OrderStatusException("ÐÐ¾Ð¶Ð½Ð¾ Ð½Ð°Ð·Ð½Ð°ÑÐ°ÑÑ ÐºÑÑÑÐµÑÐ° ÑÐ¾Ð»ÑÐºÐ¾ Ð´Ð»Ñ ÑÐ¾Ð·Ð´Ð°Ð½Ð½ÑÑ Ð·Ð°ÐºÐ°Ð·Ð¾Ð²");
    }

    if (!courier->getIsAvailable()) {
        throw OrderStatusException("ÐÑÑÑÐµÑ Ð½ÐµÐ´Ð¾ÑÑÑÐ¿ÐµÐ½ Ð´Ð»Ñ Ð½Ð°Ð·Ð½Ð°ÑÐµÐ½Ð¸Ñ");
    }

    if (courier->assignOrder(std::make_shared<Order>(*this))) {
        m_assignedCourier = courier;
        updateStatus(OrderStatus::IN_PROGRESS);
    }
    else {
        throw OrderStatusException("ÐÐµ ÑÐ´Ð°Ð»Ð¾ÑÑ Ð½Ð°Ð·Ð½Ð°ÑÐ¸ÑÑ ÐºÑÑÑÐµÑÐ° Ð½Ð° Ð·Ð°ÐºÐ°Ð·");
    }
}

// Ð Ð°ÑÑÐµÑ Ð¸ÑÐ¾Ð³Ð¾Ð²Ð¾Ð¹ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÐ¸ Ñ Ð¾Ð±ÑÐ°Ð±Ð¾ÑÐºÐ¾Ð¹ Ð¾ÑÐ¸Ð±Ð¾Ðº
void Order::calculateFinalCost() {
    try {
        if (m_chosenTariff) {
            // ÐÐ±Ð½Ð¾Ð²Ð»ÑÐµÐ¼ Ð¾Ð±ÑÑÑ Ð²ÑÑÑÑÐºÑ (Ð²ÑÑÐ¸ÑÐ°ÐµÐ¼ ÑÑÐ°ÑÑÑ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ, Ð´Ð¾Ð±Ð°Ð²Ð»ÑÐµÐ¼ Ð½Ð¾Ð²ÑÑ)
            s_totalRevenue -= m_finalCost;
            m_finalCost = m_chosenTariff->calculateCost(m_parcel, m_fromAddress, m_toAddress);
            s_totalRevenue += m_finalCost;
            if (m_finalCost < 0) {
                throw std::logic_error("Ð Ð°ÑÑÑÐ¸ÑÐ°Ð½Ð½Ð°Ñ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÑ Ð½Ðµ Ð¼Ð¾Ð¶ÐµÑ Ð±ÑÑÑ Ð¾ÑÑÐ¸ÑÐ°ÑÐµÐ»ÑÐ½Ð¾Ð¹");
            }
        }
        else {
            throw std::logic_error("ÐÐµ Ð²ÑÐ±ÑÐ°Ð½ ÑÐ°ÑÐ¸Ñ Ð´Ð»Ñ ÑÐ°ÑÑÐµÑÐ° ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÐ¸");
        }
    }
    catch (const std::exception& e) {
        // ÐÐ¾ÑÑÑÐ°Ð½Ð°Ð²Ð»Ð¸Ð²Ð°ÐµÐ¼ Ð¿ÑÐµÐ´ÑÐ´ÑÑÐµÐµ Ð·Ð½Ð°ÑÐµÐ½Ð¸Ðµ Ð²ÑÑÑÑÐºÐ¸
        s_totalRevenue += m_finalCost;
        throw InvalidOrderException(std::string("ÐÑÐ¸Ð±ÐºÐ° ÑÐ°ÑÑÐµÑÐ° ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÐ¸: ") + e.what());
    }
}


// ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ° < (ÑÑÐ°Ð²Ð½ÐµÐ½Ð¸Ðµ Ð¿Ð¾ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÐ¸)
bool Order::operator<(const Order& other) const {
    return m_finalCost < other.m_finalCost;
}

// ÐÐµÑÐµÐ³ÑÑÐ·ÐºÐ° Ð¾Ð¿ÐµÑÐ°ÑÐ¾ÑÐ° > (ÑÑÐ°Ð²Ð½ÐµÐ½Ð¸Ðµ Ð¿Ð¾ ÑÑÐ¾Ð¸Ð¼Ð¾ÑÑÐ¸)
bool Order::operator>(const Order& other) const {
    return m_finalCost > other.m_finalCost;
}

// ÐÑÐµÑÐ¸ÐºÑÐ½ÑÐ¹ Ð¸Ð½ÐºÑÐµÐ¼ÐµÐ½Ñ (Ð¿ÐµÑÐµÑÐ¾Ð´ Ðº ÑÐ»ÐµÐ´ÑÑÑÐµÐ¼Ñ ÑÑÐ°ÑÑÑÑ)
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
        std::cerr << "ÐÑÐ¸Ð±ÐºÐ° Ð¿ÑÐ¸ Ð¸Ð·Ð¼ÐµÐ½ÐµÐ½Ð¸Ð¸ ÑÑÐ°ÑÑÑÐ°: " << e.what() << std::endl;
        throw;
    }
    return *this;
}

// ÐÐ¾ÑÑÑÐ¸ÐºÑÐ½ÑÐ¹ Ð¸Ð½ÐºÑÐµÐ¼ÐµÐ½Ñ (Ð¿ÐµÑÐµÑÐ¾Ð´ Ðº ÑÐ»ÐµÐ´ÑÑÑÐµÐ¼Ñ ÑÑÐ°ÑÑÑÑ)
Order Order::operator++(int) {
    Order temp = *this;
    ++(*this);
    return temp;
}