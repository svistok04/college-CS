package pl.edu.zut.po.wzorce.symulator;

public class WabikKaczka extends Kaczka{
    public WabikKaczka() {
        kwakanieInt = new Kwacz();
        latanieInt = new NieLatam();
    }

    public void wyswietl(){
        System.out.println("Wygląda jak wabik kaczka");
    }
}
