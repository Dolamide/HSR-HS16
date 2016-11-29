package ch.hsr.se.testat3;

import static org.junit.Assert.*;

import org.junit.Test;

import ch.hsr.se.testat3.DecorationElement.DecorationElementType;

public class PastryTest {

	@Test
	public void testSimpleDecorationDescription() {
		Pastry cake = new SquareCake();
		cake = new ChocolateSprinkles(cake);
		assertEquals("Cake (Kastenform), Schokoladen-Streusel", cake.getDescription());
	}
	
	@Test
	public void testChocolateTextDecorationDescription() {
		Pastry cake = new SquareCake();
		cake = new ChocolateText(cake, "Hey Joe!");
		assertEquals("Cake (Kastenform), Schrift in Schokolade \"Hey Joe!\"",
					  cake.getDescription());
	}
		
	@Test
	public void testSimpleDecorationPrice() {
		Pastry cake = new RoundCake();
		cake = new ChocolateSprinkles(cake);
		assertEquals(23.5, cake.getPrice(), 0.005);
	}
	
	@Test
	public void testChocolateTextDecorationPrice() {
		Pastry cake = new SquareCake();
		cake = new ChocolateText(cake, "Hey Joe!");
		assertEquals(26, cake.getPrice(), 0.005);
	}
	
	@Test
	public void testChocolateTextDecorationPriceFreeForBirthday() {
		Pastry cake = new SquareCake();
		cake = new ChocolateText(cake, "Alles Gute zum Geburtstag!");
		assertEquals(16, cake.getPrice(), 0.005);
	}
	
	@Test
	public void testChocolateTextDecorationPriceForMuffins() {
		Pastry cake = new MuffinSet();
		cake = new ChocolateText(cake, "Hey Joe!");
		assertEquals(27, cake.getPrice(), 0.005);
	}
	
	@Test
	public void testAgeDiscountDecorationPrice() {
		Pastry cake = new RoundCake();
		cake = new ChocolateSprinkles(cake);
		cake = new AgeDiscount(cake);
		assertEquals(18.8, cake.getPrice(), 0.005);
	}
	
	@Test
	public void testDecorationElementDecorationDescription() {
		Pastry cake = new SquareCake();
		cake = new DecorationElement(cake, DecorationElementType.FOOTBALL);
		assertEquals("Cake (Kastenform), Dekorationselement \"Fussball\" aus Zuckerguss",
					  cake.getDescription());
	}
	
	@Test
	public void testChocolateTextCanOnlyBeDecoratedOnce() {
		Pastry cake = new SquareCake();
		cake = new ChocolateText(cake, "Once!");
		try{
			cake = new ChocolateText(cake, "Twice!");
			fail("Decorate twice with ChocolateText should not be allowed!");
		}catch (Exception e) {
			// Expected Exception!
		}
	}
	
}
