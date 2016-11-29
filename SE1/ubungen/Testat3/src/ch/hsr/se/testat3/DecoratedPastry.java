package ch.hsr.se.testat3;

public abstract class DecoratedPastry extends Pastry{
	protected Pastry pastry;
	
	public DecoratedPastry(Pastry pastry) {
		this.pastry = pastry;
	}
	
	@Override
	public String getDescription() {
		return pastry.getDescription() + ", " + description;
	}
	
}
