package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.TV;

public class WlaczTv implements Polecenie{
    TV tv;

    public WlaczTv(TV tv) {
        super();
        this.tv = tv;
    }


    @Override
    public void wykonaj() {
        tv.wlacz();
        tv.ustawDVD();
    }

    @Override
    public void wycofaj() {
        tv.wylacz();
    }
}
