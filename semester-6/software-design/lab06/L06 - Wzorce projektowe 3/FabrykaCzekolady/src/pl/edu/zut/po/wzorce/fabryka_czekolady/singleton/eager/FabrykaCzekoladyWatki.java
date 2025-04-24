package pl.edu.zut.po.wzorce.fabryka_czekolady.singleton.eager;

public class FabrykaCzekoladyWatki {

	public static void main(String... params) {
		Thread watek1 = new Thread("Wątek 1") {
			public void run() {
				System.out.println("Uruchomione przez: " + getName());
				CzekoladowyKociol kociol = CzekoladowyKociol.pobierzInstance();
				kociol.napelniaj();
				kociol.gotuj();
				kociol.oprozniaj();
			}
		};
		Thread watek2 = new Thread("Wątek 2") {
			public void run() {
				System.out.println("Uruchomione przez: " + getName());
				CzekoladowyKociol kociol = CzekoladowyKociol.pobierzInstance();
				kociol.napelniaj();
				kociol.gotuj();
				kociol.oprozniaj();
			}
		};
		watek1.start();
		watek2.start();
	}
}
