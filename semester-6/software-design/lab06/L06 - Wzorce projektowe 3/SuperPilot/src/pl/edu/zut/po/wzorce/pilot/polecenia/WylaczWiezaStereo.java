package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.WiezaStereo;

public class WylaczWiezaStereo implements Polecenie{
    WiezaStereo wiezaStereo;

    public WylaczWiezaStereo(WiezaStereo wiezaStereo) {
        super();
        this.wiezaStereo = wiezaStereo;
    }


    @Override
    public void wykonaj() {
        wiezaStereo.wylacz();
    }

    @Override
    public void wycofaj() {
        wiezaStereo.wlacz();
        wiezaStereo.ustawCD();
    }
}
