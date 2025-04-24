package pl.edu.zut.po.wzorce.cafe.skladniki;

import pl.edu.zut.po.wzorce.cafe.napoje.Napoj;

public class BitaSmietana extends SkladnikDekorator{


    public BitaSmietana(Napoj napoj) {
        super(napoj);
    }

    @Override
    public double koszt() {
        return napoj.koszt() + 0.10;
    }

    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\nz bitą śmietaną";
    }
}
