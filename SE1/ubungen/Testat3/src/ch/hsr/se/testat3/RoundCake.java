package ch.hsr.se.testat3;

public class RoundCake extends Pastry{

	public RoundCake() {
		description = "Kuchen (rund, mehrschichtig)";
	}

	@Override
	public double getPrice() {
		return 21;
	}

}
