package pl.edu.zut.po.wzorce.pilot.sterowniki;

public class DrzwiGarazu {
	private String lokalizacja;

	public DrzwiGarazu(String lokalizacja) {
		this.lokalizacja = lokalizacja;
	}

	public void podnies() {
		System.out.println(lokalizacja + " drzwi garażu są podniesione");
	}

	public void opusc() {
		System.out.println(lokalizacja + " drzwi garażu są opuszczone");
	}

	public void stop() {
		System.out.println(lokalizacja + " drzwi garażu są zatrzymane");
	}

	public void wlaczSwiatlo() {
		System.out.println(lokalizacja + " światło w garażu jest włączone");
	}

	public void wylaczSwiatlo() {
		System.out.println(lokalizacja + " światło w garażu jest wyłączone");
	}
}
