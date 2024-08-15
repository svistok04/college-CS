1a) **Zaprojektuj zapytanie select, które policzy liczbę pozycji zamówienia oraz wartość zamówienia każdego zamówienia.**
```SQL
SELECT orderNumber, COUNT(*) AS liczba_pozycji, SUM(orderdetails.priceEach * orderdetails.quantityOrdered) AS wartosc
FROM orderdetails
GROUP BY orderNumber
```

1b) **Wyjaśnij (explain) to polecenie i sprawdź z czy korzysta z indeksu.**
![[Pasted image 20240513140802.png]]

1c) **Utwórz widok na podstawie tego zapytania i nazwij go wartoscizamowien**
```SQL
CREATE VIEW wartoscizamowien AS
SELECT orderNumber, COUNT(*) AS liczba_pozycji, SUM(orderdetails.priceEach * orderdetails.quantityOrdered) AS wartosc
FROM orderdetails
GROUP BY orderNumber
```

1d) **Utwórz zapytanie select korzystając z utworzonego widoku. Wywołaj je bez oraz z warunkiem WHERE (np. liczba pozycji w zamówieniu mniejsza od 10).**
```SQL
SELECT * 
FROM wartoscizamowien
WHERE liczba_pozycji < 10
```
![[Pasted image 20240513141018.png]]
![[Pasted image 20240513141029.png]]

1e) **Dodaj pojedynczy wpis do tabeli `orderdetails` dla wybranego nr zamówienia `orderNumber`. Sprawdź, czy ma to wpływ na wartości zwracane przez widok.**
```SQL
INSERT INTO `orderdetails` (`orderNumber`, `productCode`, `quantityOrdered`, `priceEach`, `orderLineNumber`) VALUES (10101, 'S18_4600', 1, '95.06', 1)
```
![[Pasted image 20240513142647.png]]

1f) **Stwórz select, który połączy widok z tabelą `orders`, tak aby oprócz standardowych kolumn z widoku wyświetlała się także data zamówienia i status.**
```SQL
SELECT wartoscizamowien.*, orders.shippedDate, orders.status
FROM wartoscizamowien
JOIN orders ON wartoscizamowien.orderNumber = orders.orderNumber
```

2a) **Utwórz zapytanie grupujące pozycje zamówiania wg ich liczebności (quantityOrdered)**
```SQL
SELECT *
FROM orderdetails
GROUP BY quantityOrdered
```

2b) **Wyjaśnij (explain) to zapytanie. Sprawdź, czy korzysta z indeksów.**
![[Pasted image 20240513143128.png]]

2c) **Dodaj do tabeli `orderDetails` indeks, który usprawni operację grupowania. Następnie ponownie wyjaśnij zapytanie z 2b i sprawdź użycie indeksu.**
![[Pasted image 20240513143737.png]]

2d) **Utwórz widok dla zapytania z pkt. 2a. Nazwij go `quantityorderderdcounts`**
```SQL
CREATE VIEW quantityorderderdcounts AS 
SELECT COUNT(*) AS liczba_pozycji, quantityOrdered 
FROM orderdetails
GROUP BY quantityOrdered
ORDER by quantityOrdered
```

3a) **W tabeli `offices` utwórz indeks, który usprawni zapytania zawierające w warunku WHERE odwołania do kolumn `country` oraz `state`, np. SELECT * FROM `offices` WHERE `country`='USA' and `state`='CA'**
```SQL
ALTER TABLE offices ADD INDEX country_state (`country`, `state`);
```

3b) **Sprawdź różne warianty zapytania select odwołujące się do tych kolumn w warunku WHERE – sprawdź różną kolejność ich występowania oraz przypadki użycia tylko pojedynczych kolumn. Użyj polecenia EXPLAIN z tymi zapytaniami i sprawdź, w których przypadkach wykorzystywany jest stworzony indeks.**
```SQL
EXPLAIN
SELECT * 
FROM offices
WHERE country = 'USA' AND state = 'CA'
```
![[Pasted image 20240513145253.png]]
```SQL
EXPLAIN
SELECT * 
FROM offices
WHERE country = 'Japan'
```
![[Pasted image 20240513145354.png]]

4)**Utwórz jednoznaczny indeks w tabeli klientów `customers`, który wykluczy możliwość istnienia takiej samej osoby kontaktowej (takie same imię, nazwisko oraz numer telefonu) u dwóch lub większej liczby klientów**
```SQL
ALTER TABLE customers ADD UNIQUE INDEX name_lastname_phone(`contactFirstName`, `contactLastName`, `phone`)
```

5a) **Utwórz widok zwracający trzy przykładowe nazwy kraju w kolumnie nazwanej `country`. Widok nie powinien odwoływać się do żadnej z istniejących w bazie tabel.**
```SQL
CREATE VIEW randomCountries(country) AS 
SELECT 'Germany'
UNION
SELECT 'France'
UNION 
SELECT 'Poland'
```

5b) **Zmodyfikuj widok, tak aby zwracał inny zestaw nazw krajów.**
```SQL
CREATE OR REPLACE VIEW randomCountries(country) AS 
SELECT 'Spain'
UNION
SELECT 'UK'
UNION 
SELECT 'Italy'
```

5c) **Stwórz zapytanie do tabeli `customers` wyświetlające klientów tylko z krajów zwracanych przez ten widok**
```SQL
SELECT *
FROM customers
WHERE country IN (SELECT country FROM randomCountries)
```