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
        System.out.println("=== System Information (using this) ===");
        System.out.println("Version: " + DeliverySystem.getSystemVersion());
        System.out.println("Total orders in this system: " + this.allOrders.size());
        System.out.println("Total clients: " + this.allClients.size());
        System.out.println("Total couriers: " + this.allCouriers.size());
        System.out.println("Global order count: " + DeliverySystem.getGlobalOrderCount());
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
}