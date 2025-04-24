package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.Jacuzzi;

public class PrzygotujJacuzzi implements Polecenie{
    Jacuzzi jacuzzi;

    public PrzygotujJacuzzi(Jacuzzi jacuzzi) {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.wlacz();
        jacuzzi.ustawTemperature(50);
        jacuzzi.wlaczDysze();
    }

    @Override
    public void wycofaj() {
        jacuzzi.wylacz();
    }
}
