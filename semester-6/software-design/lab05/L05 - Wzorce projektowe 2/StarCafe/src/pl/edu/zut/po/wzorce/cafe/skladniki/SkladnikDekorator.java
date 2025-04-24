package pl.edu.zut.po.wzorce.cafe.skladniki;

import pl.edu.zut.po.wzorce.cafe.napoje.Napoj;

public abstract class SkladnikDekorator extends Napoj{
    Napoj napoj;

    public SkladnikDekorator(Napoj napoj) {
        this.napoj = napoj;
    }

    public abstract double koszt();
    public abstract String pobierzOpis();

}
