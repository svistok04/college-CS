package pl.edu.zut.wi.po.newmath;

public class Circle {
	public static double circumference(double radius) {
		return 2 * Math.PI * radius;
	}
	
	public static void main(String[] params) {
		System.out.println(String.format("circumference of radius 2 equals %f", Circle.circumference(2)));
	}
}
