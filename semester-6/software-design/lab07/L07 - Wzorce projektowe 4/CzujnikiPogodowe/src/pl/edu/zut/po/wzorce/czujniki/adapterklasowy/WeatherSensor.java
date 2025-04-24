package pl.edu.zut.po.wzorce.czujniki.adapterklasowy;

import java.util.Random;

public class WeatherSensor {
    private final Random generator = new Random(1234L);
    
    /** Provides air temperature.
     * 
     * @return Temperature in °F (degrees Fahrenheit)
     */
    public double readTemp() {
        return Math.round((generator.nextDouble() * 150 - 30) *10)/10d;
    }
    
    /** Provides air humidity.
     * 
     * @return Humidity in fraction (not percentage)
     */
    public double readHumidity() {
    	return Math.round(Math.min(1, (Math.max(0, generator.nextGaussian() * 0.1 + 0.5))) * 100)/100d;
    }
    
    /** Provides atmospheric pressure.
     * 
     * @return Pressure in bar.
     */
    public double readPressure() {
    	return Math.round(Math.min(1050, (Math.max(950, generator.nextGaussian() * 25 + 1000))) * 100)/100000d;
    }
}
