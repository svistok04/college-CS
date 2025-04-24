package pl.edu.zut.wi.po.employee;

public class Employee {
	private float salary;
	private float bonusPercentage;
	private EmployeeType employeeType;

	public EmployeeType getEmployeeType() {
		return employeeType;
	}

	public Employee(float salary, float bonusPercentage, EmployeeType employeeType) {
		super();
		this.salary = salary;
		this.bonusPercentage = bonusPercentage;
		this.employeeType = employeeType;
	}
	
	public float calculateSalary() {
		switch(employeeType) {
		case Worker:
			return salary;
		case Supervisor:
			return salary + (bonusPercentage * 0.5f);
		case Manager:
			return salary + (bonusPercentage * 0.7f);
		}
		return 0f;
	}

	public float calculateYearBouns() {
		switch(employeeType) {
		case Worker:
			return 0;
		case Supervisor:
			return salary + salary * 0.7f;
		case Manager:
			return salary + salary * 0.1f;
		}
		return 0f;
	}
	

}
