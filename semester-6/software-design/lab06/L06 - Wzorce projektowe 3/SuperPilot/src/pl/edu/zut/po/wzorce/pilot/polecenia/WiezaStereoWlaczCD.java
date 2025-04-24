package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.WiezaStereo;

public class WiezaStereoWlaczCD implements Polecenie{
    WiezaStereo wiezaStereo;

    public WiezaStereoWlaczCD(WiezaStereo wiezaStereo) {
        super();
        this.wiezaStereo = wiezaStereo;
    }

    @Override
    public void wykonaj() {
        wiezaStereo.wlacz();
        wiezaStereo.ustawCD();
    }

    @Override
    public void wycofaj() {
        wiezaStereo.wylacz();
    }
}
