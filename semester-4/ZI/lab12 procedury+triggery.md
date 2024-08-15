1. Napisz deklarację procedury wykonującej dowolne pojedyncze zapytanie typu SELECT. Przetestuj jej wywołanie.
```SQL
CREATE PROCEDURE example()
	SELECT 1
``` 
```SQL
CALL example()
```

2. Napisz deklarację procedury z **parametrem wejściowym**, wykonującej pojedyncze zapytanie typu SELECT i używające wartości tego parametru w warunku WHERE.
```SQL
CREATE PROCEDURE select_customer_by_id(IN id INT)
    SELECT *
    FROM customers
    WHERE customers.customerNumber = id
```
```SQL
CALL select_customer_by_id(103)
```

3. Napisz deklarację procedury z parametrem wyjściowym, która zlicza rekordy w tabeli `orders` i zwraca tę wartość poprzez parametr procedury. Poćwicz jej wywołania i sposób odczytania zwracanej wartości.
```SQL
CREATE PROCEDURE count_orders(OUT number INT)
	SELECT COUNT(*) INTO number
	FROM orders
```
```SQL
CALL count_orders(@number);
SELECT @number
```

4. Napisz deklarację procedury, która obliczy różnicę w liczbie zamówień i zrealizowanych płatności. Wynik powinien być zwrócony poprzez wyjściowy parametr procedury.
```SQL
DELIMITER //
CREATE OR REPLACE PROCEDURE count_unpaid_orders(OUT number INT)
	BEGIN
	DECLARE orders_number INT;
    DECLARE payments_number INT;
	SELECT COUNT(*) INTO orders_number FROM orders;
	SELECT COUNT(*) INTO payments_number FROM payments;
    SET number = orders_number - payments_number;
    END //
DELIMITER ;
```
```SQL
CALL count_unpaid_orders(@number);
SELECT @number

```
5. Napisz deklarację procedury, która realizuje operację dodania nowego zamówienia na jeden konkretny produktu z jednoczesnym ustaleniem jego ceny sprzedaży.
```SQL
DELIMITER //
CREATE OR REPLACE PROCEDURE order_something(IN customer_number INT, 
                                            IN product_code VARCHAR(20), 
                                            IN quantity INT, 
                                            IN margin_procent DECIMAL(10, 2), 
                                            OUT order_price DECIMAL(10,2))
BEGIN
DECLARE price DECIMAL(10, 2);
DECLARE order_number INT;
SELECT products.buyPrice INTO price FROM products WHERE products.productCode = product_code;
SET price = price * (1.0 + margin_procent) / 100.0;
SELECT MAX(orders.orderNumber) + 1 INTO order_number FROM orders;
INSERT INTO orders(orderNumber, orderDate, requiredDate, status, customerNumber) VALUES(order_number, NOW(), DATE_ADD(NOW(), INTERVAL 1 WEEK), 'In process', customer_number);
INSERT INTO orderdetails VALUES(order_number, product_code, quantity, price, 1);
SET order_price = price * quantity;
END //
DELIMITER ;
```
```SQL
CALL order_something(103, 'S10_1678', 4, 12.5, @order_price);
SELECT @order_price;
```
![[Pasted image 20240527144320.png]]

6. Utwórz wyzwalacz dla tabeli `offices`, który dla każdego nowego rekordu zmieni podaną nazwę kraju na tę samą nazwę, ale pisaną wielkimi literami.
```SQL
CREATE TRIGGER country_uppercase BEFORE INSERT ON offices
FOR EACH ROW
SET NEW.country = UPPER(NEW.country)
```

7. a) Zdefiniuj trigger, który **po dodaniu pozycji zamówienia** (tabela `orderdetails`) obliczy sumę wartości wszystkich pozycji zamówienia i zapisze ją w kolumnie _`orders`.`total`_ właściwego rekordu dla tego zamówienia.
```SQL
DELIMITER //
CREATE OR REPLACE TRIGGER order_total_price_insert AFTER INSERT ON orderdetails
FOR EACH ROW
BEGIN
DECLARE total DECIMAL(10, 2);
SELECT SUM(orderdetails.priceEach * orderdetails.quantityOrdered) INTO total FROM orderdetails 
WHERE orderdetails.orderNumber = NEW.ordernumber;
UPDATE orders SET orders.total = total
WHERE orders.orderNumber = NEW.orderNumber;
END //
DELIMITER ; 
```

7. b) Zdefiniuj trigger, który **po aktualizacji pozycji zamówienia** obliczy sumę wartości wszystkich pozycji zamówienia i zapisze ją w kolumnie `orders`.`total` właściwego rekordu dla tego zamówienia.
```SQL
DELIMITER //
CREATE OR REPLACE TRIGGER order_total_price_update AFTER UPDATE ON orderdetails
FOR EACH ROW
BEGIN
DECLARE total DECIMAL(10, 2);
SELECT SUM(orderdetails.priceEach * orderdetails.quantityOrdered) INTO total FROM orderdetails 
WHERE orderdetails.orderNumber = NEW.ordernumber;
UPDATE orders SET orders.total = total
WHERE orders.orderNumber = NEW.orderNumber;
END //
DELIMITER ; 
```
7. c) Zdefiniuj trigger, który **po usunięciu pozycji zamówienia** obliczy sumę wartości wszystkich pozycji zamówienia i zapisze ją w kolumnie `orders`.`total` właściwego rekordu dla tego zamówienia. Zadbaj o to, aby w przypadku usunięcia ostatniej pozycji danego zamówienia w  `orders`.`total` została wpisana wartość 0.0 (a nie null).
```SQL
DELIMITER //
CREATE OR REPLACE TRIGGER order_total_price_delete AFTER DELETE ON orderdetails
FOR EACH ROW
BEGIN
DECLARE total DECIMAL(10, 2);
SELECT SUM(orderdetails.priceEach * orderdetails.quantityOrdered) INTO total FROM orderdetails 
WHERE orderdetails.orderNumber = OLD.ordernumber;
IF total IS NULL THEN
SET total = 0.0;
END IF;
UPDATE orders SET orders.total = total
WHERE orders.orderNumber = OLD.orderNumber;
END //
DELIMITER ; 
```
