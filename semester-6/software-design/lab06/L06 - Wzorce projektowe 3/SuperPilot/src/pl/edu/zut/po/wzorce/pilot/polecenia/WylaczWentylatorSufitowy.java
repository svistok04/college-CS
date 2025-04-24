package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.WentylatorSufitowy;

public class WylaczWentylatorSufitowy implements Polecenie{
    WentylatorSufitowy wentylatorSufitowy;

    public WylaczWentylatorSufitowy(WentylatorSufitowy wentylatorSufitowy) {
        super();
        this.wentylatorSufitowy = wentylatorSufitowy;
    }

    @Override
    public void wykonaj() {
        wentylatorSufitowy.off();
    }

    @Override
    public void wycofaj() {
        wentylatorSufitowy.szybko();
    }
}
