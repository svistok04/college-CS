package pl.edu.zut.wi.po.order;

public class Order {
	private double quantity;
	private double itemPrice;

	public Order(double quantity, double itemPrice) {
		super();
		this.quantity = quantity;
		this.itemPrice = itemPrice;
	}

	public double getQuantity() {
		return quantity;
	}
	public void setQuantity(double quantity) {
		this.quantity = quantity;
	}
	public double getItemPrice() {
		return itemPrice;
	}
	public void setItemPrice(double itemPrice) {
		this.itemPrice = itemPrice;
	}


}
