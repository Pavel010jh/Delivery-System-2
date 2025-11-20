package src;

public class ExpressTariff extends Tariff {
    private static final double VOLUME_RATE = 0.1;
    private static final double WEIGHT_RATE = 50.0;

    public ExpressTariff(String name, double basePrice) {
        super(name, basePrice);
    }

    @Override
    public double calculateCost(Parcel parcel, Address from, Address to) {
        return basePrice + parcel.calculateVolume() * VOLUME_RATE + parcel.getWeight() * WEIGHT_RATE;
    }
}