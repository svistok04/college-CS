Zdefiniuj funkcję wbudowaną, która dla podanej wartości numeru klienta z tabeli `customers` zwróci wartość tekstową zawierającą połączone imię i nazwisko osoby kontaktowej.
```SQL
CREATE FUNCTION contactPerson(customerNumber INT)
RETURNS VARCHAR(255)
DETERMINISTIC
RETURN (
   SELECT concat(contactFirstName, ' ', contactLastName)
   FROM customers
   WHERE customers.customerNumber=customerNumber 
);
```

Stwórz polecenie SELECT wykorzystujące utworzoną funkcję. Wyświetl zwracane przez nią wartości obok wartości kolumn `contactFirstName` oraz `contactLastName`.
```SQL
SELECT contactFirstName, contactLastName, contactPerson(customerNumber) FROM customers
```

 Zdefiniuj funkcję wbudowaną, która na podstawie podanej wartości zmiennoprzecinkowej zwróci jej wartość słowną wg następujących warunków:
wartość mniejsza od 100000 jako 'mały'
wartość większa równa 100000 i mniejsza od 200000 jako 'średni'
w pozostałym przypadku 'duży;
Nazwij funkcję limitKredytowy i zdefiniuj ją w następujących wariantach
2a) ciało funkcji składa się z pojedynczej instrukcji SELECT CASE
```SQL
CREATE OR REPLACE FUNCTION limitKredytowy(kwota DOUBLE)
RETURNS VARCHAR(10)
DETERMINISTIC
RETURN (
    SELECT CASE
    	WHEN kwota < 100000 THEN 'maly'
    	WHEN kwota >= 100000 AND kwota < 200000 THEN 'sredni'
    	ELSE 'duzy'
    END
    )
```
2b) ciało funkcji składa się z bloku (BEGIN END), w którym instrukcja CASE zwraca wartość przy pierwszym spełnionym warunku WHEN
```SQL
DELIMITER //
CREATE OR REPLACE FUNCTION limitKredytowy(kwota DOUBLE)
RETURNS VARCHAR(10)
DETERMINISTIC
BEGIN
	CASE
      WHEN kwota < 100000 THEN RETURN 'mały';
      WHEN kwota >= 100000 AND kwota < 200000 THEN RETURN 'średni';
      ELSE RETURN 'duży';
    END CASE;
END  //
DELIMITER ;
```
2c) ciało funkcji składa się z bloku (BEGIN END), w którym instrukcja CASE przepisuje wynik do lokalnej zmiennej, której wartość jest zwracana po zakończeniu instrukcji CASE
```SQL
DELIMITER //
CREATE OR REPLACE FUNCTION limitKredytowy(kwota DOUBLE)
RETURNS VARCHAR(10)
DETERMINISTIC
BEGIN
    DECLARE returnVal VARCHAR(10);
    CASE
        WHEN kwota < 100000 THEN SET returnVal = 'maly';
        WHEN kwota >= 100000 AND kwota < 200000 THEN SET returnVal = 'sredni';
        ELSE SET returnVal = 'duzy';
    END CASE;
    RETURN returnVal;
END //
DELIMITER ;
```

Stwórz polecenie SELECT używające stworzonej funkcji limitKredytowy dla pola `creditLimit` w tabeli `customers`. Wyświetl jej wartość dla wszystkich rekordów tej tabeli.
```SQL
SELECT limitKredytowy(creditLimit), creditLimit
FROM customers
```

Przeanalizuj ponownie definicje zaprojektowane w punktach 1 i 2. Zastanów się czy powinien być w nich użyty modyfikator DETERMINISTIC czy NOT DETERMINISTIC? Jaka jest między nimi różnica?
```SQL
DELIMITER //
CREATE OR REPLACE FUNCTION wskaznik(a DOUBLE, b DOUBLE)
RETURNS DOUBLE
DETERMINISTIC
BEGIN
    DECLARE wynik DOUBLE;
    SET wynik = (a + b) * (2 * a + b);
    SET wynik = MOD(wynik, 10);
    IF wynik < 5 THEN SET wynik = wynik / 10;
    ELSE SET wynik = (1 + (wynik / 10));
    END IF;
    RETURN wynik;
END //
DELIMITER ;
```