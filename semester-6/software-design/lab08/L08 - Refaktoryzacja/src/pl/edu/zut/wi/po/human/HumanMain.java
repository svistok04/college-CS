package pl.edu.zut.wi.po.human;

public class HumanMain {

	public static void main(String[] args) {
		Human h = new Human("Jan Kowalski", "33", "Polska", "Szczecin", "Langiewicza", "15", "2");
		System.out.println(h.getFullAddress());
	}

}
