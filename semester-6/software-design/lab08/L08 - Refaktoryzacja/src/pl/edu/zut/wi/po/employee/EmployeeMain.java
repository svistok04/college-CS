package pl.edu.zut.wi.po.employee;

public class EmployeeMain {

	public static void main(String[] args) {
		Employee w = new Employee(1000, 10, EmployeeType.Worker);
		System.out.println("employee type: " + w.getEmployeeType());
		System.out.println("employee salary: " + w.calculateSalary());
		System.out.println("employee year bonus: " + w.calculateYearBouns());

		Employee e = new Employee(1500, 20, EmployeeType.Supervisor);
		System.out.println("employee type: " + e.getEmployeeType());
		System.out.println("employee salary: " + e.calculateSalary());
		System.out.println("employee year bonus: " + e.calculateYearBouns());

		e = new Employee(2000, 30, EmployeeType.Manager);
		System.out.println("employee type: " + e.getEmployeeType());
		System.out.println("employee salary: " + e.calculateSalary());
		System.out.println("employee year bonus: " + e.calculateYearBouns());
		
	}

}
