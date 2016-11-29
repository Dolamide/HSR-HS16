package ch.hsr.se.testat3;

public class ChocolateSprinkles extends DecoratedPastry{

	public ChocolateSprinkles(Pastry pastry) {
		super(pastry);
		description = "Schokoladen-Streusel";
	}

	@Override
	public double getPrice() {
		return pastry.getPrice() + 2.5;
	}

}
