1. **Z tabeli pracowników wyświetl imię, nazwisko i email. Dodaj do wyników kolumnę z nazwą miasta, w którym znajduje się biuro pracownika. Kolumnę dodaj jako zapytanie zagnieżdżone, nazwij ją używając aliasu `city`.**
	```SQL
	SELECT employees.firstName, 
		   employees.lastName, 
		   employees.email, 
		   (SELECT offices.city FROM offices WHERE offices.officeCode = employees.officeCode) AS city
	FROM employees
	```
	![[Pasted image 20240326172513.png]]
	<br>

2. **Z tabeli pracowników wyświetl imię, nazwisko i email. Przefiltruj wyniki zwracając tylko pracowników mających biuro w 'Sydney'.**
	```SQL
	SELECT *
	FROM (
	    SELECT employees.firstName, 
	           employees.lastName, 
	           employees.email, 
	           (SELECT offices.city FROM offices WHERE offices.officeCode = employees.officeCode) AS city
	    FROM employees
	) AS subquery
	WHERE city = 'Sydney';
	```
	![[Pasted image 20240326172544.png]]
	<br>

3. **Z tabeli klientów wyświetl nazwę klienta oraz email do przypisanego mu przedstawiciela handlowego. Kolumnę z emailem przedstawiciela dodaj jako zapytanie zagnieżdżone i nadaj jej alias `salesRepEmail`. Tabelom wykrzystywanym w zapytaniu (customers, employees) nadaj aliasy (odpowiednio: c, e) i użyj tych aliasów w warunku WHERE zapytania zagnieżdżonego.**
	```SQL
	SELECT c.customerName,
		   (SELECT e.email FROM employees e WHERE c.salesRepEmployeeNumber = e.employeeNumber) AS salesRepEmail
	FROM customers c
	```
	![[Pasted image 20240326172607.png]]
	<br>

4. **Z tabeli produktów wyświetl nazwy produktów wraz z różnicą pomiędzy ceną sugerowaną `MSRP`, a ceną zakupu `buyPrice`. Nazwij kolumnę z różnicą używając aliasu `roznica`. Posortuj wyniki wg różnicy (używając aliasu).**
    ```SQL
    SELECT products.productName, products.MSRP - products.buyPrice AS roznica
    FROM products
    ORDER BY roznica
    ```
    ![[Pasted image 20240326172632.png]]
    a) **Przefiltruj wcześniejsze zapytanie - wyświetl tylko produkty, dla których wartość różnicy jest większa od 50. Zastosuj alias w warunku WHERE.**
	```SQL
	SELECT *
	FROM (
		SELECT products.productCode, products.MSRP - products.buyPrice AS roznica
		FROM products
	) AS subquery
	WHERE roznica > 50
	```
	![[Pasted image 20240408144232.png]]
	<br>
	
5. **Z tabeli `customers` pobierz nazwy klientów `customerName`. W wynikach umieść kolumnę jako podzapytanie, które dla każdego klienta pokaże sumę jego wszystkich płatności. Nazwij tę kolumnę używając aliasu `suma`.**
	```SQL
	SELECT customers.customerName,
		   (SELECT SUM(payments.amount) FROM payments WHERE customers.customerNumber = payments.customerNumber) AS suma
	FROM customers
	```
	![[Pasted image 20240326174552.png]]
	a) **Przefiltruj poprzednie zapytanie nakładając warunek na sumę (suma > 100000) oraz posortuj wyniki wg sumy.**
	```SQL
	SELECT *
	FROM (
		SELECT customers.customerName,
			   (SELECT SUM(payments.amount) FROM payments WHERE customers.customerNumber = payments.customerNumber) AS suma
		FROM customers
	) AS subquery
	WHERE suma > 100000
	ORDER BY suma
	```
	![[Pasted image 20240326174528.png]]
	<br>

6. **Utwórz tablicę z kolumną zawierającą wszystkie nazwiska z bazy (nazwiska zarówno pracowników jak i przedstawicieli klientów).**
	```SQL
	SELECT customers.contactLastName AS lastName
	FROM customers
	UNION ALL
	SELECT employees.lastName AS lastName
	FROM employees
	```
	![[Pasted image 20240408140017.png]]
	a) **Sprawdź ile razy pojawia się każde nazwisko. Dodaj kolumnę wykorzystującą funkcję COUNT().**
	```SQL
	SELECT lastName, COUNT(*)
	FROM (SELECT customers.contactLastName AS lastName
	      FROM customers
	      UNION ALL
	      SELECT employees.lastName AS lastName
	      FROM employees
	) AS subquery
	GROUP BY lastName
	```
	![[Pasted image 20240408140130.png]]
	b) **Ogranicz wyniki tylko do nazwisk które pojawiają się więcej niż raz. Całość ułóż od najczęściej występującego nazwiska.**
	```SQL
	SELECT lastName, COUNT(*)
	FROM (SELECT customers.contactLastName AS lastName
	      FROM customers
	      UNION ALL
	      SELECT employees.lastName AS lastName
	      FROM employees
	) AS subquery
	GROUP BY lastName
	HAVING COUNT(*) > 1
	ORDER BY COUNT(*) DESC
	```
	![[Pasted image 20240408140255.png]]
	c) **Teraz pokaż nazwiska oraz imiona wszystkich osób z bazy, których nazwiska występują więcej niż jeden raz.**
	```SQL
	SELECT nameSurnameData.name, nameSurnameData.lastName,
	       (SELECT COUNT(*)
	        FROM (
	            SELECT customers.contactLastName AS lastName
	            FROM customers
	            UNION ALL
	            SELECT employees.lastName AS lastName
	            FROM employees
	        ) AS subquery
	        WHERE subquery.lastName = nameSurnameData.lastName
	       ) AS count
	FROM (
	      SELECT customers.contactLastName AS lastName, customers.contactFirstName AS name
	      FROM customers
	      UNION ALL
	      SELECT employees.lastName AS lastName, employees.firstName AS name
	      FROM employees
	) AS nameSurnameData
	HAVING count > 1
	```
	![[Pasted image 20240408142201.png]]
	d) **Teraz pokaż nazwiska, imiona oraz miasta w których pracują wszystkie osoby, których nazwiska występują w bazie więcej niż jeden raz.**
	```SQL
	SELECT peoplesData.lastName, peoplesData.firstName, peoplesData.city, counts.count
	FROM (
	     SELECT employees.lastName as lastName, employees.firstName as firstName, offices.city AS city
	     FROM employees
	     JOIN offices ON employees.officeCode = offices.officeCode
	     UNION ALL
	     SELECT customers.contactLastName as lastName, customers.contactFirstName as firstName, customers.city AS city
	     FROM customers
	) AS peoplesData
	JOIN (
	     SELECT lastName, COUNT(*) AS count
	     FROM (
			  SELECT customers.contactLastName AS lastName
	          FROM customers
	          UNION ALL
	          SELECT employees.lastName AS lastName
	          FROM employees
		 ) AS countsSubquery
	     GROUP BY lastName
	     HAVING count > 1
	) AS counts ON peoplesData.lastName = counts.lastName
	ORDER BY counts.count DESC
	```
	![[Pasted image 20240408143051.png]]
