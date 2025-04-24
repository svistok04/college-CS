package pl.edu.zut.po.wzorce.pilot.sterowniki;

public class Jacuzzi {
	private boolean wlączone;
	private int temperatura;

	public Jacuzzi() {
	}

	public void wlacz() {
		wlączone = true;
	}

	public void wylacz() {
		wlączone = false;
	}

	public void cyrkulacja() {
		if (wlączone) {
			System.out.println("Jacuzzi bąbluje!");
		}
	}

	public void wlaczDysze() {
		if (wlączone) {
			System.out.println("Jacuzzi dysze są włączone");
		}
	}

	public void wylaczDysze() {
		if (wlączone) {
			System.out.println("Jacuzzi dysze są wyłączone");
		}
	}

	public void ustawTemperature(int temperatura) {
		if (temperatura > this.temperatura) {
			System.out.println("Jacuzzi nagrzewa się do parowania w temp. " + temperatura + " stopni");
		}
		else {
			System.out.println("Jacuzzi oziębia się do temp. " + temperatura + " stopni");
		}
		this.temperatura = temperatura;
	}
}
