package pl.edu.zut.wi.po.driver;

public class Driver {
	private String name;
	private int lateDeliveries;

	public Driver(String name, int lateDeliveries) {
		this.name = name;
		this.lateDeliveries = lateDeliveries;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getLateDeliveries() {
		return lateDeliveries;
	}

	public void setLateDeliveries(int lateDeliveries) {
		this.lateDeliveries = lateDeliveries;
	}
	
}
