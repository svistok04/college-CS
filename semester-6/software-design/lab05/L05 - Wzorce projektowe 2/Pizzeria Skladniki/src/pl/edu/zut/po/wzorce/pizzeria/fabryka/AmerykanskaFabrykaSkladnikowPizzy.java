package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.skladniki.*;

import java.util.List;

public class AmerykanskaFabrykaSkladnikowPizzy implements FabrykaSkladnikowPizzy {
    public Ciasto utworzCiasto() {
        return new GrubeChrupkieCiasto();
    }

    public Sos utworzSos() {
        return new SosPomidorowy();
    }

    public List<Ser> utworzSer() {
        return List.of(
                new SerMozarella(),
                new SerParmezan(),
                new SerReggiano());
    }

    public List<Warzywa> utworzWarzywa() {
        return List.of(
                new Baklazan(),
                new Szpinak(),
                new CzarneOliwki()
                );
    }

    public Pepperoni utworzPepperoni() {
        return new PlastryPepperoni();
    }

    public Malze utworzMalze() {
        return new MrozoneMalze();
    }
}