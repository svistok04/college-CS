package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;

public abstract class Pizzeria {
	public Pizza zamowPizze(String type) {
		Pizza pizza = utworzPizza(type);
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}
	protected abstract Pizza utworzPizza(String type);
}