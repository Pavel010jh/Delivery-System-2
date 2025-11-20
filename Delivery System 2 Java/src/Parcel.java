package src;

public class Parcel {
    private final String description;
    private final double weight;
    private final double length;
    private final double width;
    private final double height;
    private final double estimatedValue;

    // Конструктор
    public Parcel(String description, double weight, double length, 
                  double width, double height, double estimatedValue) {
        this.description = description;
        this.weight = weight;
        this.length = length;
        this.width = width;
        this.height = height;
        this.estimatedValue = estimatedValue;
    }

    // Методы
    public double calculateVolume() {
        return length * width * height;
    }

    // Геттеры
    public String getDescription() { return description; }
    public double getWeight() { return weight; }
    public double getLength() { return length; }
    public double getWidth() { return width; }
    public double getHeight() { return height; }
    public double getEstimatedValue() { return estimatedValue; }
}