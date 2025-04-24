package pl.edu.zut.po.wzorce.pilot.polecenia;

import pl.edu.zut.po.wzorce.pilot.sterowniki.DrzwiGarazu;

public class OtworzDrzwiGarazowe implements Polecenie{
    DrzwiGarazu drzwiGarazu;

    public OtworzDrzwiGarazowe(DrzwiGarazu drzwiGarazu) {
        super();
        this.drzwiGarazu = drzwiGarazu;
    }

    @Override
    public void wykonaj() {
        drzwiGarazu.podnies();
    }

    @Override
    public void wycofaj() {
        drzwiGarazu.opusc();
    }
}
