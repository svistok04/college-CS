package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.WentylatorSufitowy;

public class WentylatorSufitowyWysokieObroty implements Polecenie{
    WentylatorSufitowy wentylatorSufitowy;

    public WentylatorSufitowyWysokieObroty(WentylatorSufitowy wentylatorSufitowy) {
        super();
        this.wentylatorSufitowy = wentylatorSufitowy;
    }

    @Override
    public void wykonaj() {
        wentylatorSufitowy.szybko();
    }

    @Override
    public void wycofaj() {
        wentylatorSufitowy.off();
    }
}
