package pl.edu.zut.po.wzorce.pilot.sterowniki;

public class WiezaStereo {
	private String lokalizacja;

	public WiezaStereo(String location) {
		this.lokalizacja = location;
	}

	public void wlacz() {
		System.out.println(lokalizacja + " wieża stereo jest włączona");
	}

	public void wylacz() {
		System.out.println(lokalizacja + " wieża stereo jest wyłączona");
	}

	public void ustawCD() {
		System.out.println(lokalizacja + " wieża stereo CD jest włączone");
	}

	public void ustawDVD() {
		System.out.println(lokalizacja + " wieża stereo DVD jest włączone");
	}

	public void ustawRadio() {
		System.out.println(lokalizacja + " wieża stereo Radio jest włączone");
	}

	public void ustawGlosnosc(int glosnosc) {
		// code to set the volume
		// valid range: 1-11 (after all 11 is better than 10, right?)
		System.out.println(lokalizacja + " wieża stereo głośność ustawiona na " + glosnosc);
	}

}
