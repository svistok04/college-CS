1. **Utwórz zestaw rekordów z tabeli Products, wyświetlając nazwę produktu i liczbę znaków tej nazwy. Uporządkuj malejąco według długości nazwy (wynik ogranicz do 25 wierszy).**
	```SQL
	SELECT products.productName, LENGTH(products.productName) AS `dlugosc nazwy`
	FROM products
	ORDER BY `dlugosc nazwy` DESC
	LIMIT 25
	```
	![[Pasted image 20240415141453.png]]
	<br>

2. **Wyświetl nazwy kategorii produktów (productlines), zamieniając wszystkie
wystąpienia litery ‘a’ na tekst ‘\<A\>’ z uwzględnieniem wielkości liter. Wynik: (stara nazwa, nowa nazwa)**
```SQL
SELECT productlines.productLine AS `stara nazwa`, REPLACE(productlines.productLine, 'a', '<A>') AS `nowa nazwa`
FROM productlines
```
![[Pasted image 20240415141708.png]]
<br>

3. **Wyszukaj wszystkie modele wykonane z drewna i podaj ich nazwę, skalę oraz producenta. Uporządkuj alfabetycznie wg nazwy producenta.**
	```SQL
	SELECT products.productName, products.productScale, products.productVendor
	FROM products
	WHERE products.productDescription LIKE '%wood%'
	ORDER BY products.productVendor
	```
	![[Pasted image 20240415142002.png]]
	<br>

4. **Wyszukaj wszystkich sprzedawców i utwórz dla nich nowe adresy e-mail według wzoru: \<pierwsza i ostatnia litera imienia\>”.”\<nazwisko\>”@motoshop.biz” (małe litery), Wyniki uporządkuj rosnąco według nazwiska.**
	```SQL
	SELECT employees.jobTitle, 
		   employees.firstName, employees.lastName, 
	       CONCAT(LOWER(LEFT(employees.firstName, 1)), 
	              RIGHT(employees.firstName, 1),
	              '.',
	              LOWER(employees.lastName),
	              '@motorshop.biz') AS `nowy email`
	FROM employees
	```
	![[Pasted image 20240422141409.png]]
	<br>

5. **Sporządź wykaz wszystkich motocykli, wyodrębniając z ich nazwy: rok i model, po czym uporządkuj rosnąco według roku.**
	```SQL
	SELECT products.productName, 
		   LEFT(products.productName, 4) AS Rok, 
	       SUBSTR(products.productName, 5, LENGTH(products.productName) - 4) AS Model
	FROM products
	WHERE products.productLine = 'Motorcycles'
	ORDER BY Rok
	```
	![[Pasted image 20240422141539.png]]
	<br>

6. **Sporządź wykaz klientów, porządkując według kraju i stanu (w przypadku braku nazwy stanu umieść tekst ‘brak danych’).**
	```SQL
	SELECT customers.customerName, customers.country, customers.city, IF(customers.state IS NOT NULL, customers.state, 'brak danych') AS stan
	FROM customers
	ORDER BY customers.country, stan
	```
	![[Pasted image 20240415143905.png]]
	<br>

7. **Wykaz sprzedawców według oddziałów firmy i uporządkowany alfabetycznie wg nazwisk wraz z określeniem terytorium sprzedaży, stosując następujące nazwy regionu: ‘NA’ – ‘Ameryka Północna’, ‘EMEA’ – ‘Europa’, dla pozostałych - ‘reszta świata’.**
	```SQL
	SELECT employees.officeCode, offices.city, employees.firstName, employees.lastName, offices.country,
		   CASE
	           WHEN offices.territory = 'NA' THEN 'Ameryka Północna'
	           WHEN offices.territory = 'EMEA' THEN 'Europa'
	           ELSE 'reszta świata'
	       END AS `Kod terytorium`
	FROM employees
	JOIN offices ON offices.officeCode = employees.officeCode
	ORDER BY employees.officeCode, employees.lastName
	```
	![[Pasted image 20240415144452.png]]