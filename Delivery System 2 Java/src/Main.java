package src;

import java.util.Locale;

public class Main {
    
    public static String statusToString(OrderStatus status) {
        switch (status) {
            case CREATED: return "СОЗДАН";
            case IN_PROGRESS: return "В ПРОЦЕССЕ";
            case DELIVERED: return "ДОСТАВЛЕН";
            default: return "НЕИЗВЕСТЕН";
        }
    }
    public static void main(String[] args) {
        // Устанавливаем локаль для корректного отображения русских символов
        Locale.setDefault(new Locale("ru", "RU"));
        
        System.out.println("=== Демонстрация системы доставки ===");

        System.out.println("\n1. Статическая инициализация:");
        Address address1 = new Address("ул. Ленина", "Москва", "101000");
        Parcel parcel1 = new Parcel("Книги", 2.0, 30, 20, 10, 500);
        System.out.println("Адрес: " + address1.getFullAddress());
        System.out.println("Посылка: " + parcel1.getDescription() + 
                         ", вес: " + parcel1.getWeight() + " кг" +
                         ", объём: " + parcel1.calculateVolume() + "см^3" + 
                         ", стоимость: " + parcel1.getEstimatedValue() + " руб.");

        System.out.println("\n2. Динамическая инициализация:");
        Client client1 = new Client(1, "Иван Иванов", "+79161112233", "ivan@mail.com");
        Courier courier1 = new Courier(1, "Пётр Петров", "+79061133233", "автомобиль", true);
        System.out.println("Клиент: " + client1.getName() + 
                         ", телефон: " + client1.getPhoneNumber() + 
                         ", email: " + client1.getEmail());
        System.out.println("Курьер: " + courier1.getName() + 
                         ", транспорт: " + courier1.getVehicleType() + 
                         ", доступен: " + (courier1.getIsAvailable() ? "да" : "нет"));

        System.out.println("\n3. Работа с ссылками:");
        Address address2 = new Address("ул. Пушкина", "Санкт-Петербург", "190000");
        Address ref = address2;
        System.out.println("Через ссылку: " + ref.getFullAddress());

        System.out.println("\n4. Массив объектов:");
        Parcel[] parcels = new Parcel[]{
            new Parcel("Документы", 0.5, 20, 15, 5, 100),
            new Parcel("Одежда", 1.0, 40, 30, 10, 800)
        };
        for (int i = 0; i < parcels.length; i++) {
            System.out.println("Посылка" + (i + 1) + ": " + parcels[i].getDescription() + 
                             ", объём:" + parcels[i].calculateVolume() + " см^3" + 
                             ", вес:" + parcels[i].getWeight() + "кг");
        }

        System.out.println("\n5. Массив динамических объектов:");
        Client[] clients = new Client[]{
            new Client(2, "Анна Сидорова", "+79872223344", "anna@mail.com"),
            new Client(3, "Сергей Петров", "+79452323359", "sergey@mail.com")
        };
        for (int i = 0; i < clients.length; i++) {
            System.out.println("Клиент " + (i + 1) + ": " + clients[i].getName() + 
                             ", телефон: " + clients[i].getPhoneNumber());
        }

        System.out.println("\n6. Полная демонстрация системы:");

        DeliverySystem system = new DeliverySystem();
        ExpressTariff express = new ExpressTariff("Экспресс доставка", 300.00);

        Address from = new Address("ул. Партизанская 10", "Москва", "101100");
        Address to = new Address("ул. Ленина 20", "Москва", "102100");
        Parcel parcel = new Parcel("Документы", 1.5, 35, 25, 5, 2000);

        Order order = system.createOrder(client1, null, from, to, parcel, express);
        order.assignCourier(courier1);

        System.out.println("=== ИНФОРМАЦИЯ О ЗАКАЗЕ ===");
        System.out.println("Трек номер: " + order.getTrackingNumber());
        System.out.println("Статус: " + statusToString(order.getStatus()));
        System.out.println("Стоимость доставки: " + order.getFinalCost() + " руб.");
        System.out.println("Откуда: " + from.getFullAddress());
        System.out.println("Куда: " + to.getFullAddress());
        System.out.println("Посылка: " + parcel.getDescription() + 
                         " (" + parcel.calculateVolume() + " см^3)");
        System.out.println("Тариф: " + express.getName());

        Courier assignedCourier = order.getAssignedCourier();
        System.out.println("Курьер: " + (assignedCourier != null ? assignedCourier.getName() : "не назначен"));

        System.out.println("\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===");
    }
}
