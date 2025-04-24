package pl.edu.zut.po.wzorce.pilot;

import java.util.*;

import pl.edu.zut.po.wzorce.pilot.polecenia.BrakPolecenia;
import pl.edu.zut.po.wzorce.pilot.polecenia.Polecenie;

//
// This is the invoker
//
public class SuperPilot {
	private Polecenie[] poleceniaWlacz;
	private Polecenie[] poleceniaWylacz;
	private Polecenie polecenieWycofaj;
 
	public SuperPilot() {
		poleceniaWlacz = new Polecenie[7];
		poleceniaWylacz = new Polecenie[7];
 
		Polecenie brakPolecenia = new BrakPolecenia();
		for(int i=0; i<7; i++) {
			poleceniaWlacz[i] = brakPolecenia;
			poleceniaWylacz[i] = brakPolecenia;
		}
		polecenieWycofaj = brakPolecenia;
	}
  
	public void ustawPolecenie(int slot, Polecenie polecenieWlacz, Polecenie polecenieWylacz) {
		poleceniaWlacz[slot] = polecenieWlacz;
		poleceniaWylacz[slot] = polecenieWylacz;
	}
 
	public void wcisnietoPrzyciskWlacz(int slot) {
		poleceniaWlacz[slot].wykonaj();
		polecenieWycofaj = poleceniaWlacz[slot];
	}
 
	public void wcisnietoPrzyciskWylacz(int slot) {
		poleceniaWylacz[slot].wykonaj();
		polecenieWycofaj = poleceniaWylacz[slot];
	}

	public void wcisnietoPrzyciskWycofaj() {
		polecenieWycofaj.wycofaj();
	}
 
	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------ Super Pilot -------\n");
		for (int i = 0; i < poleceniaWlacz.length; i++) {
			stringBuff.append("[slot " + i + "] " + poleceniaWlacz[i].getClass().getName()
				+ "    " + poleceniaWylacz[i].getClass().getName() + "\n");
		}
		stringBuff.append("[undo] " + polecenieWycofaj.getClass().getName() + "\n");
		return stringBuff.toString();
	}
}
