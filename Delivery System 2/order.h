#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "address.h"
#include "parcel.h"

using namespace std;

class Courier;
class Tariff;

// Статусы заказа
enum class OrderStatus {
	CREATED = 0,
	IN_PROGRESS = 1,
	DELIVERED = 2
};

class Order {
public:
	Order(const std::string& trackingNumber, const Address& fromAddress, const Address& toAddress, const Parcel& parcel, Tariff* tariff);

	// Конструктор копирования
	Order(const Order& other);

	// Оператор присваивания
	Order& operator=(const Order& other);

	// Методы для работы со строками
	std::string getStatusString() const;
	std::string getDetailedInfo() const;
	bool trackingNumberStartsWith(const std::string& prefix) const;

	// Методы с обработкой исключений
	void updateStatus(OrderStatus newStatus);
	void assignCourier(std::shared_ptr<Courier> courier);
	void calculateFinalCost();
	void validateOrder() const;

	// Статические методы и поля
	static int getTotalOrdersCreated() { return s_totalOrdersCreated; }
	static double getTotalRevenue() { return s_totalRevenue; }
	static void resetStatistics();

	// Использование this
	Order* getThisPointer() { return this; }
	const Order* getThisPointer() const { return this; }
	void printOrderInfo() const;

	// Перегрузка операторов
	bool operator<(const Order& other) const;
	bool operator>(const Order& other) const;
	Order& operator++();    // Префиксный инкремент
	Order operator++(int);  // Постфиксный инкремент

	// Геттеры
	std::string getTrackingNumber() const { return m_trackingNumber; }
	OrderStatus getStatus() const { return m_status; }
	double getFinalCost() const { return m_finalCost; }
	std::shared_ptr<Courier> getAssignedCourier() const { return m_assignedCourier; }

private:
	std::string m_trackingNumber;
	OrderStatus m_status;
	double m_finalCost;
	Address m_fromAddress;
	Address m_toAddress;
	Parcel m_parcel;
	std::shared_ptr<Courier> m_assignedCourier;
	Tariff* m_chosenTariff;
	// Статические поля
	static int s_totalOrdersCreated;
	static double s_totalRevenue;
	// Вспомогательные методы
	std::string getStatusString() const;
};

// Пользовательские исключения для Order
class InvalidOrderException : public std::runtime_error {
public:
	InvalidOrderException(const std::string& message) : std::runtime_error(message) {}
};

class OrderStatusException : public std::runtime_error {
public:
	OrderStatusException(const std::string& message) : std::runtime_error(message) {}
};