1. Pokaż informacje o nazwie, stanie magazynowym i cenie zakupu produktów
```SQL
SELECT JSON_VALUE(productInformation, '$.productName') AS productName, 
	   JSON_VALUE(productInformation, '$.quantityInStock') AS quantity,
       JSON_VALUE(productInformation, '$.buyPrice') AS `buy price`
FROM productsJSON;
```



2. Pokaż wszystkie produkty o cenie zakupu wyższej od 100
```SQL
SELECT JSON_VALUE(productInformation, '$.productName') AS productName, 
	   JSON_VALUE(productInformation, '$.quantityInStock') AS quantity,
       JSON_VALUE(productInformation, '$.buyPrice') AS `buy price`
FROM productsJSON
WHERE JSON_VALUE(productInformation, '$.buyPrice') > 100;
```



3. Podaj liczbę produktów w każdej kategorii produktów
```SQL
SELECT JSON_VALUE(productInformation, '$.productLine') AS productLine, COUNT(*)
FROM productsJSON
GROUP BY productLine;
```



4. Do wybranych produktów dodaj atrybut numeryczny length zawierający długość produktu
```SQL
UPDATE productsJSON
SET productInformation = JSON_INSERT(productInformation, '$.length', 38.5)
WHERE productCode = 'S10_1949';
UPDATE productsJSON
SET productInformation = JSON_INSERT(productInformation, '$.length', 25.0)
WHERE productCode = 'S18_1589';
```

5. Znajdź wszystkie produkty posiadające informacje o ich długości
```SQL
SELECT *
FROM productsJSON
WHERE JSON_CONTAINS_PATH(productInformation, 'one', '$.length');
```

6. Przygotuj tablicę JSON zawierającą informację o pracownikach każdego z oddziałów. Podaj lokalizację oddziału (miasto) oraz imię i nazwisko każdego z pracowników tam pracujących

```SQL
CREATE TABLE officesemployees AS (
	SELECT city,
    	CONCAT('[', 
               GROUP_CONCAT(JSON_OBJECT('firstName',
                                        firstName,
                                        'lastName',
                                        lastName)
					SEPARATOR ",\n"),
               ']') AS employeesInformation
	FROM offices, employees
	WHERE offices.officeCode = employees.officeCode
    GROUP BY offices.city
);
```