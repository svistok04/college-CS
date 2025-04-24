package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.*;
import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {
	public static void main(String[] args) {
		Pizzeria amerykanska = new AmerykanskaPizzeria();
		Pizzeria wloska = new WloskaPizzeria();

		Pizza p1 = amerykanska.zamowPizze("pepperoni");
		System.out.println(amerykanska.getClass().getSimpleName() + " wyprodukowała " + p1.getClass().getSimpleName());

		Pizza p2 = wloska.zamowPizze("pepperoni");
		System.out.println(wloska.getClass().getSimpleName() + " wyprodukowała " + p2.getClass().getSimpleName());

		Pizza p3 = amerykanska.zamowPizze("serowa");
		System.out.println(amerykanska.getClass().getSimpleName() + " wyprodukowała " + p3.getClass().getSimpleName());

		Pizza p4 = wloska.zamowPizze("serowa");
		System.out.println(wloska.getClass().getSimpleName() + " wyprodukowała " + p4.getClass().getSimpleName());

	}
}
