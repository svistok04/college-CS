package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.ProstaFabrykaPizzy;
import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;

public class Pizzeria {
	private ProstaFabrykaPizzy fabryka;

	public Pizzeria(ProstaFabrykaPizzy fabryka) {
		this.fabryka = fabryka;
	}

	public Pizza zamowPizze(String type) {
		Pizza pizza = fabryka.utworzPizze(type);
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}

}
