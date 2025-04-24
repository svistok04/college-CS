package pl.edu.zut.po.wzorce.fabryka_czekolady.singleton.jbloch;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKociol kociol = CzekoladowyKociol.INSTANCE;
		kociol.napelniaj();
		kociol.gotuj();
		kociol.oprozniaj();
	}
}
