package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.WiezaStereo;

public class WiezaStereoWlaczDVD implements Polecenie{
    WiezaStereo stereo;

    public WiezaStereoWlaczDVD(WiezaStereo stereo) {
        super();
        this.stereo = stereo;
    }

    @Override
    public void wykonaj() {
        stereo.wlacz();
        stereo.ustawDVD();
    }

    @Override
    public void wycofaj() {
        stereo.wylacz();
    }
}
