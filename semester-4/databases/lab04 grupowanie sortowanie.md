1. **Z tabeli employees pokaż maile pracowników ułożone alfabetycznie.**
	```SQL
	SELECT email
	FROM employees
	ORDER BY email;
	```
	![[Pasted image 20240318133545.png]]

2. **Z tabeli products pokaż nazwy modeli oraz ich ceny, w kolejności od najwyższej.**
	```SQL
	SELECT productName, buyPrice
	FROM products
	ORDER BY buyPrice DESC;
	```
	![[Pasted image 20240318133655.png]]

3. **Znajdź cenę modelu najtaniej kupowanego od producenta. Pokaż tylko jego cenę (buyPrice).**
	```SQL
	SELECT MIN(buyPrice)
	FROM products;
	```
	![[Pasted image 20240318135618.png]]


4. **Pokaż cenę modelu najdrożej sprzedawanego (czyli MSRP - cena sprzedaży już z nałożoną marżą). Pokaż tylko wysokość tej kwoty.**
	```SQL
	SELECT MAX(MSRP)
	FROM products;
	```
	![[Pasted image 20240318135548.png]]


5. **Pokaż sumę wpłat z tablicy payments.**
	```SQL
	SELECT SUM(quantityOrdered*priceEach)
	FROM orderdetails;
	```
	![[Pasted image 20240318135508.png]]


6. **Pokaż wartość wszystkich zamówień.**
	```SQL
	SELECT SUM(quantityOrdered*priceEach)
	FROM orderdetails;
	```
	![[Pasted image 20240318135714.png]]


7. **Z tabeli products pokaż sumę wartości wszystkich modeli z serii Classic Cars.**
	```SQL
	SELECT SUM(buyPrice)
	FROM products
	WHERE productLine = 'Classic Cars';
	```
	![[Pasted image 20240318140339.png]]



8. **Z tabeli products zlicz ilość modeli których cena jest wyższa niż 50.**
	```SQL
	SELECT COUNT(*)
	FROM products
	WHERE buyPrice>50;
	```
	![[Pasted image 20240318140451.png]]



9. **Z tabeli customers pokaż łączną liczbę klientów pochodzących z USA, UK lub Australii.**
	```SQL
	SELECT COUNT(*)
	FROM customers
	WHERE country IN ('USA', 'UK', 'Australia');
	```
	![[Pasted image 20240318140815.png]]


10. **Pokaż z ilu łącznie krajów pochodzą klienci .**
	```SQL
	SELECT COUNT(DISTINCT country)
	FROM customers;
	```
	![[Pasted image 20240318140932.png]]

11. **Z tabeli customers pokaż każdy kraj oraz liczbę klientów pochodzących z danego kraju.**
	```SQL
	SELECT country, COUNT(*)
	FROM customers
	GROUP BY country;
	```
	![[Pasted image 20240318141112.png]]

12. **Z tabeli products pokaż linie modeli w których są tanie modele (poniżej 30). Pokaż nazwę linii oraz liczbę takich modeli dla każdej.**
	```SQL
	SELECT productLine, COUNT(*)
	FROM products
	WHERE buyPrice<30
	GROUP BY productLine
	```
	![[Pasted image 20240318141622.png]]

13. **Z tabeli payments pokaż klientów oraz sumy ich zamówień malejąco.**
	```SQL
	SELECT customerNumber, SUM(amount)
	FROM payments
	GROUP BY customerNumber
	ORDER BY SUM(amount) DESC;
	```
	![[Pasted image 20240318141944.png]]

14. **Z tabeli products pokaż serie modeli dla których suma wartości wszystkich dostępnych dla niej modeli jest większa od 1000.**
	```SQL
	SELECT productLine, SUM(buyPrice)
	FROM products
	GROUP BY productLine
	HAVING SUM(buyPrice)>1000;
	```
	![[Pasted image 20240318142551.png]]

15. **Z tabeli products pokaż skalę modelu oraz liczbę sztuk modeli w danej skali. Jednak liczba modeli musi być większa lub równa 10 w kolejności rosnącej.**
	```SQL
	SELECT productScale, COUNT(*) as amount
	FROM products
	GROUP BY productScale
	HAVING amount>=10
	ORDER BY amount;
	```
	![[Pasted image 20240318144758.png]]

16. **Ilu klientów mieszka w krajach w których znajdują się biura firmy.**
	```SQL
	SELECT COUNT(*)
	FROM customers
	WHERE country IN (
	    SELECT country
		FROM offices
	    );
	```
	![[Pasted image 20240318143953.png]]

17. **Pokaż ilu klientów znajduje się w każdym z krajów w których firma ma swoje placówki.**
	```SQL
	SELECT country, COUNT(*)
	FROM customers
	WHERE country IN (
	    SELECT country
		FROM offices
	    )
	GROUP BY country;
	```
	![[Pasted image 20240318144106.png]]