package pl.edu.zut.po.wzorce.pogodynka.wyswietl;

import pl.edu.zut.po.wzorce.pogodynka.Obserwator;
import pl.edu.zut.po.wzorce.pogodynka.WyświetlElement;

public class WarunkiBiezaceWyswietlanie implements Obserwator, WyświetlElement {

	private float temperatura;
	private float wilgotnosc;
	private float cisnienie;

	public void aktualizacja(float temperatura, float wilgotnosc, float cisnienie) {
		this.temperatura = temperatura;
		this.wilgotnosc = wilgotnosc;
		this.cisnienie = cisnienie;
		wyświetl();
	}
	
	public void wyświetl() {
		System.out.println("Warunki bieżące " + temperatura + " stopni C oraz " + wilgotnosc + "% wilgotność");
	}

}