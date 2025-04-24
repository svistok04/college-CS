package pl.edu.zut.wi.po.space;

public class Ship {
	Person owner;

	public Ship(Person owner) {
		super();
		this.owner = owner;
	}

	public Person getOwner() {
		return owner;
	}

	public void setOwner(Person owner) {
		this.owner = owner;
	}
	
	
}
