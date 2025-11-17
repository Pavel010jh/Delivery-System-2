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

        // Статическое поле
    private static int clientCounter = 0;
    private static final int MAX_CLIENTS = 1000;

    // Конструктор
    public Client(int id, String name, String phoneNumber, String email) {
        // Использование this для разрешения конфликта имен
        this.id = id;
        this.name = name;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.addresses = new ArrayList<>();
        this.orderHistory = new ArrayList<>();
        clientCounter++;
    }

        // Статический метод
    public static int getClientCounter() {
        return clientCounter;
    }
    
    public static boolean canCreateMoreClients() {
        return clientCounter < MAX_CLIENTS;
    }
    
    public static void resetCounter() {
        clientCounter = 0;
    }

    // Методы с использованием this
    public void updateContactInfo(String phoneNumber, String email) {
        this.phoneNumber = phoneNumber;
        this.email = email;
    }
    
    public Client getCurrentClient() {
        return this;
    }
    
    public void printClientInfo() {
        System.out.println("Client Info (using this):");
        System.out.println("  ID: " + this.id);
        System.out.println("  Name: " + this.name);
        System.out.println("  Phone: " + this.phoneNumber);
        System.out.println("  Email: " + this.email);
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