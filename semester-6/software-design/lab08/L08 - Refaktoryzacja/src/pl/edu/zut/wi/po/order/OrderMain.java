package pl.edu.zut.wi.po.order;

public class OrderMain {

	public static void main(String[] args) {
		Order order = new Order(10, 100);
		System.out.println(String.format("Cena ko�cowa zam�wienia: %.2f", OrderCalculator.price(order)));
	}

}
