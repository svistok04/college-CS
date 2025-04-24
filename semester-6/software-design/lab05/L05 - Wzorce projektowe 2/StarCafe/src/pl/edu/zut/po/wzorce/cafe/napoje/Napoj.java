package pl.edu.zut.po.wzorce.cafe.napoje;

public abstract class Napoj {
	protected String opis;

	public Napoj() {
		opis = "Nieznany napój";
	}

	public String pobierzOpis() {
		return opis;
	}

	public abstract double koszt();
}