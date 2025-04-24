package pl.edu.zut.wi.po.invoice;

public class Order {
	private double amount;

	public Order(double amount) {
		this.amount = amount;
	}

	public double getAmount() {
		return amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

}
