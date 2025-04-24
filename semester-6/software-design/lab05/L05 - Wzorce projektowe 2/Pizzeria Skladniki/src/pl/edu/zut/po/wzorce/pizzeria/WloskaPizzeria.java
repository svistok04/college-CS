package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.FabrykaSkladnikowPizzy;
import pl.edu.zut.po.wzorce.pizzeria.fabryka.WloskaFabrykaSkladnikowPizzy;
import pl.edu.zut.po.wzorce.pizzeria.pizza.OwoceMorzaPizza;
import pl.edu.zut.po.wzorce.pizzeria.pizza.PepperoniPizza;
import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;
import pl.edu.zut.po.wzorce.pizzeria.pizza.SerowaPizza;
import pl.edu.zut.po.wzorce.pizzeria.pizza.WegetarianskaPizza;

public class WloskaPizzeria extends Pizzeria {
	@Override
	protected Pizza utworzPizza(String type) {
		FabrykaSkladnikowPizzy fabryka = new WloskaFabrykaSkladnikowPizzy();
		Pizza pizza = null;
		switch (type) {
			case "serowa":
				pizza = new SerowaPizza(fabryka);
				pizza.ustawNazwa("Włoska Pizza Serowa");
				break;
			case "wegetariańska":
				pizza = new WegetarianskaPizza(fabryka);
				pizza.ustawNazwa("Włoska Pizza Wegetariańska");
				break;
			case "owoce morza":
				pizza = new OwoceMorzaPizza(fabryka);
				pizza.ustawNazwa("Włoska Pizza Owoce Morza");
				break;
			case "pepperoni":
				pizza = new PepperoniPizza(fabryka);
				pizza.ustawNazwa("Włoska Pizza Pepperoni");
				break;
		}
		return pizza;
	}
}