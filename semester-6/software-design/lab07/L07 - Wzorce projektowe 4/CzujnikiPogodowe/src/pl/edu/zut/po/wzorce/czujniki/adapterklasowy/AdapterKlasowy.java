package pl.edu.zut.po.wzorce.czujniki.adapterklasowy;

public class AdapterKlasowy extends WeatherSensor implements CzujnikPogodowy {

    public double pobierzTemperature() {
        return Math.round((readTemp() - 32) * 5/9 * 10.0) / 10.0;
    }

    public double pobierzCisnienie() {
        return Math.round(readPressure() * 1000 * 10.0) / 10.0;
    }

    public double pobierzWilgotnosc() {
        return readHumidity() * 100;
    }
}
