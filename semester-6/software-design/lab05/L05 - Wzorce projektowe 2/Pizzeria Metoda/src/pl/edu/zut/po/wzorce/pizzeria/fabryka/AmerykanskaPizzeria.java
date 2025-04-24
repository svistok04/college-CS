package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.pizza.*;

public class AmerykanskaPizzeria extends Pizzeria {

    @Override
    public Pizza utworzPizze(String type) {
        if (type.equals("serowa")) {
            return new AmerykanskaSerowaPizza();
        } else if (type.equals("grecka")) {
            return new AmerykanskaPepperoniPizza();
        } else if (type.equals("pepperoni")) {
            return new AmerykanskaPepperoniPizza();
        } else if (type.equals("owocemorza")) {
            return new AmerykanskaOwoceMorzaPizza();
        } else if (type.equals("wegetariańska")) {
            return new AmerykanskaWegetarianskaPizza();
        }
        return null;
    }
}
