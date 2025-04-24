package pl.edu.zut.po.wzorce.fabryka_czekolady.singleton.eager;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKociol kociol = CzekoladowyKociol.pobierzInstance();
		kociol.napelniaj();
		kociol.gotuj();
		kociol.oprozniaj();
	}
}
