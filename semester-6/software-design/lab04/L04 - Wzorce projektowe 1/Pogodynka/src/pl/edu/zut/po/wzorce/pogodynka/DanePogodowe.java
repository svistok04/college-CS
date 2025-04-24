package pl.edu.zut.po.wzorce.pogodynka;

import pl.edu.zut.po.wzorce.pogodynka.wyswietl.PrognozaWyswietlanie;
import pl.edu.zut.po.wzorce.pogodynka.wyswietl.StatystykaWyswietlanie;
import pl.edu.zut.po.wzorce.pogodynka.wyswietl.WarunkiBiezaceWyswietlanie;
import java.util.ArrayList;


public class DanePogodowe implements Podmiot{
	private float temperatura;
	private float wilgotnosc;
	private float cisnienie;

	private ArrayList<Obserwator> obserwatorzy = new ArrayList<>();

	private PrognozaWyswietlanie prognozaWyswietl = new PrognozaWyswietlanie();
	private WarunkiBiezaceWyswietlanie warunkiBiezaceWyswietl = new WarunkiBiezaceWyswietlanie();
	private StatystykaWyswietlanie statystykaWyswietl = new StatystykaWyswietlanie();

	public void odczytyZmiana(){
		float temp = pobierzTemperature();
		float wilgotnosc = pobierzWilgotnosc();
		float cisnienie = pobierzCisnienie();
//		warunkiBiezaceWyswietl.aktualizacja(temp, wilgotnosc, cisnienie);
//		statystykaWyswietl.aktualizacja(temp, wilgotnosc, cisnienie);
//		prognozaWyswietl.aktualizacja(temp, wilgotnosc, cisnienie);
	}

	private float pobierzTemperature(){
		return temperatura;
	}

	private float pobierzWilgotnosc(){
		return wilgotnosc;
	}

	private float pobierzCisnienie(){
		return cisnienie;
	}
	
	public void ustawOdczyty(float temperatura, float wilgotnosc, float cisnienie) {
		this.temperatura = temperatura;
		this.wilgotnosc = wilgotnosc;
		this.cisnienie = cisnienie;
		odczytyZmiana();
	}

	@Override
	public void zarejestrujObserwatora(Obserwator o) {
		obserwatorzy.add(o);
	}

	@Override
	public void usuńObserwatora(Obserwator o) {
		obserwatorzy.remove(o);
	}

	@Override
	public void powiadomObserwatorów() {
		obserwatorzy.forEach(o -> o.aktualizacja(temperatura, wilgotnosc, cisnienie));
	}
}
