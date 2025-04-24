package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.skladniki.Cebula;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ciasto;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.CienkieChrupkieCiasto;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.CzerwonaPapryka;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Czosnek;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Malze;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Pepperoni;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Pieczarki;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.PlastryPepperoni;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ser;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.SerReggiano;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Sos;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.SosMarinara;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.SwiezeMalze;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Warzywa;

import java.util.List;

public class WloskaFabrykaSkladnikowPizzy implements FabrykaSkladnikowPizzy {
	public Ciasto utworzCiasto() {
		return new CienkieChrupkieCiasto();
	}

	public Sos utworzSos() {
		return new SosMarinara();
	}

	public List<Ser> utworzSer() {
		return List.of(new SerReggiano());
	}

	public List<Warzywa> utworzWarzywa() {
		return List.of(
				new Czosnek(),
				new Cebula(),
				new Pieczarki(),
				new CzerwonaPapryka()
		);
	}

	public Pepperoni utworzPepperoni() {
		return new PlastryPepperoni();
	}

	public Malze utworzMalze() {
		return new SwiezeMalze();
	}
}