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

    // Конструктор с валидацией
    public Order(String trackingNumber, Address fromAddress, Address toAddress, 
             Parcel parcel, Tariff tariff) {
    // Валидация в конструкторе
    if (trackingNumber == null || !trackingNumber.startsWith("TRK")) {
        throw new IllegalArgumentException("Неверный формат трек-номера. Должен начинаться с 'TRK'");
    }
    
    if (fromAddress == null || toAddress == null) {
        throw new IllegalArgumentException("Адреса не могут быть пустыми");
    }
    
    if (parcel == null) {
        throw new IllegalArgumentException("Посылка не может быть пустой");
    }
    
    if (tariff == null) {
        throw new IllegalArgumentException("Тариф не может быть пустым");
    }


        this.trackingNumber = trackingNumber;
        this.status = OrderStatus.CREATED;
        this.fromAddress = fromAddress;
        this.toAddress = toAddress;
        this.parcel = parcel;
        this.chosenTariff = tariff;
        calculateFinalCost();
    }

// Метод с проверкой и исключением
public void assignCourierWithValidation(Courier courier) throws IllegalStateException {
    if (courier == null) {
        throw new IllegalArgumentException("Курьер не может быть пустым");
    }
    
    if (this.status != OrderStatus.CREATED) {
        throw new IllegalStateException("Нельзя назначить курьера для заказа со статусом: " + this.status);
    }
    
    if (!courier.getIsAvailable()) {
        throw new IllegalStateException("Курьер недоступен");
    }
    
    if (courier.assignOrder(this)) {
        this.assignedCourier = courier;
        updateStatus(OrderStatus.IN_PROGRESS);
    } else {
        throw new IllegalStateException("Не удалось назначить курьера на заказ");
    }
}

// Методы с использованием this для цепочки вызовов
public Order updateContactInfoAndReturn() {
    // Демонстрация возврата this
    return this;
}

public void printOrderDetails() {
    System.out.println("=== Информация о заказе (использование this) ===");
    System.out.println("Трек номер: " + this.trackingNumber);
    System.out.println("Статус: " + this.status);
    System.out.println("Итоговая стоимость: " + this.finalCost + " руб.");
    System.out.println("Откуда: " + this.fromAddress.getFullAddress());
    System.out.println("Куда: " + this.toAddress.getFullAddress());
    System.out.println("Посылка: " + this.parcel.getDescription());
    if (this.assignedCourier != null) {
        System.out.println("Назначенный курьер: " + this.assignedCourier.getName());
    }
}

// Методы с обработкой исключений для статуса
public void updateStatusWithValidation(OrderStatus newStatus) throws IllegalStateException {
    if (this.status == OrderStatus.DELIVERED && newStatus != OrderStatus.DELIVERED) {
        throw new IllegalStateException("Нельзя изменить статус доставленного заказа");
    }
    
    if (this.status == OrderStatus.CREATED && newStatus == OrderStatus.DELIVERED) {
        throw new IllegalStateException("Нельзя пометить заказ как доставленный без статуса 'В процессе'");
    }
    
    if (newStatus == OrderStatus.IN_PROGRESS && this.assignedCourier == null) {
        throw new IllegalStateException("Нельзя установить статус 'В процессе' без назначенного курьера");
    }
    
    this.status = newStatus;
}

// Метод с try-catch для безопасного обновления
public boolean safeStatusUpdate(OrderStatus newStatus) {
    try {
        updateStatusWithValidation(newStatus);
        return true;
    } catch (IllegalStateException e) {
        System.err.println("Обновление статуса не удалось: " + e.getMessage());
        return false;
    }
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
    public Tariff getChosenTariff() { return chosenTariff; }

    // Метод для проверки валидности заказа
public void validateOrder() throws IllegalArgumentException {
    if (trackingNumber == null || trackingNumber.trim().isEmpty()) {
        throw new IllegalArgumentException("Трек-номер не может быть пустым");
    }
    
    if (finalCost < 0) {
        throw new IllegalArgumentException("Итоговая стоимость не может быть отрицательной");
    }
    
    if (fromAddress == null || toAddress == null) {
        throw new IllegalArgumentException("Адреса не могут быть пустыми");
    }
    
    if (parcel == null) {
        throw new IllegalArgumentException("Посылка не может быть пустой");
    }
    
    if (chosenTariff == null) {
        throw new IllegalArgumentException("Тариф не может быть пустым");
    }
}

// Метод для получения строкового представления статуса
public String getStatusString() {
    switch (this.status) {
        case CREATED: return "Создан";
        case IN_PROGRESS: return "В процессе";
        case DELIVERED: return "Доставлен";
        default: return "Неизвестен";
    }
}

@Override
public String toString() {
    return "Заказ{трекНомер='" + trackingNumber + 
           "', статус=" + getStatusString() + 
           ", стоимость=" + finalCost + " руб." + 
           ", курьер=" + (assignedCourier != null ? assignedCourier.getName() : "не назначен") + "}";
}
}