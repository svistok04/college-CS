1. **Połącz tablice produclines oraz products aby uzyskać tablicę zawierającą nazwę produktu ('1968 Ford Mustang') oraz textDescription.**
	```SQL
	SELECT products.productName, productlines.textDescription
	FROM products, productlines
	WHERE products.productName = '1968 Ford Mustang' AND products.productLine = productlines.productLine 
	```
	![[Pasted image 20240325144424.png]]
	<br>

2. **Utwórz identyczną tablicę jak w powyższym zadaniu.**
	```SQL
	SELECT products.productName, productlines.textDescription
	FROM products
	JOIN productlines ON products.productLine = productlines.productLine
	WHERE products.productName = '1968 Ford Mustang';
	```
	![[Pasted image 20240325143657.png]]
	<br>

3. **Dla zamówienia numer 10100 pokaż jego: numer, nazwę zamawiającego klienta, cenę całościową zamówienia oraz status tego zamówienia. Wykorzystaj dowolną z poznanych metod łączenia tablic.**
	```SQL
	SELECT orders.orderNumber, customers.customerName, SUM(orderdetails.quantityOrdered * orderdetails.priceEach), orders.status
	FROM orders 
	JOIN orderdetails ON orders.orderNumber = orderdetails.orderNumber
	JOIN customers ON orders.customerNumber = customers.customerNumber
	WHERE orders.orderNumber = 10100
	```
	![[Pasted image 20240325143636.png]]
	<br>

4. **Znajdź firmę która wydała w sklepie najwięcej pieniędzy. Pokaż nazwę firmy oraz sumę jej wydatków.**
	```SQL
	SELECT customers.customerName, SUM(orderdetails.priceEach * orderdetails.quantityOrdered)
	FROM orders
	LEFT JOIN orderdetails ON orders.orderNumber = orderdetails.orderNumber
	LEFT JOIN customers ON orders.customerNumber = customers.customerNumber
	GROUP BY orders.customerNumber
	ORDER BY SUM(orderdetails.priceEach * orderdetails.quantityOrdered) DESC
	LIMIT 1;
	```
	![[Pasted image 20240325143604.png]]
	<br>
	
5. **Znajdź firmy które dokonały tylko jednej wpłaty(bez względu na liczbę zamówień). Pokaż ich nazwę, oraz wysokość wpłat.**
	```SQL
	SELECT customers.customerName, amount
	FROM payments
	LEFT JOIN customers ON payments.customerNumber = customers.customerNumber
	GROUP BY payments.customerNumber
	HAVING COUNT(*)=1;
	```
	![[Pasted image 20240325143545.png]]
	<br>
	
6. **Pokaż tablicę z kolumną zawierającą wszystkie imiona z bazy danych, czyli imiona przedstawicieli klientów oraz pracowników.**
	```SQL
	SELECT contactFirstName
	FROM customers
	UNION ALL
	SELECT firstName
	FROM employees;
	```
	![[Pasted image 20240325143523.png]]
	<br>
	
7. **Pokaż powyższą tablicę, ale bez powtórzeń.**
	```SQL
	SELECT contactFirstName
	FROM customers
	UNION
	SELECT firstName
	FROM employees;
	```
	![[Pasted image 20240325143507.png]]
	<br>
	
8. **Pokaż wszystkie miasta zarówno z tabeli klienci jak i biura (z powtórzeniami). Uszereguj alfabetycznie.**
	```SQL
	SELECT city
	FROM customers
	UNION ALL
	SELECT city
	FROM offices
	ORDER BY city;
	```
	![[Pasted image 20240325143445.png]]
	<br>
	
9. **Pokaż wszystkie miasta(nazwa - nie numer miasta/biura) oraz liczbę wystąpień danego miasta w bazie (tablice customers i offices). Użyj funkcji COUNT() oraz GROUP BY. Uszereguj od największej liczby wystąpień.**
	```SQL
	SELECT city, COUNT(*)
	FROM (
	    SELECT city 
	    FROM customers
	    UNION ALL
	    SELECT city 
	    FROM offices
	) AS combined
	GROUP BY city
	ORDER BY COUNT(*) DESC;
	```
	![[Pasted image 20240325143353.png]]
	<br>
	
10. **Pokaż imiona i nazwiska wszystkich pracowników oraz nazwę kraju w którym pracują. Wyniki uszereguj alfabetycznie według nazwy kraju.**
	```SQL
	SELECT employees.firstName, employees.lastName, offices.country 
	FROM employees
	JOIN offices ON employees.officeCode = offices.officeCode;
	```
	![[Pasted image 20240325143312.png]]
	<br>
	
11. **Znajdź 10 klientów z największą liczbą zamówień. Pokaż nazwę oraz łączną liczbę złożonych zamówień. Posortuj zamówienia malejąco.**
	```SQL
	SELECT customers.customerName, COUNT(*)
	FROM orders
	LEFT JOIN customers ON orders.customerNumber = customers.customerNumber
	GROUP BY orders.customerNumber
	ORDER BY COUNT(*) DESC
	LIMIT 10;
	```
	![[Pasted image 20240325143239.png]]
	<br>
	
12. **Pokaż imię, nazwisko oraz stanowisko dla każdego pracownika który obsługuje klientów. Dla każdego takiego pracownika pokaż również nazwy przypisanych klientów. Tabelę uporządkuj alfabetycznie nazwą klienta.**
	```SQL
	SELECT employees.firstName, employees.lastName, employees.officeCode, customers.customerName 
	FROM employees 
	INNER JOIN customers ON employees.employeeNumber = customers.salesRepEmployeeNumber 
	ORDER BY customers.customerName
	```
	![[Pasted image 20240325143221.png]]
	<br>
	
13. **Wykonaj ponownie powyższą tabelę, tylko tym razem pokaż również nieprzypisanych klientów.**
	```SQL
	SELECT customers.customerName, employees.firstName, employees.lastName, employees.officeCode
	FROM employees
	RIGHT JOIN customers ON employees.employeeNumber = customers.salesRepEmployeeNumber
	ORDER BY customers.customerName
	```
	![[Pasted image 20240325143146.png]]
	<br>
	
14. **Wykonaj jeszcze raz tą samą tabelę tym razem pokazując wszystkich pracowników.**
	```SQL
	SELECT employees.firstName, employees.lastName, employees.officeCode, customers.customerName
	FROM employees
	LEFT JOIN customers ON employees.employeeNumber = customers.salesRepEmployeeNumber
	ORDER BY customers.customerName
	```
	![[Pasted image 20240325143117.png]]
	<br>
	
15. **Pokaż nazwy wszystkich dostępnych modeli oraz ile sztuka każdego z nich sprzedano. Użyj poniższej funkcji aby nadać domyślną wartość zero, gdy nie sprzedano żadnego egzemplarza.**
	```SQL
	SELECT products.productName, COALESCE(SUM(orderdetails.quantityOrdered), 0)
	FROM products
	LEFT JOIN orderdetails ON products.productCode = orderdetails.productCode
	GROUP BY products.productName
	```
	![[Pasted image 20240325145816.png]]