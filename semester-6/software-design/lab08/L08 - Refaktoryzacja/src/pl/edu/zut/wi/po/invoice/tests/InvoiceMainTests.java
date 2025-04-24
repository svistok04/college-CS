package pl.edu.zut.wi.po.invoice.tests;

import static org.junit.Assert.assertEquals;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Arrays;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import pl.edu.zut.wi.po.invoice.Invoice;
import pl.edu.zut.wi.po.invoice.InvoiceManager;
import pl.edu.zut.wi.po.invoice.Order;

public class InvoiceMainTests {
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private final PrintStream originalOut = System.out;

	@Before
	public void setUpStreams() {
	    System.setOut(new PrintStream(outContent));
	}

	@After
	public void restoreStreams() {
	    System.setOut(originalOut);
	}
	@Test
	public void testMain() {
		Invoice invoice = new Invoice("Klient sp. z o.o.", Arrays.asList(new Order [] {
				new Order(10), 
				new Order(20), 
				new Order(30)}));
		InvoiceManager.printOwing(invoice);
		assertEquals("************************\r\n" + 
				"* Rachunek dla klienta *\r\n" + 
				"************************\r\n" + 
				"nazwa: Klient sp. z o.o.\r\n" + 
				"kwota: 60,00\r\n" + 
				"p�atno�� do: 2020-11-11\r\n", outContent.toString());
	}

}
