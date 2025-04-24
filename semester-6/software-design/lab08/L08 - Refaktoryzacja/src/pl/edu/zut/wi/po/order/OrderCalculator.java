package pl.edu.zut.wi.po.order;

public class OrderCalculator {

	public static double price(Order order) {
		// Cena ko�cowa = cena bazowa � upust + koszt wysy�ki.
		final double a = order.getQuantity() * order.getItemPrice();
		final double b = Math.max(0, order.getQuantity() - 500) * order.getItemPrice() * 0.05;
		final double c = Math.min(order.getQuantity() * order.getItemPrice() * 0.1, 100);
		return a - b + c;
	}
}
