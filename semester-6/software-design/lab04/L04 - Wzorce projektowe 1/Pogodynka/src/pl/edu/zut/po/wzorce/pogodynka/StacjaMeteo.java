package pl.edu.zut.po.wzorce.pogodynka;

import pl.edu.zut.po.wzorce.pogodynka.wyswietl.IndeksCieplaWyswietlanie;
import pl.edu.zut.po.wzorce.pogodynka.wyswietl.PrognozaWyswietlanie;
import pl.edu.zut.po.wzorce.pogodynka.wyswietl.StatystykaWyswietlanie;
import pl.edu.zut.po.wzorce.pogodynka.wyswietl.WarunkiBiezaceWyswietlanie;

public class StacjaMeteo {

	public static void main(String[] args) {
		DanePogodowe danePogodowe = new DanePogodowe();

		Obserwator prognozaWyswietlanie = new PrognozaWyswietlanie();
		Obserwator statystykaWyswietlanie = new StatystykaWyswietlanie();
		Obserwator warunkiBiezaceWyswietlanie = new WarunkiBiezaceWyswietlanie();

		danePogodowe.zarejestrujObserwatora(prognozaWyswietlanie);
		danePogodowe.zarejestrujObserwatora(statystykaWyswietlanie);
		danePogodowe.zarejestrujObserwatora(warunkiBiezaceWyswietlanie);

		danePogodowe.ustawOdczyty(26.6f, 65, 1013.1f);

		danePogodowe.powiadomObserwatorów();
		System.out.println("---------------------------------------");
		danePogodowe.ustawOdczyty(27.7f, 70, 997.0f);

		danePogodowe.powiadomObserwatorów();
		System.out.println("---------------------------------------");

		danePogodowe.usuńObserwatora(prognozaWyswietlanie);

		danePogodowe.powiadomObserwatorów();
		System.out.println("---------------------------------------");

		danePogodowe.usuńObserwatora(statystykaWyswietlanie);

		danePogodowe.powiadomObserwatorów();
		System.out.println("---------------------------------------");

		Obserwator indeksCieplaWyswietlanie = new IndeksCieplaWyswietlanie();
		danePogodowe.zarejestrujObserwatora(indeksCieplaWyswietlanie);

		danePogodowe.powiadomObserwatorów();
	}
	
}