package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ciasto;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Malze;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Pepperoni;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Ser;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Sos;
import pl.edu.zut.po.wzorce.pizzeria.skladniki.Warzywa;

import java.util.List;

public interface FabrykaSkladnikowPizzy {
	public Ciasto utworzCiasto();

	public Sos utworzSos();

	public List<Ser> utworzSer();

	public List<Warzywa> utworzWarzywa();

	public Pepperoni utworzPepperoni();

	public Malze utworzMalze();
}