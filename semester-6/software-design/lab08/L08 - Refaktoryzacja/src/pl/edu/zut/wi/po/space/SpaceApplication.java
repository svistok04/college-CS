package pl.edu.zut.wi.po.space;

public class SpaceApplication {

	public static void main(String[] args) {
		Space space = new Space();
		space.setDefaultOwner(new Person("Martin", "Fowler"));
		Ship spaceShip = new Ship(space.getDefaultOwner());
		space.setDefaultOwner(new Person("Rebecca", "Parsons"));
	}

}
