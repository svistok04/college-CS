package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.DrzwiGarazu;

public class ZamknijDrzwiGarazowe implements Polecenie{
    DrzwiGarazu drzwiGarazu;

    public ZamknijDrzwiGarazowe(DrzwiGarazu drzwiGarazu) {
        super();
        this.drzwiGarazu = drzwiGarazu;
    }

    @Override
    public void wykonaj() {
        drzwiGarazu.opusc();
    }

    @Override
    public void wycofaj() {
        drzwiGarazu.podnies();
    }
}
