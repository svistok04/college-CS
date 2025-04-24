package pl.edu.zut.po.wzorce.pizzeria.pizza;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.FabrykaSkladnikowPizzy;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.*;

import java.util.stream.Collectors;

public class WegetarianskaPizza extends Pizza {
	FabrykaSkladnikowPizzy fabrykaSkladnikow;

	public WegetarianskaPizza(FabrykaSkladnikowPizzy fabrykaSkladnikow) {
		this.fabrykaSkladnikow = fabrykaSkladnikow;
		this.nazwa = "Pizza Wegetariańska";
	}

	@Override
	public void przygotowanie() {
		System.out.println("Przygotowywanie: " + nazwa);
		ciasto = fabrykaSkladnikow.utworzCiasto();
		sos = fabrykaSkladnikow.utworzSos();
		sery = fabrykaSkladnikow.utworzSer().stream()
				.filter(s -> s instanceof SerMozarella || s instanceof SerParmezan)
				.collect(Collectors.toList());

		warzywa = fabrykaSkladnikow.utworzWarzywa();
	}
}
