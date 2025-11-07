package src;

import java.util.ArrayList;
import java.util.List;

public class Client {
    private int id;
    private String name;
    private String phoneNumber;
    private String email;
    private List<Address> addresses;
    private List<Order> orderHistory;

    // Конструктор
    public Client(int id, String name, String phoneNumber, String email) {
        this.id = id;
        this.name = name;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.addresses = new ArrayList<>();
        this.orderHistory = new ArrayList<>();
    }

    // Методы
    public void addAddress(Address newAddress) {
        addresses.add(newAddress);
    }

    public void addToHistory(Order order) {
        orderHistory.add(order);
    }

    // Геттеры
    public int getId() { return id; }
    public String getName() { return name; }
    public String getPhoneNumber() { return phoneNumber; }
    public String getEmail() { return email; }
    public List<Address> getAddresses() { return addresses; }
}