package pl.edu.zut.po.wzorce.pilot.sterowniki;

public class TV {
	private String lokalizacja;
	private int kanal;

	public TV(String lokalizacja) {
		this.lokalizacja = lokalizacja;
	}

	public void wlacz() {
		System.out.println(lokalizacja + " TV jest włączony");
	}

	public void wylacz() {
		System.out.println(lokalizacja + " TV jest wyłączony");
	}

	public void ustawDVD() {
		this.kanal = 3;
		System.out.println(lokalizacja + " TV kanał jest ustawiony na DVD");
	}
	
	public void ustawKanal(int kanal) {
		this.kanal = kanal;
		System.out.println(lokalizacja + " Kanał: " + this.kanal);
	}
}
