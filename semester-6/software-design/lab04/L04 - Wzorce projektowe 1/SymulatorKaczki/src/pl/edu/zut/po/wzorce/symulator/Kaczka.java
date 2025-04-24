package pl.edu.zut.po.wzorce.symulator;

public class Kaczka {

    protected LatanieInterfejs latanieInt;
    protected KwakanieInterfejs kwakanieInt;

    void plywaj() {
    	System.out.println("Pływam jak kaczka.");
    }
    void wyswietl() {
    	System.out.println("Wyglądam jak kaczka.");
    }

    void wykonajKwacz(){
        kwakanieInt.kwacz();
    };
    void wykonajLeć(){
        latanieInt.leć();
    };


}
