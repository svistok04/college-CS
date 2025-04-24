package pl.edu.zut.po.wzorce.cafe;

import pl.edu.zut.po.wzorce.cafe.napoje.*;
import pl.edu.zut.po.wzorce.cafe.skladniki.*;

public class StarCafe {
	public static void main(String... params) {
//		MocnoPalona napoj = new MocnoPalona();
//		System.out.println(napoj.pobierzOpis() + " " + napoj.koszt() + "zł");

		Napoj napój1 = new MocnoPalona();
		napój1 = new Czekolada(napój1);
		napój1 = new BitaSmietana(napój1);

		System.out.println("Zamówienie 1:");
		System.out.println(napój1.pobierzOpis() + " " + String.format("%.2f", napój1.koszt()) + " zł\n");

		Napoj napój2 = new Bezkofeinowa();
		napój2 = new Mleko(napój2);
		napój2 = new Mleko(napój2);

		System.out.println("Zamówienie 2:");
		System.out.println(napój2.pobierzOpis() + " " + String.format("%.2f", napój2.koszt()) + " zł");


	}
}
