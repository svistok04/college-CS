package pl.edu.zut.wi.po.invoice;

import java.time.LocalDate;
import java.util.Arrays;

public class InvoiceMain {

	public static void main(String[] args) {
		Invoice invoice = new Invoice("Klient sp. z o.o.", Arrays.asList(new Order [] {
				new Order(10), 
				new Order(20), 
				new Order(30)}));
		InvoiceManager.printOwing(invoice);
	}

}
