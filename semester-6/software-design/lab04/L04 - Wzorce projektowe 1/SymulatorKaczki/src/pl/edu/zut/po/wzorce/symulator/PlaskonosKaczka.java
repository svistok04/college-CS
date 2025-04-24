package pl.edu.zut.po.wzorce.symulator;

public class PlaskonosKaczka extends Kaczka {

	public PlaskonosKaczka() {
		kwakanieInt = new Kwacz();
		latanieInt = new LatamBoMamSkrzydła();
	}
	public void wyswietl(){
		System.out.println("Wygląda jak płaskonos");
	}
}