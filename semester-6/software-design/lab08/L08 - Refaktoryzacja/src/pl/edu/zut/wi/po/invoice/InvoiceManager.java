package pl.edu.zut.wi.po.invoice;

import java.time.LocalDate;

public class InvoiceManager {

	public static void printOwing(Invoice invoice) {
		double outstanding = 0;
		printPreNote();
		// Wyliczenie nale�no�ci.
		outstanding = calculateOutstanding(invoice);
		// Zapisanie daty p�atno�ci.
		writeDate(invoice);
		// Wy�wietlenie szczeg��w.
		printDetail(invoice, outstanding);
	}

	public static void printPreNote(){
		System.out.println("************************");
		System.out.println("* Rachunek dla klienta *");
		System.out.println("************************");
	}

	public static void writeDate(Invoice invoice) {
		LocalDate today = LocalDate.now();
		invoice.setDueDate(today.plusDays(30));
	}

	public static double calculateOutstanding(Invoice invoice) {
		double outstanding = 0;
		for (Order o : invoice.getOrders()) {
			outstanding += o.getAmount();
		}
		return outstanding;
	}

	public static void printDetail(Invoice invoice, double outstanding) {
		System.out.println(String.format("nazwa: %s", invoice.getCustomer()));
		System.out.println(String.format("kwota: %.2f", outstanding));
		System.out.println(String.format("p�atno�� do: %s", invoice.getDueDate()));
	}

}
