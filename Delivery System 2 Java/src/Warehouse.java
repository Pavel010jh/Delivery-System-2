package src;

import java.util.ArrayList;
import java.util.List;

public class Warehouse {
    private int id;
    private Address address;
    private String phoneNumber;
    private List<Order> storedOrders;

    // Конструктор
    public Warehouse(int id, Address address, String phoneNumber) {
        this.id = id;
        this.address = address;
        this.phoneNumber = phoneNumber;
        this.storedOrders = new ArrayList<>();
    }

    // Методы
    public void receiveOrder(Order order) {
        storedOrders.add(order);
    }

    // Геттеры
    public int getId() { return id; }
    public Address getAddress() { return address; }
    public String getPhoneNumber() { return phoneNumber; }
}