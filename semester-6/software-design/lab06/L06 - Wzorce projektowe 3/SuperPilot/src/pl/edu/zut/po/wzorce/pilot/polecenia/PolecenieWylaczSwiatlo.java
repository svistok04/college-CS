package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.Swiatlo;

public class PolecenieWylaczSwiatlo implements Polecenie{
    Swiatlo swiatlo;

    public PolecenieWylaczSwiatlo(Swiatlo swiatlo) {
        super();
        this.swiatlo = swiatlo;
    }

    public void wykonaj() {
        swiatlo.wylacz();
    }

    @Override
    public void wycofaj() {
        swiatlo.wlacz();
    }
}
