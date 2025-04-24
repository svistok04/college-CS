package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.pizza.*;

public class ProstaFabrykaPizzy {
	public Pizza utworzPizze(String type) {
		Pizza pizza = null;
		if (type.equals("serowa")) {
			pizza = new SerowaPizza();
		} else if (type.equals("grecka")) {
			pizza = new GreckaPizza();
		} else if (type.equals("pepperoni")) {
			pizza = new PepperoniPizza();
		} else if (type.equals("owocemorza")) {
			pizza = new OwoceMorzaPizza();
		} else if (type.equals("wegetariańska")) {
			pizza = new WegetarianskaPizza();
		}
		return pizza;
	}
}