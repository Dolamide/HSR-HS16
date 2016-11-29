package ch.hsr.se.testat3;

public abstract class Pastry {
	
	protected String description = "Unknown Pastry";

	public String getDescription(){
		return description;
	}
	
	public abstract double getPrice();
}
