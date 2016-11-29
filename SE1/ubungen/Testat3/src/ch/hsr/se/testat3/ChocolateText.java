package ch.hsr.se.testat3;

public class ChocolateText extends DecoratedPastry{

	private final String text;
	private final boolean muffin;

	public ChocolateText(Pastry pastry, String text) {
		super(pastry);
		assertDecoratorOnlyOnce();
		this.text = text;
		this.muffin = isMuffin();
		
		if(muffin){
			description = "Karte \"" + text + "\"";
		}else{
			description = "Schrift in Schokolade \"" + text + "\"";				
		}
	}

	private void assertDecoratorOnlyOnce() {
		Pastry current = pastry;
		while(current instanceof DecoratedPastry){
			if(current instanceof ChocolateText){
				throw new IllegalArgumentException("You can only have one Choco text :( ");
			}
			current = ((DecoratedPastry)current).pastry;
		}
		
	}

	@Override
	public double getPrice() {
		if(text.contains("Geburtstag")){
			return pastry.getPrice();
		}
		
		if(muffin){
			return pastry.getPrice() + 8;
		}
		
		return pastry.getPrice() + 10;
	}
	
	public String getText() {
		return text;
	}

	private boolean isMuffin(){
		Pastry current = pastry;
		while(current instanceof DecoratedPastry){
			current = ((DecoratedPastry)current).pastry;
		}
		return current instanceof MuffinSet;
	}
}
