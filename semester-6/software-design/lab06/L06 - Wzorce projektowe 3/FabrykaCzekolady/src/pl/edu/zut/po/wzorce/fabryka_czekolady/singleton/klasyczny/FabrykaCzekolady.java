package pl.edu.zut.po.wzorce.fabryka_czekolady.singleton.klasyczny;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKociol kociol = CzekoladowyKociol.pobierzInstancje();
		kociol.napelniaj();
		kociol.gotuj();
		kociol.oprozniaj();
	}
}
