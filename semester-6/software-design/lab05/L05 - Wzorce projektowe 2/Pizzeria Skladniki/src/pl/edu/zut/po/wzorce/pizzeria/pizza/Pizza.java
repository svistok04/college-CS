package pl.edu.zut.po.wzorce.pizzeria.pizza;

import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ciasto;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Malze;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Pepperoni;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ser;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Sos;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Warzywa;

import java.util.List;
import java.util.stream.Collectors;

public abstract class Pizza {
	String nazwa;
	Ciasto ciasto;
	Sos sos;
	protected List<Ser> sery;
	protected List<Warzywa> warzywa;
	Pepperoni pepperoni;
	Malze malze;

	public abstract void przygotowanie();

	public void pieczenie() {
		System.out.println("Pieczenie: 25 minut w temperaturze 180 stopni Celsjusza");
	}

	public void krojenie() {
		System.out.println("Krojenie pizzy na 8 kawałków");
	}

	public void pakowanie() {
		System.out.println("Pakowanie pizzy w oficjalne pudełko naszej sieci Pizzerii.");
	}

	public void ustawNazwa(String nazwa) {
		this.nazwa = nazwa;
	}

	public String pobierzNazwa() {
		return nazwa;
	}

	public String toString() {
		// kod wyświetlający informacje o pizzy
		String warz = "brak";
		if (warzywa != null && !warzywa.isEmpty()) {
			warz = warzywa.stream()
					.map(w -> w.getClass().getSimpleName())
					.collect(Collectors.joining(", "));
		}


		String seryStr = "brak";
		if (sery != null && !sery.isEmpty()) {
			seryStr = sery.stream()
					.map(s -> s.getClass().getSimpleName())
					.collect(Collectors.joining(", "));
		}

		String info = String.format("%s\n"
				+ "ciasto: %s\n"
				+ "sos: %s\n"
				+ "warzywa: %s\n"
				+ "ser: %s\n"
				+ "pepperoni: %s\n"
				+ "małże: %s", 
				nazwa,
				ciasto == null ? "brak" : ciasto.getClass().getSimpleName(),
				sos == null ? "brak" : sos.getClass().getSimpleName(),
				warz,
				seryStr,
				pepperoni == null ? "brak" : pepperoni.getClass().getSimpleName(),
				malze == null ? "brak" : malze.getClass().getSimpleName()); 
		return info;
	}
}