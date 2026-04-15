1.  **Z tabeli productlines pokaż nazwę linii produktu oraz jego opis.**
	```SQL
	SELECT productLine, textDescription 
	FROM `productlines`
	```
	![[Pasted image 20240311141132.png]]


2. **Pokaż kraje pochodzenia klientów.**
	```SQL
	SELECT country 
	FROM `customers`
	```
	![[Pasted image 20240311143633.png]]


3. **Pokaż kraje pochodzenia klientów (bez powtórzeń).**
	```SQL
	SELECT DISTINCT country 
	FROM `customers`
	```
	![[Pasted image 20240311141240.png]]


4. **Z tabeli products wybierz produkty, których na stanie jest więcej niż 9000.  Pokaż ich nazwę, kod produktu oraz ilość danego modelu w sklepie.**
	```SQL
	SELECT productName, productCode, quantityInStock
	FROM `products` 
	WHERE quantityInStock>9000
	```
	![[Pasted image 20240311143555.png]]

5. **Z tabeli orders pokaż zamówienia, które zostały anulowane, wstrzymane lub sprawa została rozwiązana. Pokaż status i komentarz zamówienia oraz numer klienta, który złożył dane zamówienie.**
	```SQL
	SELECT status, comments, customerNumber
	FROM `orders` 
	WHERE status IN ('Cancelled', 'On Hold', 'Resolved');
	```
	![[Pasted image 20240311143510.png]]

6. **Z tabeli orderdetails wybierz produkty, dla których ilość zamówienia jest większa niż 80 lub cena jest wyższa niż 200,  przy czym warunki te nie mogą być spełnione jednocześnie.** 
   **Pokaż kod produktu, ilość zamówionych sztuk oraz cenę produktu.**
	```SQL
	SELECT productCode, quantityOrdered, priceEach
	FROM `orderdetails` 
	WHERE (quantityOrdered>80 OR priceEach>200) AND NOT (quantityOrdered>80 AND priceEach>200)
	```
	![[Pasted image 20240311145849.png]]

7. **Pokaż wszystkie niedostarczone zamówienia.**
	```SQL
	SELECT *
	FROM `orders` 
	WHERE shippedDate IS NULL;
	```
	![[Pasted image 20240311143439.png]]

8. **Pokaż wszystkie zamówienia, do których dołączono komentarz.**
	```SQL
	SELECT *
	FROM `orders` 
	WHERE comments IS NOT NULL;
	```
	![[Pasted image 20240311143413.png]]

9. **Z tabeli products pokaż nazwę każdego modelu oraz wartość wszystkich jego egzemplarzy znajdujących się w magazynie. Do wyliczenia wartości wykorzystaj atrybut _buyPrice_, czyli cenę zakupu i stan bieżący produktu (_quantityInStock_). Użyj aliasu do zmiany nazwy nowo powstałej kolumny (_Wartosc_), a otrzymane wyniki zaokrąglij do jednego miejsca po przecinku.**
	```SQL
	SELECT productName, ROUND(quantityInStock*buyPrice, 1) AS Wartosc 
	FROM `products`
	```
	![[Pasted image 20240311144100.png]]

10. **Oulu, Herzlia, Hatfield, Cowes. Pokaż klientów którzy są w krajach w których znajdują się wymienione miasta. Pokaż nazwę, miasto i kraj takiego klienta.**
	```SQL
	SELECT customerName, city, country
	FROM `customers`
	WHERE country IN 
		(SELECT country
	    FROM `customers`
	    WHERE city in ('Oulu', 'Herzlia', 'Hatfield', 'Cowes'));
	```
	![[Pasted image 20240311151222.png]]

11. **Z tabeli customers pokaż nazwy klientów oraz ich kraje, posiadających creditLimit wyższy niż najwyższy creditLimt klienta z UK.**
	```SQL
	SELECT customerName, country
	FROM `customers`
	WHERE creditLimit > ALL
		(SELECT creditLimit
	     FROM `customers`
	     WHERE country = 'UK')
	```
	![[Pasted image 20240311151222.png]]