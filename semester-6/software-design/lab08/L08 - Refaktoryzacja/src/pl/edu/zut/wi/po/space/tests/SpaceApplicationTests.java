package pl.edu.zut.wi.po.space.tests;

import static org.junit.Assert.*;

import org.junit.Test;

import pl.edu.zut.wi.po.space.Person;
import pl.edu.zut.wi.po.space.Ship;
import pl.edu.zut.wi.po.space.Space;

public class SpaceApplicationTests {

	@Test
	public void test() {
		Space space = new Space();
		space.setDefaultOwner(new Person("Martin", "Fowler"));
		Ship spaceShip = new Ship(space.getDefaultOwner());
		assertEquals("Martin", spaceShip.getOwner().getFirstName());
		assertEquals("Fowler", spaceShip.getOwner().getLastName());
	}

}
