package ch.hsr.se.testat3;

public class AgeDiscount extends DecoratedPastry{

	public AgeDiscount(Pastry pastry) {
		super(pastry);
		description = "Altersrabatt";
	}

	@Override
	public double getPrice() {
		return pastry.getPrice() * 0.8;
	}

}
