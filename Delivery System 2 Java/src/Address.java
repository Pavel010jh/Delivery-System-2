package src;

public class Address {
    private String street;
    private String city;
    private String postalCode;

    // Конструкторы
    public Address() {}

    public Address(String street, String city, String postalCode) {
        this.street = street;
        this.city = city;
        this.postalCode = postalCode;
    }

    // Методы
    public String getFullAddress() {
        return street + ", " + city + ", " + postalCode;
    }

    // Геттеры
    public String getStreet() { return street; }
    public String getCity() { return city; }
    public String getPostalCode() { return postalCode; }
}