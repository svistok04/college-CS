package pl.edu.zut.po.wzorce.czujniki.adapterobiektowy;


public class AdapterObiektowy implements CzujnikPogodowy {
    WeatherSensor weatherSensor;
    public AdapterObiektowy(WeatherSensor weatherSensor) {
        this.weatherSensor = weatherSensor;
    }

    @Override
    public double pobierzTemperature() {
        return Math.round((weatherSensor.readTemp() - 32) * 5/9 * 10.0) / 10.0;
    }

    @Override
    public double pobierzCisnienie() {
        return Math.round(weatherSensor.readPressure() * 1000 * 10.0) / 10.0;
    }

    @Override
    public double pobierzWilgotnosc() {
        return weatherSensor.readHumidity() * 100;
    }
}