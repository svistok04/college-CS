package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.Swiatlo;

public class PolecenieWlaczSwiatlo implements Polecenie {
	Swiatlo swiatlo;

	public PolecenieWlaczSwiatlo(Swiatlo swiatlo) {
		super();
		this.swiatlo = swiatlo;
	}

	@Override
	public void wykonaj() {
		swiatlo.wlacz();
	}

	@Override
	public void wycofaj() {
		swiatlo.wylacz();
	}
}
