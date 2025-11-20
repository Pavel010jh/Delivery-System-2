#include "delivery_system.h"
#include <iostream>
#include <algorithm>

// Èíèöèàëèçàöèÿ ñòàòè÷åñêèõ ïåðåìåííûõ
int DeliverySystem::s_globalOrderCount = 0;
const std::string DeliverySystem::s_systemVersion = "2.1.0";

// Èíèöèàëèçàöèÿ ñòàòè÷åñêîé ïåðåìåííîé
int DeliverySystem::m_orderCounter = 0;

// Êîíñòðóêòîð
DeliverySystem::DeliverySystem() {}

// Äåñòðóêòîð
DeliverySystem::~DeliverySystem() {
}

// Âûâîä èíôîðìàöèè î ñèñòåìå ñ èñïîëüçîâàíèåì this
void DeliverySystem::printSystemInfo() const {
	std::cout << "=== Èíôîðìàöèÿ î ñèñòåìå äîñòàâêè ===" << std::endl;
	std::cout << "Âåðñèÿ ñèñòåìû: " << this->getSystemVersion() << std::endl;
	std::cout << "Âñåãî çàêàçîâ â ñèñòåìå: " << this->m_allOrders.size() << std::endl;
	std::cout << "Âñåãî êëèåíòîâ: " << this->m_allClients.size() << std::endl;
	std::cout << "Âñåãî êóðüåðîâ: " << this->m_allCouriers.size() << std::endl;
	std::cout << "Ãëîáàëüíûé ñ÷åò÷èê çàêàçîâ: " << this->getGlobalOrderCount() << std::endl;
}

// Ñîçäàíèå íîâîãî çàêàçà ñ îáðàáîòêîé èñêëþ÷åíèé
std::shared_ptr<Order> DeliverySystem::createOrder(std::shared_ptr<Client> sender, std::shared_ptr<Client> receiver, const Address& from, const Address& to, const Parcel& parcel, std::shared_ptr<Tariff> tariff)
{
	try {
		// Âàëèäàöèÿ âõîäíûõ äàííûõ
		validateOrderData(from, to, parcel);

		if (!tariff) {
			throw std::invalid_argument("Òàðèô íå ìîæåò áûòü íóëåâûì");
		}
	std::string trackingNumber = "TRK" + std::to_string(++m_orderCounter);
	auto newOrder = std::make_shared<Order>(trackingNumber, from, to, parcel, tariff.get());

	m_allOrders.push_back(newOrder);
	if (sender) sender->addToHistory(newOrder);

	incrementGlobalOrderCount();

	return newOrder;
}
	catch (const InvalidAddressException& e) {
		std::cerr << "Îøèáêà àäðåñà ïðè ñîçäàíèè çàêàçà: " << e.what() << std::endl;
		throw OrderCreationException("Íå óäàëîñü ñîçäàòü çàêàç èç-çà íåâåðíîãî àäðåñà", e);
	}
	catch (const InvalidParcelException& e) {
		std::cerr << "Îøèáêà ïîñûëêè ïðè ñîçäàíèè çàêàçà: " << e.what() << std::endl;
		throw OrderCreationException("Íå óäàëîñü ñîçäàòü çàêàç èç-çà íåâåðíûõ äàííûõ ïîñûëêè", e);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Íåâåðíûé àðãóìåíò ïðè ñîçäàíèè çàêàçà: " << e.what() << std::endl;
		throw OrderCreationException("Íåâåðíûå ïàðàìåòðû çàêàçà", e);
	}
	catch (const std::exception& e) {
		std::cerr << "Íåèçâåñòíàÿ îøèáêà ïðè ñîçäàíèè çàêàçà: " << e.what() << std::endl;
		throw OrderCreationException("Íåèçâåñòíàÿ îøèáêà ïðè ñîçäàíèè çàêàçà", e);
	}
}

