package pl.edu.zut.po.wzorce.symulator;

public class MiniSymulatorKaczki {

	public static void main(String[] args) {
		Kaczka dzika = new DzikaKaczka();
		System.out.println("Kaczka dzika");
		dzika.wyswietl();
		dzika.wykonajKwacz();
		dzika.wykonajLeć();
		Kaczka gumowa = new GumowaKaczka();
		System.out.println("Kaczka gumowa");
		gumowa.wyswietl();
		gumowa.wykonajKwacz();
		gumowa.wykonajLeć();
		Kaczka wabik = new WabikKaczka();
		System.out.println("Kaczka wabik");
		wabik.wyswietl();
		wabik.wykonajKwacz();
		wabik.wykonajLeć();
		Kaczka plaskonos = new PlaskonosKaczka();
		System.out.println("Kaczka plaskonos");
		plaskonos.wyswietl();
		plaskonos.wykonajKwacz();
		plaskonos.wykonajLeć();

		ModelKaczki z_napedem = new ModelKaczki();
		System.out.println("Kaczka z napędem");
		z_napedem.wykonajLeć();
		z_napedem.wykonajKwacz();

		z_napedem.ustawLeć(new LotZNapędemRakietowym());
		z_napedem.wykonajLeć();

	}


}
