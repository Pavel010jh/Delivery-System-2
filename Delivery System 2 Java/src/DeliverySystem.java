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

    // Конструктор
    public DeliverySystem() {
        this.allOrders = new ArrayList<>();
        this.allCouriers = new ArrayList<>();
        this.allClients = new ArrayList<>();
        this.allWarehouses = new ArrayList<>();
        this.availableTariffs = new ArrayList<>();
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