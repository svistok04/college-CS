package pl.edu.zut.po.wzorce.fabryka_czekolady;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKociol kociol = new CzekoladowyKociol();
		kociol.napelniaj();
		kociol.gotuj();
		kociol.oprozniaj();
	}
}
