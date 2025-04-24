package pl.edu.zut.po.wzorce.pizzeria.fabryka;

import pl.edu.zut.po.wzorce.pizzeria.pizza.*;

public class WloskaPizzeria extends Pizzeria{

    @Override
    public Pizza utworzPizze(String type) {
        if (type.equals("serowa")) {
            return new WloskaSerowaPizza();
        } else if (type.equals("grecka")) {
            return new WloskaPepperoniPizza();
        } else if (type.equals("pepperoni")) {
            return new WloskaPepperoniPizza();
        } else if (type.equals("owocemorza")) {
            return new WloskaOwoceMorzaPizza();
        } else if (type.equals("wegetariańska")) {
            return new WloskaWegetarianskaPizza();
        }
        return null;
    }

}