// Ïîèñê êëèåíòà ïî ID ñ èñêëþ÷åíèåì
std::shared_ptr<Client> DeliverySystem::findClientById(int id) const {
    for (const auto& client : m_allClients) {
        if (client->getId() == id) {
            return client;
        }
    }
    throw ClientNotFoundException("Êëèåíò ñ ID " + std::to_string(id) + " íå íàéäåí");
}

// Ïîèñê äîñòóïíîãî êóðüåðà ñ èñêëþ÷åíèåì
std::shared_ptr<Courier> DeliverySystem::findAvailableCourier() const {
    for (const auto& courier : m_allCouriers) {
        if (courier->getIsAvailable()) {
            return courier;
        }
    }
    throw NoAvailableCourierException("Íåò äîñòóïíûõ êóðüåðîâ â ñèñòåìå");
}

// Âàëèäàöèÿ äàííûõ çàêàçà
void DeliverySystem::validateOrderData(const Address& from, const Address& to, const Parcel& parcel) const {
    // Ïðîâåðêà àäðåñà îòïðàâèòåëÿ
    if (from.getStreet().empty() || from.getCity().empty()) {
        throw InvalidAddressException("Àäðåñ îòïðàâèòåëÿ íå ìîæåò áûòü ïóñòûì");
    }

    // Ïðîâåðêà àäðåñà ïîëó÷àòåëÿ
    if (to.getStreet().empty() || to.getCity().empty()) {
        throw InvalidAddressException("Àäðåñ ïîëó÷àòåëÿ íå ìîæåò áûòü ïóñòûì");
    }

    // Ïðîâåðêà ÷òî àäðåñà ðàçíûå
    if (from.getStreet() == to.getStreet() && from.getCity() == to.getCity()) {
        throw InvalidAddressException("Àäðåñà îòïðàâèòåëÿ è ïîëó÷àòåëÿ íå ìîãóò ñîâïàäàòü");
    }

    // Ïðîâåðêà ïîñûëêè
    if (parcel.getWeight() <= 0) {
        throw InvalidParcelException("Âåñ ïîñûëêè äîëæåí áûòü ïîëîæèòåëüíûì");
    }

    if (parcel.getWeight() > 100.0) {
        throw InvalidParcelException("Âåñ ïîñûëêè íå ìîæåò ïðåâûøàòü 100 êã");
    }

    if (parcel.calculateVolume() <= 0) {
        throw InvalidParcelException("Îáúåì ïîñûëêè äîëæåí áûòü ïîëîæèòåëüíûì");
    }

    if (parcel.calculateVolume() > 1000000.0) { // 1 ì?
        throw InvalidParcelException("Îáúåì ïîñûëêè íå ìîæåò ïðåâûøàòü 1 ì?");
    }

    if (parcel.getEstimatedValue() < 0) {
        throw InvalidParcelException("Îöåíî÷íàÿ ñòîèìîñòü íå ìîæåò áûòü îòðèöàòåëüíîé");
    }
}

// Ïîèñê çàêàçîâ ïî ñòàòóñó
std::vector<std::shared_ptr<Order>> DeliverySystem::findOrdersByStatus(OrderStatus status) const {
	std::vector<std::shared_ptr<Order>> result;
	for (auto order : m_allOrders) {
		if (order->getStatus() == status) {
			result.push_back(order);
		}
	}
	return result;
}

// Äîáàâëåíèå êëèåíòà â ñèñòåìó
void DeliverySystem::addClient(std::shared_ptr<Client> client) {
	m_allClients.push_back(client);
}

// Äîáàâëåíèå êóðüåðà â ñèñòåìó
void DeliverySystem::addCourier(std::shared_ptr<Courier> courier) {
	m_allCouriers.push_back(courier);
}

// Äîáàâëåíèå òàðèôà â ñèñòåìó
void DeliverySystem::addTariff(std::shared_ptr<Tariff> tariff) {
	m_availableTariffs.push_back(tariff);
}