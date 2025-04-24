package pl.edu.zut.wi.po.tea;

public class TeaApplication {

	public static void main(String[] args) {

		System.out.println(String.format("firstMethod=%.2f", firstMethod()));
		System.out.println(String.format("secondMethod=%.2f", secondMethod()));
		System.out.println(String.format("thirdMethod=%.2f", thirdMethod()));
	}

	public static double firstMethod() {
		ReadingRecord aReading = acquireReading();
		aReading.transform();
		return aReading.baseCharge;
	}

	public static double secondMethod() {
		ReadingRecord aReading = acquireReading();
		aReading.transform();
		return aReading.taxableCharge;
	}
	
	public static double thirdMethod() {
		ReadingRecord aReading = acquireReading();
		aReading.transform();
		return aReading.baseCharge;
	}


	private static ReadingRecord acquireReading() {
		ReadingRecord reading = new ReadingRecord();
		reading.customer = "ivan";
		reading.quantity = 10;
		reading.month = 2;
		reading.year = 2019;
		return reading;
	}
}
