package ch.hsr.se.testat3;

public class DecorationElement extends DecoratedPastry {

	public enum DecorationElementType {
		HEART("Herz"),
		STAR("Stern"),
		FIR("Tanne"),
		FOOTBALL("Fussball"),
		FOOTBALL_PLAYER("Fussballspieler"),
		SKIS("Ski"),
		SKIER("Skifahrer");
		
		private final String label;

		private DecorationElementType(String label) {
			this.label = label;
		}
		
		@Override
		public String toString() {
			return label;
		}
	}

	private DecorationElementType type;
	
	public DecorationElement(Pastry pastry, DecorationElementType type) {
		super(pastry);
		this.type = type;
		description = "Dekorationselement \"" + type + "\" aus Zuckerguss";
	}
	
	
	@Override
	public double getPrice() {
		return pastry.getPrice() + 4;
	}
	
	public DecorationElementType getType() {
		return type;
	}
		
}
