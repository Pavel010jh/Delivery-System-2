package src;

import java.util.ArrayList;
import java.util.List;

public class DeliverySystem {
    private List<Order> allOrders;
    private List<Courier> allCouriers;
    private List<Client> allClients;
    private List<Warehouse> allWarehouses;
    private List<Tariff> availableTariffs;
    private static int orderCounter = 0;

    // Статические поля
    private static int globalOrderCount = 0;
    private static final String SYSTEM_VERSION = "1.0.0";

    // Конструктор
    public DeliverySystem() {
        this.allOrders = new ArrayList<>();
        this.allCouriers = new ArrayList<>();
        this.allClients = new ArrayList<>();
        this.allWarehouses = new ArrayList<>();
        this.availableTariffs = new ArrayList<>();
    }

        // Статические методы
    public static int getGlobalOrderCount() {
        return globalOrderCount;
    }
    
    public static String getSystemVersion() {
        return SYSTEM_VERSION;
    }
    
    public static void incrementGlobalOrderCount() {
        globalOrderCount++;
    }
    
    public static void resetGlobalStatistics() {
        globalOrderCount = 0;
    }

    // Метод с использованием this
    public DeliverySystem getSystemInstance() {
        return this;
    }
    
    public void printSystemInfo() {
        System.out.println("=== Информация о системе доставки (использование this) ===");
        System.out.println("Версия системы: " + DeliverySystem.getSystemVersion());
        System.out.println("Всего заказов в этой системе: " + this.allOrders.size());
        System.out.println("Всего клиентов: " + this.allClients.size());
        System.out.println("Всего курьеров: " + this.allCouriers.size());
        System.out.println("Глобальный счетчик заказов: " + DeliverySystem.getGlobalOrderCount());
    }

    // Основные методы
    public Order createOrder(Client sender, Client receiver, Address from, 
                            Address to, Parcel parcel, Tariff tariff) {
        String trackingNumber = "TRK" + (++orderCounter);
        Order newOrder = new Order(trackingNumber, from, to, parcel, tariff);
        
        allOrders.add(newOrder);
        if (sender != null) {
            sender.addToHistory(newOrder);
        }
        
        // Увеличиваем глобальный счетчик
        incrementGlobalOrderCount();

        return newOrder;
    }

        // Методы с обработкой исключений
    public Order createOrderWithValidation(Client sender, Client receiver, Address from, 
                                         Address to, Parcel parcel, Tariff tariff) 
            throws InvalidAddressException, InvalidParcelException {
        
        // Валидация данных
        validateOrderData(from, to, parcel);
        
        if (tariff == null) {
            throw new IllegalArgumentException("Tariff cannot be null");
        }

        String trackingNumber = "TRK" + (++orderCounter);
        Order newOrder = new Order(trackingNumber, from, to, parcel, tariff);
        
        allOrders.add(newOrder);
        if (sender != null) {
            sender.addToHistory(newOrder);
        }
        
        incrementGlobalOrderCount();
        return newOrder;
    }

    // Валидация данных с выбрасыванием исключений
    private void validateOrderData(Address from, Address to, Parcel parcel) 
            throws InvalidAddressException, InvalidParcelException {
        
        // Проверка адресов
        if (from.getStreet() == null || from.getStreet().trim().isEmpty()) {
            throw new InvalidAddressException("Улица отправителя не может быть пустой");
        }
        
        if (to.getStreet() == null || to.getStreet().trim().isEmpty()) {
            throw new InvalidAddressException("Улица получателя не может быть пустой");
        }
        
        if (from.getCity() == null || from.getCity().trim().isEmpty()) {
            throw new InvalidAddressException("Город отправителя не может быть пустым");
        }
        
        if (to.getCity() == null || to.getCity().trim().isEmpty()) {
            throw new InvalidAddressException("Город получателя не может быть пустым");
        }
        
        // Проверка что адреса разные
        if (from.getStreet().equals(to.getStreet()) && from.getCity().equals(to.getCity())) {
            throw new InvalidAddressException("Адреса отправителя и получателя не могут совпадать");
        }
        
        // Проверка посылки
        if (parcel.getWeight() <= 0) {
            throw new InvalidParcelException("Вес посылки должен быть положительным");
        }
        
        if (parcel.getWeight() > 100.0) {
            throw new InvalidParcelException("Вес посылки не может превышать 100 кг");
        }
        
        if (parcel.calculateVolume() <= 0) {
            throw new InvalidParcelException("Объем посылки должен быть положительным");
        }
        
        if (parcel.calculateVolume() > 1000000.0) {
            throw new InvalidParcelException("Объем посылки не может превышать 1 м^3");
        }
        
        if (parcel.getEstimatedValue() < 0) {
            throw new InvalidParcelException("Оценочная стоимость посылки не может быть отрицательной");
        }
    }

    // Поиск с исключением
    public Client findClientById(int id) throws ClientNotFoundException {
        for (Client client : allClients) {
            if (client.getId() == id) {
                return client;
            }
        }
        throw new ClientNotFoundException("Клиент с ID " + id + " не найден");
    }

    public Courier findAvailableCourier() throws NoAvailableCourierException {
        for (Courier courier : allCouriers) {
            if (courier.getIsAvailable()) {
                return courier;
            }
        }
        throw new NoAvailableCourierException("Нет доступных курьеров в системе");
    }

    // Метод с try-catch блоком
    public void processOrderSafely(Client sender, Client receiver, Address from, 
                                  Address to, Parcel parcel, Tariff tariff) {
        try {
            Order order = createOrderWithValidation(sender, receiver, from, to, parcel, tariff);
            System.out.println("Заказ успешно создан: " + order.getTrackingNumber());
            
        } catch (InvalidAddressException e) {
            System.err.println("Ошибка валидации адреса: " + e.getMessage());
        } catch (InvalidParcelException e) {
            System.err.println("Ошибка валидации посылки: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Неожиданная ошибка: " + e.getMessage());
        }
    }

    public List<Order> findOrdersByStatus(OrderStatus status) {
        List<Order> result = new ArrayList<>();
        for (Order order : allOrders) {
            if (order.getStatus() == status) {
                result.add(order);
            }
        }
        return result;
    }

    // Методы добавления сущностей
    public void addClient(Client client) {
        allClients.add(client);
    }

    public void addCourier(Courier courier) {
        allCouriers.add(courier);
    }

    public void addTariff(Tariff tariff) {
        availableTariffs.add(tariff);
    }

    // Геттеры
    public List<Order> getAllOrders() { return allOrders; }
    public List<Courier> getAllCouriers() { return allCouriers; }
    public List<Client> getAllClients() { return allClients; }
    public List<Tariff> getAvailableTariffs() { return availableTariffs; }
}