package pl.edu.zut.wi.po.newmath.tests;

import static org.junit.Assert.*;

import org.junit.Test;

import pl.edu.zut.wi.po.newmath.Circle;

public class CircleTests {

	@Test
	public void testCircumference() {
		assertEquals(12.56, Circle.circumference(2), 0.01);
	}

}
