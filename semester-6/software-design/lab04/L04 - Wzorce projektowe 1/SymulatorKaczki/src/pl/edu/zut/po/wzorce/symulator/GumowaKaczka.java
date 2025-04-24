package pl.edu.zut.po.wzorce.symulator;


public class GumowaKaczka extends Kaczka {

	public GumowaKaczka() {
		kwakanieInt = new Piszcz();
		latanieInt = new NieLatam();
	}

	public void wyswietl(){
		System.out.println("Wygląda jak gumowa kaczka");
	}
}