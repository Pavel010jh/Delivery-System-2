#include <iostream>
#include <locale.h>
#include <iomanip>
#include <memory>
#include <vector>
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

    cout << "=== ДЕМОНСТРАЦИЯ ===" << endl << endl;

    try {
        // 1. Демонстрация умных указателей и работы со строками
        cout << "1. Умные указатели и строки:" << endl;
        auto client1 = make_shared<Client>(1, "Иван Иванов", "89161112233", "ivan@mail.com");
        auto client2 = make_shared<Client>(2, "Петр Петров", "89262223344", "petr@mail.com");
        auto courier1 = make_shared<Courier>(1, "Алексей Курьер", "89363334455", "автомобиль", true);

        Address address1("ул. Ленина 10", "Москва", "101000");
        cout << "   Адрес: " << address1 << " (operator<<)" << endl;
        cout << "   Клиент: " << client1->getFullInfo() << endl;

        // 2. Демонстрация перегрузки операторов
        cout << "\n2. Перегрузка операторов:" << endl;
        Parcel parcel1("Книги", 2.0, 30, 20, 10, 500);
        Parcel parcel2("Одежда", 1.5, 25, 15, 5, 300);
        Parcel combined = parcel1 + parcel2;
        cout << "   Объединенная посылка: " << combined.getDescription()
            << ", вес: " << combined.getWeight() << " кг" << endl;

        // 3. Создание системы и заказов
        cout << "\n3. Работа системы:" << endl;
        DeliverySystem system;
        system.addClient(client1);
        system.addClient(client2);
        system.addCourier(courier1);

        ExpressTariff express("Экспресс", 350.00);
        Address from("ул. Отправления 10", "Москва", "101100");
        Address to("ул. Доставки 20", "Москва", "101200");

        auto order1 = system.createOrder(client1, client2, from, to, parcel1,
            make_shared<ExpressTariff>(express));
        cout << "   Заказ создан: " << order1->getTrackingNumber() << endl;

        // 4. Демонстрация статических членов
        cout << "\n4. Статические члены:" << endl;
        cout << "   Всего заказов: " << Order::getTotalOrdersCreated() << endl;
        cout << "   Общая выручка: " << Order::getTotalRevenue() << " руб." << endl;

        order1->printOrderInfo(); // Использование this

        // 5. Демонстрация обработки исключений
        cout << "\n5. Обработка исключений:" << endl;
        try {
            Parcel invalidParcel("", -1.0, 0, 0, 0, 0);
            system.createOrder(client1, nullptr, from, to, invalidParcel,
                make_shared<ExpressTariff>(express));
        }
        catch (const std::exception& e) { 
            cout << "   Поймано исключение: " << e.what() << endl;
        }

        // 6. Демонстрация конструкторов копирования
        cout << "\n6. Конструкторы копирования:" << endl;
        Order orderCopy(*order1);
        cout << "   Копия заказа создана: " << orderCopy.getTrackingNumber() << endl;

        // 7. Финальная статистика
        cout << "\n7. Финальная статистика:" << endl;
        system.printSystemInfo();

    }
    catch (const std::exception& e) {
        cerr << "ОШИБКА: " << e.what() << endl;
        return 1;
    }
    return 0;
}