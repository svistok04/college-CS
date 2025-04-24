package pl.edu.zut.wi.po.invoice;

import java.time.LocalDate;
import java.util.List;

public class Invoice {
	private String customer;
	private LocalDate dueDate;
	private List<Order> orders;

	public Invoice(String customer, List<Order> orders) {
		this.customer = customer;
		this.orders = orders;
	}

	public String getCustomer() {
		return customer;
	}

	public void setCustomer(String customer) {
		this.customer = customer;
	}

	public LocalDate getDueDate() {
		return dueDate;
	}

	public void setDueDate(LocalDate dueDate) {
		this.dueDate = dueDate;
	}

	public List<Order> getOrders() {
		return orders;
	}

	public void setOrders(List<Order> orders) {
		this.orders = orders;
	}


	
	
}
