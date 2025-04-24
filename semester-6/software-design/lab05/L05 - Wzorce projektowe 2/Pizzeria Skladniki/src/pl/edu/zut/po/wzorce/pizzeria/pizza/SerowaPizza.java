package pl.edu.zut.po.wzorce.pizzeria.pizza;

import pl.edu.zut.po.wzorce.pizzeria.fabryka.FabrykaSkladnikowPizzy;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.*;

import java.util.stream.Collectors;

public class SerowaPizza extends Pizza {
	FabrykaSkladnikowPizzy fabrykaSkladnikow;

	public SerowaPizza(FabrykaSkladnikowPizzy fabrykaSkladnikow) {
		this.fabrykaSkladnikow = fabrykaSkladnikow;
		this.nazwa = "Pizza Serowa";
	}

	@Override
	public void przygotowanie() {
		System.out.println("Przygotowywanie: " + nazwa);
		ciasto = fabrykaSkladnikow.utworzCiasto();
		sos = fabrykaSkladnikow.utworzSos();
		sery = fabrykaSkladnikow.utworzSer().stream()
				.filter(s -> s instanceof SerMozarella || s instanceof SerParmezan || s instanceof SerReggiano)
				.collect(Collectors.toList());
	}
}
