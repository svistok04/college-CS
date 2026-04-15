# <center>Sprawozdanie laboratorium 2</center>

0. Podgotowanie do wykonania zadań
	a) Tworzymy bazę danych: 
	```SQL
	CREATE DATABASE `towary` CHARACTER SET `utf8mb4` COLLATE `utf8mb4_unicode_ci`;
	```
	
	b)Tworzymy tabelę: 
	```SQL
	CREATE TABLE `towary` (
		`Kod` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	    `nazwa` VARCHAR(30) NOT NULL,
	    `ilosc` INT NOT NULL,
	    `cena` DECIMAL(10, 2) NOT NULL
	);
	```
	![[Pasted image 20240304152529.png]]
	
1. Wstawiamy do tabeli dane o towarach:
	```SQL
	INSERT INTO `towary` VALUES (NULL, 'Monitor LCD 21\'\'', 3, 300.50);
	INSERT INTO `towary` VALUES (NULL, 'Monitor LCD 19\'\'', 5, 250.00);
	INSERT INTO `towary` VALUES
	(NULL, 'Monitor LCD 29\'\'', 15, 550.00),
	(NULL, 'Monitor LCD 19\'\'', 30, 300.00),
	(NULL, 'Monitor LCD 21\'\'', 25, 250.00),
	(NULL, 'klawiatura', 15, 67.45),
	(NULL, 'plyta glowna', 20, 350.20),
	(NULL, 'klawiatura', 35, 42.35),
	(NULL, 'mysz bezprzewodowa', 23, 51.00),
	(NULL, 'pamiec SSD', 50, 75.25);
	```
	![[Pasted image 20240304152707.png]]

2. Modyfikujemy strukturę:
	a) Dodajemy nową kolumnę `producent`
	b) Dodajemy nową kolumnę `model`
	```SQL
	ALTER TABLE `towary` ADD COLUMN `producent` VARCHAR(30) NULL AFTER `cena`;
	ALTER TABLE `towary` ADD COLUMN `model` VARCHAR(20) NULL AFTER `producent`;
	```
	![[Pasted image 20240304152754.png]]
	
	c) Uzupełniamy nowe kolumny
	```SQL
	UPDATE `towary` SET `producent`='Toshiba', `model`='NC125' WHERE `Kod`=1;
	UPDATE `towary` SET `producent`='Linea' WHERE `Kod`=2;
	UPDATE `towary` SET `producent`='Bilinea', `model`='MBE124' WHERE `Kod`=3;
	UPDATE `towary` SET `producent`='Sharp' WHERE `Kod`=4;
	UPDATE `towary` SET `producent`='Sharp' WHERE `Kod`=5;
	UPDATE `towary` SET `producent`='producent', `model`='model' WHERE `Kod`=6;
	UPDATE `towary` SET `producent`='Assus' WHERE `Kod`=7;
	UPDATE `towary` SET `producent`='Logitech', `model`='BKE12' WHERE `Kod`=8;
	UPDATE `towary` SET `producent`='AITECH' WHERE `Kod`=9;
	UPDATE `towary` SET `producent`='BIGComp', `model`='OWE12' WHERE `Kod`=10;
	```
	![[Pasted image 20240304152814.png]]

3. Edytujemy dane:
	a) Zmieniamy wartość 'producent' w kolumnie `producent` na 'Sony'
	```SQL
	UPDATE `towary` SET `producent`='Sony' WHERE `producent`='producent'
	```
	b) Zamieniamy wartośći NULL w kolumnie `model` na 'NOWY'
	```SQL
	UPDATE `towary` SET `model`='NOWY' WHERE `model` IS NULL;
	```
	c) Zamieniamy wartośći 'Sharp' w kolumnie `producent` na 'Philips' i zamieniamy wartość 'NC125' w kolumnie `model` na 'BC437'
	```SQL
	UPDATE `towary` SET `producent`='Philips' WHERE `producent`='Sharp';
	UPDATE `towary` SET `model`='BC437' WHERE `model` = 'NC125';
	```
	![[Pasted image 20240304152853.png]]

4. Usuwamy z tabeli pole model 
	```SQL
	ALTER TABLE `towary` DROP COLUMN `model`
	```
	![[Pasted image 20240304152915.png]]

5. Usuwamy rekordy z tabeli, spełniające następujące warunki:
	a) ilość towaru jest mniejsza od 10
	```SQL
	DELETE FROM `towary` WHERE `ilosc`<10;
	```
	![[Pasted image 20240304152957.png]]
	b) nazwa towaru zawiera slowo 'klawiatura':
	```SQL
	DELETE FROM `towary` WHERE `nazwa` LIKE '%klawiatura%';
	```
	![[Pasted image 20240304153017.png]]
	c) cena jest z przedziału (200, 300>:
	```SQL
	 DELETE FROM `towary` WHERE `cena` BETWEEN 200.01 AND 300;``
	```
	![[Pasted image 20240304153046.png]]

6. Usuwamy wszystkie dane z tabeli towary:
	```SQL
	TRUNCATE `towary`;
	```
	![[Pasted image 20240304153109.png]]

7. Usuwamy tabelę towary:
	```SQL
	DROP TABLE `towary`;
	```
	![[Pasted image 20240304153148.png]]
    


**Podsumowanie:** podczas wykonania tego ćwiczenia udało nam się stworzyć bazę danych składajęcą się z jednej tabeli `towary`, ktorą utworzyliśmy, dodaliśmy do niej dane towarów, rozszerzyliśmy o nowe kolumny (atrybuty towarów) i uzupełniliśmy je. Następnie usunęliśmy rekordy spełnające określone założenia, kończąc wyczyszczeniem całej tabeli i jej usunięciem. W trakcie tych ćwiczeń udało nam się nauczyć korzystać z poleceń `CREATE`, `INSERT INTO`, `ALTER TABLE`, `ADD COLUMN`, `UPDATE`, `TRUNCATE`, `DROP` oraz klauzul `SET`, `VALUES`,`WHERE`, `LIKE`.