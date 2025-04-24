package pl.edu.zut.wi.po.human;

public class Human {
    private String name;
    private String age;
    private String country;
    private String city;
    private String street;
    private String house;
    private String quarter;

    public Human(String name, String age, String country, String city, String street, String house, String quarter) {
		super();
		this.name = name;
		this.age = age;
		this.country = country;
		this.city = city;
		this.street = street;
		this.house = house;
		this.quarter = quarter;
	}

	public String getFullAddress() {
        StringBuilder result = new StringBuilder();
        return result
                        .append(country)
                        .append(", ")
                        .append(city)
                        .append(", ")
                        .append(street)
                        .append(", ")
                        .append(house)
                        .append("/")
                        .append(quarter).toString();
    }
 }