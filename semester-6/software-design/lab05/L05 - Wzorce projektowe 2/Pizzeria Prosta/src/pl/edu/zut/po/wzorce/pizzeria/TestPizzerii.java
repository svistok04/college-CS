package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.ProstaFabrykaPizzy;
import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		ProstaFabrykaPizzy fabryka = new ProstaFabrykaPizzy();
		Pizzeria pizzeria = new Pizzeria(fabryka);
		Pizza pizza = pizzeria.zamowPizze("serowa");
		System.out.println(pizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName());


	}
}
