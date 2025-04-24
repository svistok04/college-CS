package pl.edu.zut.po.wzorce.pilot.sterowniki;

public class Swiatlo {
	private String lokalizacja;
	private int poziom;

	public Swiatlo(String lokalizacja) {
		this.lokalizacja = lokalizacja;
	}

	public void wlacz() {
		poziom = 100;
		System.out.println(lokalizacja + " światło jest włączone");
	}

	public void wylacz() {
		poziom = 0;
		System.out.println(lokalizacja + " światło jest wyłączone");
	}

	public void sciemnij(int poziom) {
		this.poziom = poziom;
		if (poziom == 0) {
			wylacz();
		}
		else {
			System.out.println(lokalizacja + " światło jest ściemnione na " + poziom + "%");
		}
	}

	public int odczytajPoziom() {
		return poziom;
	}
}
