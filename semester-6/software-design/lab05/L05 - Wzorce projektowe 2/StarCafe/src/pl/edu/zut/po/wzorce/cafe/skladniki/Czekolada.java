package pl.edu.zut.po.wzorce.cafe.skladniki;

import pl.edu.zut.po.wzorce.cafe.napoje.Napoj;

public class Czekolada extends SkladnikDekorator{


    public Czekolada(Napoj napoj) {
        super(napoj);
    }

    @Override
    public double koszt() {
        return napoj.koszt() + 0.20;
    }

    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\nz czekoladą";
    }
}
