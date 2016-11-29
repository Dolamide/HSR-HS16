package ch.hsr.se.testat3;

public class WhippedCream extends DecoratedPastry{
	
	public WhippedCream(Pastry pastry) {
		super(pastry);
		description = "Schlagrahm-Deko";
	}

	@Override
	public double getPrice() {
		return pastry.getPrice() + 4.50;
	}

}
