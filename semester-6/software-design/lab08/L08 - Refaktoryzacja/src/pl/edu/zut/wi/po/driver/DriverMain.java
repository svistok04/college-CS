package pl.edu.zut.wi.po.driver;

public class DriverMain {

	public static void main(String[] args) {
		DriverMain dm = new DriverMain();
		Driver driver = new Driver("jan kowalski", 6);
		dm.rate(driver);
	}

	private void rate(Driver driver) {
		System.out.println(String.format("driver: %s, rating %d", driver.getName(), rating(driver)));
	}

	public int rating(Driver driver) {
		return driver.getLateDeliveries() > 5 ? 2 : 1;
		
	}

}
