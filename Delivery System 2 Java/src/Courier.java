package src;

import java.util.ArrayList;
import java.util.List;

public class Courier {
    private int id;
    private String name;
    private String phoneNumber;
    private String vehicleType;
    private boolean isAvailable;
    private List<Order> currentOrders;

    // Конструктор
    public Courier(int id, String name, String phoneNumber, String vehicleType, boolean isAvailable) {
        this.id = id;
        this.name = name;
        this.phoneNumber = phoneNumber;
        this.vehicleType = vehicleType;
        this.isAvailable = isAvailable;
        this.currentOrders = new ArrayList<>();
    }

    // Методы
    public boolean assignOrder(Order order) {
        if (!isAvailable) return false;
        currentOrders.add(order);
        return true;
    }

    // Геттеры
    public int getId() { return id; }
    public String getName() { return name; }
    public String getPhoneNumber() { return phoneNumber; }
    public String getVehicleType() { return vehicleType; }
    public boolean getIsAvailable() { return isAvailable; }
}