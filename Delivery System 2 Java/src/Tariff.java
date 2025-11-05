package src;

public abstract class Tariff {
    protected String name;
    protected double basePrice;

    public Tariff(String name, double basePrice) {
        this.name = name;
        this.basePrice = basePrice;
    }

    // Абстрактный метод расчета стоимости
    public abstract double calculateCost(Parcel parcel, Address from, Address to);

    // Геттеры
    public String getName() { return name; }
    public double getBasePrice() { return basePrice; }
}