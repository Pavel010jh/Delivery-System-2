#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "order.h"
#include "client.h"
#include "courier.h"
#include"warehouse.h"
#include "tariff.h"

using namespace std;

class DeliverySystem {
public:
	// Êîíñòðóêòîð è äåñòðóêòîð
	DeliverySystem();
	~DeliverySystem();

	// Îñíîâíûå ìåòîäû ñ îáðàáîòêîé èñêëþ÷åíèé
	std::shared_ptr<Order> createOrder(std::shared_ptr<Client> sender, std::shared_ptr<Client> receiver, const Address& from, const Address& to, const Parcel& parcel, std::shared_ptr<Tariff> tariff);

	std::vector < std::shared_ptr<Order>> findOrdersByStatus(OrderStatus status) const;

	// Ìåòîäû ñ èñêëþ÷åíèÿìè
	std::shared_ptr<Client> findClientById(int id) const;
	std::shared_ptr<Courier> findAvailableCourier() const;
	void validateOrderData(const Address& from, const Address& to, const Parcel& parcel) const;

	// Ñòàòè÷åñêèå ìåòîäû
	static int getGlobalOrderCount() { return s_globalOrderCount; }
	static std::string getSystemVersion() { return s_systemVersion; }
	static void incrementGlobalOrderCount() { s_globalOrderCount++; }

	// Èñïîëüçîâàíèå this
	DeliverySystem* getSystemInstance() { return this; }
	const DeliverySystem* getSystemInstance() const { return this; }
	void printSystemInfo() const;

	// Ìåòîäû äîáàâëåíèÿ ñóùíîñòåé
	void addClient(std::shared_ptr<Client> client);
	void addCourier(std::shared_ptr<Courier> courier);
	void addTariff(std::shared_ptr<Tariff> tariff);

	// Ãåòòåðû
	std::vector<std::shared_ptr<Order>> getAllOrders() const { return m_allOrders; }

private:
	std::vector<std::shared_ptr<Order>> m_allOrders;
	std::vector<std::shared_ptr<Courier>> m_allCouriers;
	std::vector<std::shared_ptr<Client>> m_allClients;
	std::vector<std::shared_ptr<Warehouse>> m_allWarehouses;
	std::vector<std::shared_ptr<Tariff>> m_availableTariffs;
	static int m_orderCounter;
	// Ñòàòè÷åñêèå ïîëÿ
	static int s_globalOrderCount;
	static const std::string s_systemVersion;

	// Ïîëüçîâàòåëüñêèå êëàññû èñêëþ÷åíèé
	class InvalidAddressException : public std::runtime_error {
	public:
		InvalidAddressException(const std::string& message) : std::runtime_error(message) {}
	};

	class InvalidParcelException : public std::runtime_error {
	public:
		InvalidParcelException(const std::string& message) : std::runtime_error(message) {}
	};

	class ClientNotFoundException : public std::runtime_error {
	public:
		ClientNotFoundException(const std::string& message) : std::runtime_error(message) {}
	};

	class NoAvailableCourierException : public std::runtime_error {
	public:
		NoAvailableCourierException(const std::string& message) : std::runtime_error(message) {}
	};

	class OrderCreationException : public std::runtime_error {
	public:
		OrderCreationException(const std::string& message) : std::runtime_error(message) {}

		OrderCreationException(const std::string& message, const std::exception& cause)
			: std::runtime_error(message + ": " + cause.what()) {}
	};
};