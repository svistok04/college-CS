package pl.edu.zut.po.wzorce.pizzeria;

import pl.edu.zut.po.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		WloskaPizzeria pizzeria1 = new WloskaPizzeria();
		AmerykanskaPizzeria pizzeria2 = new AmerykanskaPizzeria();

		String[] typyPizz = {
				"serowa",
				"wegetariańska",
				"owoce morza",
				"pepperoni"
		};

		System.out.println("Test Włoska Pizzeria");
		for (String typ : typyPizz) {
			Pizza pizza = pizzeria1.zamowPizze(typ);
			System.out.println(pizza);
			System.out.println();
		}

		System.out.println("Test Amerykanska Pizzeria");
		for (String typ : typyPizz) {
			Pizza pizza = pizzeria2.zamowPizze(typ);
			System.out.println(pizza);
			System.out.println();
		}

	}
}
