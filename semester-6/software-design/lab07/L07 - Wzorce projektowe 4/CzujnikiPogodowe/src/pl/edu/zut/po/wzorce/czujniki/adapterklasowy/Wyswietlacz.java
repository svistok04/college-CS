package pl.edu.zut.po.wzorce.czujniki.adapterklasowy;

public class Wyswietlacz {

    CzujnikPogodowy czujnik;
    
    public Wyswietlacz(CzujnikPogodowy czujnik) {
        this.czujnik = czujnik;
    }

    public void wyswietlDanePogodowe() {
        System.out.println("Dane z czujnika: " + czujnik.getClass().getSimpleName());
        System.out.println("Temperatura = " + czujnik.pobierzTemperature() + "°C");
        System.out.println("Ciśnienie = " + czujnik.pobierzCisnienie() + " hPa");
        System.out.println("Wilgotność względna = " + czujnik.pobierzWilgotnosc() + " %");
        System.out.println("-----------------------------------------------------");
    }
}
