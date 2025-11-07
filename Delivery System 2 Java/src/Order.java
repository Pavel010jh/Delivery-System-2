package src;

public final class Order {
    private final String trackingNumber;
    private OrderStatus status;
    private double finalCost;
    private final Address fromAddress;
    private final Address toAddress;
    private final Parcel parcel;
    private Courier assignedCourier;
    private final Tariff chosenTariff;

    // Конструктор
    public Order(String trackingNumber, Address fromAddress, Address toAddress, 
                 Parcel parcel, Tariff tariff) {
        this.trackingNumber = trackingNumber;
        this.status = OrderStatus.CREATED;
        this.fromAddress = fromAddress;
        this.toAddress = toAddress;
        this.parcel = parcel;
        this.chosenTariff = tariff;
        calculateFinalCost();
    }

    // Методы
    public void updateStatus(OrderStatus newStatus) {
        this.status = newStatus;
    }

    public void assignCourier(Courier courier) {
        if (courier != null && courier.assignOrder(this)) {
            this.assignedCourier = courier;
            updateStatus(OrderStatus.IN_PROGRESS);
        }
    }

    public void calculateFinalCost() {
        if (chosenTariff != null) {
            finalCost = chosenTariff.calculateCost(parcel, fromAddress, toAddress);
        }
    }

    // Геттеры
    public String getTrackingNumber() { return trackingNumber; }
    public OrderStatus getStatus() { return status; }
    public double getFinalCost() { return finalCost; }
    public Courier getAssignedCourier() { return assignedCourier; }
    public Address getFromAddress() { return fromAddress; }
    public Address getToAddress() { return toAddress; }
    public Parcel getParcel() { return parcel; }
}