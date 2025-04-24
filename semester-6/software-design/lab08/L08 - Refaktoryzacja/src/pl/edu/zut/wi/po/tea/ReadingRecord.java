package pl.edu.zut.wi.po.tea;

public class ReadingRecord {
	String customer;
	int quantity;
	int month;
	int year;

	double baseCharge;
	double taxableCharge;

	public void transform() {
		this.baseCharge = baseRate(month, year) * quantity;
		this.taxableCharge = Math.max(0, baseCharge - taxThreshold(year));

	}

	private double baseRate(int month, int year) {
		return 12.5;
	}

	private double taxThreshold(int year) {
		return 100;
	}
}
