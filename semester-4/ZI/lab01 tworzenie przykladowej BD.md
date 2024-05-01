# Celem zadania było stworzenie bazy danych dla sklepu internetowego z elementami normalizacji.

Ta baza danych musi obejmować: klientów, zamówienia, detali zamówień, produkty i płatności.

![[Pasted image 20240227113304.png]]

1. **Tabela `customers`**: Zawiera informacje o klientach. Zawiera unikalny numer identyfikacyjny klienta (`customerNumber`), nazwę klienta (`customerName`), informacje kontaktowe (takie jak `contactLastName`, `contactFirstName`, `phone`), adres (w tym `addressLine1`, `addressLine2`, `city`, `state`, `postalCode`, `country`) oraz limit kredytowy (`creditLimit`). Klucz główny tabeli to `customerNumber`
![[Pasted image 20240227113501.png]]

2. **Tabela `orders`**: Zawiera informacje na temat zamówień złożonych przez klientów, tj. numer zamówienia (`orderNumber`), datę złożenia zamówienia (`orderDate`), numer identyfikacyjny klienta (`customerNumber`), metod przesyłki (`shippingMethod`), status zamówienia (`orderStatus`) oraz komentarz do zamówienia (`orderComment`). Tabela ta jest również powiązana z tabelą `customers` poprzez klucz obcy `customerNumber`, co pozwala śledzić, który klient złożył dane zamówienie. Klucz główny tabeli to `orderNumber`
![[Pasted image 20240227113517.png]]

3. **Tabela `orderdetails`**: Zawiera szczegółowe informacje dotyczące poszczególnych produktów zamówionych w ramach każdego zamówienia, takie jak numer zamówienia (`orderNumber`), numer produktu (`productNumber`), ilość zamówionych produktów (`quantityOrdered`) oraz cenę za sztukę (`priceForOne`). Tabela ta jest powiązana z `orders` i `products` poprzez klucze obce `orderNumber` i `productNumber` odpowiednio, co pozwala określić, do jakiego zamówienia należą szczegóły i jakie produkty zostały zamówione w ramach każdego zamówienia.
![[Pasted image 20240227113606.png]]

4. **Tabela `payments`**: Zawiera informacje o płatnościach dokonanych przez klientów. Składa się z numeru klienta (`customerNumber`), daty płatności (`paymentDate`) oraz kwoty płatności (`amount`). Każdy rekord jest unikatowo identyfikowany przez kombinację `customerNumber` i `paymentDate`. Tabela ta jest połączona z tabelą `customers` poprzez klucz obcy `customerNumber`.
![[Pasted image 20240227113639.png]]

5. **Tabela `products`**: Zawiera informacje o produktach. Zawiera numer produktu (`productNumber`), nazwę (`productName`), opis (`productDescription`), ilość na stanie (`quantityInStock`) oraz cenę zakupu (`buyPrice`). Klucz główny to `productNumber`.
![[Pasted image 20240227113621.png]]


**Podsumowanie**: udało się stworzyć znormalizowaną bazę danych dla sklepu internetowego, uwzlędniającą pięć tabeli (`customers`, `orders`, `orderdetails`, `products` i `payments`). Każda z tych tabel przechowuje określone informacje, takie jak dane klientów, szczegóły zamówień i produktów oraz płatności, co wraz z relacjami między poszczegółnymi kluczami tabel tworzy system zarządzania informacjami niezbędnymi dla funkcjonowania sklepu internetowego. 