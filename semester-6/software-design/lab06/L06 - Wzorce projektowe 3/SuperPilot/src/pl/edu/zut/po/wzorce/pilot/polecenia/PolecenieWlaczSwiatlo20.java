package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.Swiatlo;

public class PolecenieWlaczSwiatlo20 implements Polecenie{
    Swiatlo swiatlo;

    public PolecenieWlaczSwiatlo20(Swiatlo swiatlo) {
        super();
        this.swiatlo = swiatlo;
    }

    @Override
    public void wykonaj() {
        swiatlo.wlacz();
        swiatlo.sciemnij(20);
    }

    @Override
    public void wycofaj() {
        swiatlo.wylacz();
    }
}
