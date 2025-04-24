package pl.edu.zut.po.wzorce.pilot;

import pl.edu.zut.po.wzorce.pilot.polecenia.Polecenie;

public class MiniPilot {
	Polecenie slot;
	
	public void ustawPolecenie(Polecenie polecenie) {
		slot = polecenie;
	}
	
	public void przyciskNacisniety() {
		slot.wykonaj();
	}

}
