package pl.edu.zut.po.wzorce.pizzeria.pizza;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.FabrykaSkladnikowPizzy;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.*;

public class OwoceMorzaPizza extends Pizza {
	FabrykaSkladnikowPizzy fabrykaSkladnikow;

	public OwoceMorzaPizza(FabrykaSkladnikowPizzy fabrykaSkladnikow) {
		this.fabrykaSkladnikow = fabrykaSkladnikow;
	}

	public void przygotowanie() {
		System.out.println("Przygotowywanie: " + nazwa);
		ciasto = fabrykaSkladnikow.utworzCiasto();
		sos = fabrykaSkladnikow.utworzSos();
		sery = fabrykaSkladnikow.utworzSer().stream()
				.filter(s -> s instanceof SerMozarella || s instanceof SerParmezan)
				.toList();
		malze = fabrykaSkladnikow.utworzMalze();
	}
}