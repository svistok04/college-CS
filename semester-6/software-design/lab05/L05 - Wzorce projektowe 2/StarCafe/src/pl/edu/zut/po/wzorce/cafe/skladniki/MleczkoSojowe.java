package pl.edu.zut.po.wzorce.cafe.skladniki;

import pl.edu.zut.po.wzorce.cafe.napoje.Napoj;

public class MleczkoSojowe extends SkladnikDekorator{


    public MleczkoSojowe(Napoj napoj) {
        super(napoj);
    }

    @Override
    public double koszt() {
        return napoj.koszt() + 0.15;
    }

    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\nz mleczkiem sojowym";
    }
}
