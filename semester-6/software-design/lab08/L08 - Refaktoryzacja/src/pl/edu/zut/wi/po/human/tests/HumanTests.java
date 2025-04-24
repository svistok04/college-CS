package pl.edu.zut.wi.po.human.tests;

import static org.junit.Assert.*;

import org.junit.Test;

import pl.edu.zut.wi.po.human.Human;

public class HumanTests {

	@Test
	public void testGetFullAddress() {
		Human h = new Human("Jan Kowalski", "33", "Polska", "Szczecin", "Langiewicza", "15", "2");
		assertEquals(h.getFullAddress(), "Polska, Szczecin, Langiewicza, 15/2");
	}

}
