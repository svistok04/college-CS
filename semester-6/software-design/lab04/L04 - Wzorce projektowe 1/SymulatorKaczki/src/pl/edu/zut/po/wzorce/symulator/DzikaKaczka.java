package pl.edu.zut.po.wzorce.symulator;

public class DzikaKaczka extends Kaczka {

	public void wyswietl(){
		System.out.println("Wygląda jak dzika kaczka");
	}

	public DzikaKaczka() {
		kwakanieInt = new Kwacz();
		latanieInt = new LatamBoMamSkrzydła();
	}
}