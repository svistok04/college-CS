1. 
	a) **Podaj dzień, nazwę miesiąca, rok oraz słownie dzień tygodnia dla daty przypadającej za 120 dni od daty bieżącej.**
	```SQL
	SELECT 
	    DAY(DATE_ADD(NOW(), INTERVAL 120 DAY)) AS day,
	    MONTHNAME(DATE_ADD(NOW(), INTERVAL 120 DAY)) AS month,
	    YEAR(DATE_ADD(NOW(), INTERVAL 120 DAY)) AS year,
	    DAYNAME(DATE_ADD(NOW(), INTERVAL 120 DAY)) AS weekday
	```
	![[Pasted image 20240506135726.png]]
	
	b) **Jaki dzień tygodnia przypada 205. dnia tego roku?**
	```SQL
	SELECT DAYNAME(DATE_ADD(MAKEDATE(YEAR(CURDATE()), 1), INTERVAL 204 DAY)) as weekday
	```
	![[Pasted image 20240506135833.png]]
	c) **Podaj datę (w pełnym formacie) otrzymaną po odjęciu 15 tygodni od daty bieżącej.**
	```SQL
	SELECT DATE_ADD(CURDATE(), INTERVAL -15 WEEK) AS 15WeeksAgo
	```
	![[Pasted image 20240506141617.png]]
	
<br>

2. 
	a) **rok, miesiąc-słownie, dzień - dzień_tygodnia_słownie**
	```SQL
	SELECT UPPER(DATE_FORMAT('2024-07-24', '%Y, %M %d - %W')) AS DateOrder
	```
	
	![[Pasted image 20240506141604.png]]
	b) **rok miesiąc_słownie, dzień_tygodnia_słownie**
	```SQL
	SELECT DATE_FORMAT('2024-07-24', '%Y %M, %W') AS DatePayment
	```
	
	![[Pasted image 20240506141539.png]]
	
<br>


3. **Ile czasu upłynie między ’12:01:20’ a ’23:31:10’? W odpowiedzi podaj liczbę
godzin, minut i sekund.**

```SQL
SELECT HOUR(TIMEDIFF('23:31:10', '12:01:20')) AS hours, 
	   MINUTE(TIMEDIFF('23:31:10', '12:01:20')) AS minutes, 
       SECOND(TIMEDIFF('23:31:10', '12:01:20')) AS seconds;
```
![[Pasted image 20240506141516.png]]

<br>

4. **Wybierz zamówienia złożone w piątek, wyniki uporządkuj według miesiąca, a daty
sformatuj w sposób przedstawiony na poniższym rysunku.**
```SQL
SELECT orderNumber, DATE_FORMAT(orderDate, '%W %Y %M %d') AS orderDate, status
FROM  orders
WHERE WEEKDAY(orderDate) = 4
ORDER BY MONTH(orderDate)
```
![[Pasted image 20240506141818.png]]

<br>

5. **Wyszukaj i policz zamówienia złożone między 12 a 15 tygodniem, wyniki przedstaw
dla każdego roku oddzielnie.**
```SQL
SELECT YEAR(orderDate) AS Year, WEEK(orderDate) AS WeekNumber, COUNT(*) AS ilosc_zamowien
FROM orders
WHERE WEEK(orderDate) BETWEEN 12 AND 15
GROUP BY Year, WeekNumber
```
![[Pasted image 20240506142249.png]]

<br>

6. **Utwórz ranking klientów na podstawie dokonanych płatności w IV kwartale
(pokaż 5 najlepszych).**
```SQL
SELECT customers.customerNumber, customers.customerName AS klient, SUM(payments.amount) AS kwota
FROM customers
JOIN payments ON customers.customerNumber = payments.customerNumber
WHERE MONTH(payments.paymentDate) IN (10, 11, 12)
GROUP BY customers.customerNumber
ORDER BY kwota DESC
LIMIT 5;
```
![[Pasted image 20240506142608.png]]

<br>

7. **Utwórz ranking (5 pozycji) zamówień o najdłuższym czasie realizacji zamówienia.**
```SQL
SELECT orderNumber, DATE_FORMAT(orderDate, '%d.%m.%Y'), shippedDate, DATEDIFF(shippedDate, orderDate) AS Dni_do_wysylki
FROM orders
ORDER BY DATEDIFF(shippedDate, orderDate) DESC
WHERE NOT(shippedDate IS NULL)
LIMIT 5
```
![[Pasted image 20240506143938.png]]