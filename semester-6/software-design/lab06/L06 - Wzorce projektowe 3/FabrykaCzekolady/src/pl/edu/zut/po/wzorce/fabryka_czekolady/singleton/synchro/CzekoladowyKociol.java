package pl.edu.zut.po.wzorce.fabryka_czekolady.singleton.synchro;

public class CzekoladowyKociol {
	private static CzekoladowyKociol unikalnaInstancja;
	private boolean pusty;
	private boolean ugotowany;


	private CzekoladowyKociol() {
		pusty = true;
		ugotowany = false;
		System.out.println("Utworzenie instancji Czekoladowego Kotła: " + this.hashCode());
	}

	public static synchronized CzekoladowyKociol pobierzInstancje() {
		if (unikalnaInstancja == null) {
			unikalnaInstancja = new CzekoladowyKociol();
		}
		return unikalnaInstancja;
	}



	public void napelniaj() {
		if (jestPusty()) {
			pusty = false;
			ugotowany = false;
			// napełniaj bojler mieszanką mleka i czekolady
			System.out.println("Napełnianie bojlera mieszanką czekolady i mleka " + this.hashCode());
		}
	}

	public void oprozniaj() {
		if (!jestPusty() && jestUgotowany()) {
			// opróżniaj bojler z ugotowanej mieszanki mleka i czekolady
			System.out.println("Opróżnianie bojlera z ugotowanej mieszanki czekolady i mleka " + this.hashCode());
			pusty = true;
		}
	}

	public void gotuj() {
		if (!jestPusty() && !jestUgotowany()) {
			// gotuj zawartość kotła
			System.out.println("Gotowanie mieszanki czekolady i mleka " + this.hashCode());
			ugotowany = true;
		}
	}

	public boolean jestPusty() {
		return pusty;
	}

	public boolean jestUgotowany() {
		return ugotowany;
	}
}