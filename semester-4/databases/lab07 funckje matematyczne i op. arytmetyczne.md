1. **Spróbuj zamienić kody pocztowe z tabeli customers zmieniając format na daty(format: DATE) wykorzystując funkcję CONVERT. Pokaż oryginalne kody(bez wartości NULL) pocztowe, oraz efekt zamiany. Uszereguj datami rosnąco. Przyjrzyj się które kody uległy zamianie i zastanów dlaczego.**
	```SQL
	SELECT customers.postalCode, CONVERT(customers.postalCode, DATE) AS postalCodeToDate
	FROM customers
	WHERE customers.postalCode IS NOT NULL
	ORDER BY postalCodeToDate
	```
	![[Pasted image 20240415144612.png]]
	<br>

2. **A teraz tak samo zamień kody pocztowe zmieniając ich format na czas(format: TIME). Przyjrzyj się które kody uległy zamianie i zastanów dlaczego.**
	```SQL
	SELECT customers.postalCode, CONVERT(customers.postalCode, TIME) AS postalCodeToTime
	FROM customers
	WHERE customers.postalCode IS NOT NULL
	```
	![[Pasted image 20240415140138.png]]
	<br>

3. **Dla modelu o kodzie S18_4027 od buyPrice odejmij MSRP. Wynik podaj jako wartość bezwzględną.**
	```SQL
	SELECT ABS(products.buyPrice - products.MSRP)
	FROM products
	WHERE products.productCode = 'S18_4027'
	```
	![[Pasted image 20240414121217.png]]
	<br>

4. **Dla modelu o kodzie S24_2972 jego buyPrice podnieś do potęgi trzeciej. Wynik „obetnij” do dwóch miejsc po przecinku, NIE ZAOKRĄGLAJ.**
	```SQL
	SELECT TRUNCATE(POW(products.buyPrice, 3), 2)
	FROM products
	WHERE products.productCode = 'S24_2972'
	```
	![[Pasted image 20240414121329.png]]
	<br>

5. **Dla klienta o numerze 131 oblicz pierwiastek kwadratowy z sumy jego płatności(amount z tabeli payments). Wynik zaokrąglij do czterech miejsc po przecinku.**
	```SQL
	SELECT ROUND(SQRT(SUM(payments.amount)), 4)
	FROM customers
	JOIN payments ON payments.customerNumber = customers.customerNumber 
	WHERE customers.customerNumber = 131
	```
	![[Pasted image 20240414121727.png]]
	<br>

6. **Pokaż pierwiastek trzeciego stopnia z ilości płatności dokonanych przez klienta o numerze 124.**
	```SQL
	SELECT POW(COUNT(*), 1/3)
	FROM payments
	WHERE customerNumber = 124
	```
	![[Pasted image 20240414122805.png]]
	<br>

7. **Pokaż nazwy miast w których pracują pracownicy wyższego szczebla, czyli tacy którzy mają jobTitle inne niż ‘Sales Rep’. Wykorzystaj funkcję EXISTS().**
	```SQL
	SELECT DISTINCT offices.city
	FROM offices
	WHERE EXISTS (
	    SELECT 1
	    FROM employees
	    WHERE offices.officeCode = employees.officeCode AND employees.jobTitle != 'Sales Rep'
	);
	
	```
	![[Pasted image 20240414124611.png]]
	<br>

8. **Pokaż nazwy modeli których jednorazowo zamówiono conajmniej 90 sztuk (quantityOrdered). Wykorzystaj funkcję EXISTS().**
	```SQL
	SELECT DISTINCT products.productName
	FROM products
	WHERE EXISTS (
	    SELECT 1
	    FROM orderdetails
	    WHERE orderdetails.productCode = products.productCode AND orderdetails.quantityOrdered > 90
	);
	```
	![[Pasted image 20240414130255.png]]
	<br>

9. **Pokaż ilu klientów posiada nieparzysty customerNumer. Wykorzystaj funkcję MOD() oraz zagnieżdżone zapytanie (SELECT … FROM (SELECT … FROM)).**
	```SQL
	SELECT COUNT(*)
	FROM (SELECT 1
	      FROM customers
	      WHERE MOD(customers.customerNumber, 2) = 1) AS subQuery
	```
	![[Pasted image 20240414131514.png]]
	<br>

10. **Pokaż ile firma zarobiłaby jakby sprzedała na raz wszystkie modele znajdujące się w magazynie. Kolumnie nadaj alias SUM. Wynik podaj bez miejsc po przecinku.**
	```SQL
	SELECT ROUND(SUM(quantityInStock * (MSRP - buyPrice))) AS SUM
	FROM products;
	```
	![[Pasted image 20240415135957.png]]
	a) **Dodaj kolumnę która sprawdzi ile firma zarobiłaby gdyby wszystkie ceny (zarówno zakupu jak i sprzedaży) należało obowiązkowo zaokrąglić, aby nie było żadnych miejsc po przecinku. Kolumnie nadaj alias SUM_ROUND.**
	```SQL
	SELECT SUM(quantityInStock * (ROUND(MSRP) - ROUND(buyPrice))) AS SUM_ROUND
	FROM products;
	```
	![[Pasted image 20240414132147.png]]
	 b) **Dodaj kolumnę która sprawdzi ile firma zarobiłaby gdyby wszystkie ceny (zarówno zakupu jak i sprzedaży) należało obowiązkowo zaokrąglić tylko do góry. Kolumnie nadaj alias SUM_CEIL.**
	 ```SQL
	SELECT SUM(quantityInStock * (CEIL(MSRP) - CEIL(buyPrice))) AS SUM_CEIL
	FROM products;
	```
	![[Pasted image 20240415135905.png]]
	c) **Dodaj kolumnę która sprawdzi ile firma zarobiłaby gdyby wszystkie ceny (zarówno zakupu jak i sprzedaży) należało obowiązkowo zaokrąglić tylko do dołu. Kolumnie nadaj alias SUM_FLOOR.**
	```SQL
	SELECT SUM(quantityInStock * (FLOOR(MSRP) - FLOOR(buyPrice))) AS SUM_FLOOR
	FROM products;
	```
	![[Pasted image 20240415135850.png]]