package src;

public class EconomyTariff extends Tariff {
    private static final double VOLUME_RATE = 0.05;
    private static final double WEIGHT_RATE = 30.0;

    public EconomyTariff(String name, double basePrice) {
        super(name, basePrice);
    }

    @Override
    public double calculateCost(Parcel parcel, Address from, Address to) {
        return basePrice + parcel.calculateVolume() * VOLUME_RATE + parcel.getWeight() * WEIGHT_RATE;
    }
}