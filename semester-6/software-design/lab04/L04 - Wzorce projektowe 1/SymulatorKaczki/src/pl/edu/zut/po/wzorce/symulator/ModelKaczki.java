package pl.edu.zut.po.wzorce.symulator;

public class ModelKaczki extends Kaczka{

    public ModelKaczki(){
        latanieInt = new NieLatam();
        kwakanieInt = new NieKwacz();
    }

    public void ustawKwacz(KwakanieInterfejs kwakanieInt) {
        this.kwakanieInt = kwakanieInt;
    };
    public void ustawLeć(LatanieInterfejs latanieInt){
        this.latanieInt = latanieInt;
    };


}
