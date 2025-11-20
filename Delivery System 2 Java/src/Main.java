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
        Locale.setDefault(new Locale("ru", "RU"));
        
        System.out.println("=== ДЕМОНСТРАЦИЯ ===");

        try {
            System.out.println("1. ДЕМОНСТРАЦИЯ ИСПОЛЬЗОВАНИЯ OPERATOR THIS:");
            
            Client client1 = new Client(1, "Иван Иванов", "+79161112233", "ivan@mail.com");
            
            // Демонстрация this в методах
            System.out.println("   - Client.printClientInfo() использует this для доступа к полям:");
            client1.printClientInfo();
            
            System.out.println("   - Client.getCurrentClient() возвращает this:");
            Client currentClient = client1.getCurrentClient();
            System.out.println("     Текущий объект: " + currentClient.getName());
            
            // Демонстрация this в цепочке вызовов
            System.out.println("   - Order.updateContactInfoAndReturn() возвращает this для цепочки:");
            Order testOrder = new Order("TRKTEST", 
                new Address("ул. Пушкина 1", "Москва", "101000"),
                new Address("ул. Малахова 2", "Москва", "102000"),
                new Parcel("Посылка", 1.0, 10, 10, 10, 100),
                new ExpressTariff("Посылка", 100.0));
            testOrder.updateContactInfoAndReturn().printOrderDetails();

            System.out.println("\n2. ДЕМОСТРАЦИЯ СТАТИЧЕСКИХ ПОЛЕЙ И МЕТОДОВ:");
            
            System.out.println("   - Статические поля до создания объектов:");
            System.out.println("     Client.getClientCounter(): " + Client.getClientCounter());
            System.out.println("     DeliverySystem.getGlobalOrderCount(): " + DeliverySystem.getGlobalOrderCount());
            System.out.println("     DeliverySystem.getSystemVersion(): " + DeliverySystem.getSystemVersion());
            
            // Создаем объекты для демонстрации изменения статических счетчиков
            Client client2 = new Client(2, "Петр Петров", "+79262223344", "petr@mail.com");
            Client client3 = new Client(3, "Анна Сидорова", "+79363334455", "anna@mail.com");
            
            System.out.println("   - Статические поля после создания объектов:");
            System.out.println("     Client.getClientCounter(): " + Client.getClientCounter());
            System.out.println("     Client.canCreateMoreClients(): " + Client.canCreateMoreClients());
            
            DeliverySystem system = new DeliverySystem();
            system.addClient(client1);
            system.addClient(client2);
            system.addClient(client3);
            
            // Создаем заказы для демонстрации глобального счетчика
            ExpressTariff express = new ExpressTariff("Экспресс", 350.00);
            Address from = new Address("ул. Отправления 10", "Москва", "101100");
            Address to = new Address("ул. Доставки 20", "Москва", "101200");
            Parcel parcel = new Parcel("Документы", 1.5, 35, 25, 5, 2000);
            
            Order order1 = system.createOrder(client1, client2, from, to, parcel, express);
            Order order2 = system.createOrder(client2, client3, from, to, parcel, express);
            
            System.out.println("   - Статические поля после создания заказов:");
            System.out.println("     DeliverySystem.getGlobalOrderCount(): " + DeliverySystem.getGlobalOrderCount());
            
            // Демонстрация статических методов в DeliverySystem
            System.out.println("   - DeliverySystem.printSystemInfo() использует статические методы:");
            system.printSystemInfo();

            System.out.println("\n3. ДЕМОНСТРАЦИЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ:");
            
            // 3.1 Try-catch блоки с пользовательскими исключениями
            System.out.println("   3.1 Try-catch с пользовательскими исключениями:");
            try {
                Address invalidAddress = new Address("", "Москва", "101000");
                system.createOrderWithValidation(client1, null, invalidAddress, to, parcel, express);
            } catch (InvalidAddressException e) {
                System.out.println("      Поймано InvalidAddressException: " + e.getMessage());
            } catch (InvalidParcelException e) {
                System.out.println("      Поймано InvalidParcelException: " + e.getMessage());
            }
            
            // 3.2 Try-catch блоки с встроенными исключениями
            System.out.println("\n   3.2 Try-catch с IllegalArgumentException:");
            try {
                Parcel invalidParcel = new Parcel("Невалидная", -5.0, 10, 10, 10, 100);
                system.createOrderWithValidation(client1, null, from, to, invalidParcel, express);
            } catch (InvalidParcelException e) {
                System.out.println("      Поймано InvalidParcelException: " + e.getMessage());
            } catch (Exception e) {
                System.out.println("      Поймано исключение: " + e.getMessage());
            }
            
            // 3.3 Throw инструкции в конструкторах
            System.out.println("\n   3.3 Throw в конструкторе Order:");
            try {
                Order invalidOrder = new Order("INVALID", null, to, parcel, express);
            } catch (IllegalArgumentException e) {
                System.out.println("      Поймано IllegalArgumentException из конструктора: " + e.getMessage());
            }
            
            // 3.4 Throw инструкции в методах
            System.out.println("\n   3.4 Throw в методе assignCourierWithValidation:");
            try {
                // Создаем недоступного курьера
                Courier busyCourier = new Courier(99, "Занятый Курьер", "+79999999999", "автомобиль", false);
                order1.assignCourierWithValidation(busyCourier);
            } catch (IllegalStateException e) {
                System.out.println("      Поймано IllegalStateException: " + e.getMessage());
            }
            
            // 3.5 Безопасная обработка через processOrderSafely
            System.out.println("\n   3.5 Безопасная обработка через processOrderSafely:");
            System.out.println("     Вызов system.processOrderSafely() с невалидными данными:");
            system.processOrderSafely(client1, null, from, to, 
                new Parcel("", -1.0, 0, 0, 0, 0), express);

            // 3.6 Исключения при поиске
            System.out.println("\n   3.6 Исключения при поиске несуществующих объектов:");
            try {
                system.findClientById(9999);
            } catch (ClientNotFoundException e) {
                System.out.println("      Поймано ClientNotFoundException: " + e.getMessage());
            }
            
            try {
                system.findAvailableCourier(); // Нет курьеров в системе
            } catch (NoAvailableCourierException e) {
                System.out.println("      Поймано NoAvailableCourierException: " + e.getMessage());
            }

            System.out.println("\n4. ФИНАЛЬНАЯ ДЕМОНСТРАЦИЯ РАБОТЫ СИСТЕМЫ:");
            
            // Добавляем доступного курьера
            Courier availableCourier = new Courier(4, "Алексей Доступный", "+79464445566", "автомобиль", true);
            system.addCourier(availableCourier);
            
            // Создаем валидный заказ
            Order validOrder = system.createOrderWithValidation(client1, client2, from, to, parcel, express);
            validOrder.assignCourierWithValidation(availableCourier);
            
            System.out.println("   - Успешно создан заказ: " + validOrder.getTrackingNumber());
            System.out.println("   - Статус: " + statusToString(validOrder.getStatus()));
            System.out.println("   - Стоимость: " + validOrder.getFinalCost() + " руб.");
            System.out.println("   - Курьер: " + validOrder.getAssignedCourier().getName());

            System.out.println("\n=== ИТОГОВАЯ СТАТИСТИКА ===");
            System.out.println("Всего клиентов в системе: " + Client.getClientCounter());
            System.out.println("Глобальных заказов создано: " + DeliverySystem.getGlobalOrderCount());
            System.out.println("Заказов в текущей системе: " + system.getAllOrders().size());

        } catch (Exception e) {
            System.err.println("КРИТИЧЕСКАЯ ОШИБКА: " + e.getMessage());
            e.printStackTrace();
            return;
        }
    }
}
