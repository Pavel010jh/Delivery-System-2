#include <iostream>
#include <locale.h>
#include <iomanip>
#include <memory>
#include "address.h"
#include "parcel.h"
#include "client.h"
#include "courier.h"
#include "warehouse.h"
#include "tariff.h"
#include "order.h"
#include "delivery_system.h"

using namespace std;

string statusToString(OrderStatus status) {
	switch (status) {
	case OrderStatus::CREATED: return "СОЗДАН";
	case OrderStatus::IN_PROGRESS: return "В ПРОЦЕССЕ";
	case OrderStatus::DELIVERED: return "ДОСТАВЛЕН";
	default: return "НЕИЗВЕСТЕН";
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	cout << fixed << setprecision(2);

	cout << "=== Демонстрация системы доставки ===" << endl;

	cout << "\n1. Статическая инициализация:" << endl;
	Address address1("ул. Ленина", "Москва", "101000");
	Parcel parcel1("Книги", 2.0, 30, 20, 10, 500);
	cout << "Адрес: " << address1.getFullAddress() << endl;
	cout << "Посылка: " << parcel1.getDescription() << ", вес: " << parcel1.getWeight() << " кг"
		<< ", объём: " << parcel1.calculateVolume() << "см^3" << ", стоимость: " << parcel1.getEstimatedValue() << " руб." << endl;

	cout << "\n2. Динамическая инициализация:" << endl;
	Client* client1 = new Client(1, "Иван Иванов", "+79161112233", "ivan@mail.com");
	Courier* courier1 = new Courier(1, "Пётр Петров", "+79061133233", "автомобиль", true);
	cout << "Клиент: " << client1->getName() << ", телефон: " << client1->getPhoneNumber() << ", email: " << client1->getEmail() << endl;
	cout << "Курьер: " << courier1->getName() << ", транспорт: " << courier1->getVehicleType() << ", доступен: " << (courier1->getIsAvailable() ? "да" : "нет") << endl;

	cout << "\n3. Работа с ссылками и указателями:" << endl;
	Address address2("ул. Пушкина", "Санкт-Петербург", "190000");
	Address& ref = address2;
	Address* ptr = &address2;
	cout << "Через ссылку: " << ref.getFullAddress() << endl;
	cout << "Через указатель: " << ptr->getFullAddress() << endl;

	cout << "\n4. Динамический массив объектов класса:" << endl;
	Parcel* parcels = new Parcel[2]{
		Parcel("Документы", 0.5, 20, 15, 5, 100),
		Parcel("Одежда", 1.0, 40, 30, 10, 800)
	};
	for (int i = 0; i < 2; i++) {
		cout << "Посылка" << (i + 1) << ": " << parcels[i].getDescription() << ", объём:" << parcels[i].calculateVolume() << " см^3" << ", вес:" << parcels[i].getWeight() << "кг" << endl;
	}
	delete[] parcels;

	cout << "\n5. Массив динамических объектов класса :" << endl;
	Client** clients = new Client * [2];
	clients[0] = new Client(2, "Анна Сидорова", "+79872223344", "anna@mail.com");
	clients[1] = new Client(3, "Сергей Петров", "+79452323359", "sergey@mail.com");

	for (int i = 0; i < 2; i++) {
		cout << "Клиент " << (i + 1) << ": " << clients[i]->getName() << ", телефон: " << clients[i]->getPhoneNumber() << endl;
		delete clients[i];
	}
	delete[] clients;

	cout << "\n6. Полная демонстрация системы:" << endl;

	DeliverySystem system;

	ExpressTariff express("Экспресс доставка", 300.00);

	Address from("ул. Партизанская 10", "Москва", "101100");
	Address to("ул. Ленина 20", "Москва", "102100");
	Parcel parcel("Документы", 1.5, 35, 25, 5, 2000);

	Order* order = system.createOrder(client1, nullptr, from, to, parcel, &express);
	order->assignCourier(courier1);

	cout << "=== ИНФОРМАЦИЯ О ЗАКАЗЕ ===" << endl;
	cout << "Трек номер: " << order->getTrackingNumber() << endl;
	cout << "Статус: " << statusToString(order->getStatus()) << endl;
	cout << "Стоимость доставки: " << order->getFinalCost() << " руб." << endl;
	cout << "Откуда: " << from.getFullAddress() << endl;
	cout << "Куда: " << to.getFullAddress() << endl;
	cout << "Посылка: " << parcel.getDescription() << " (" << parcel.calculateVolume() << " см^3)" << endl;
	cout << "Тариф: " << express.getName() << endl;

	Courier* assignedCourier = order->getAssignedCourier();
	cout << "Курьер:" << (assignedCourier ? assignedCourier->getName() : "не назначен") << endl;

	delete client1;
	delete courier1;

	return 0;
}