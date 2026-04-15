task b
WINDOW A
![[Pasted image 20240603144839.png]]
WINDOW B
![[Pasted image 20240603144852.png]]
WINDOW A
![[Pasted image 20240603144906.png]]
WINDOW B
![[Pasted image 20240603144922.png]]
WINDOW A
![[Pasted image 20240603144932.png]]


task c
WINDOW B
![[Pasted image 20240603144950.png]]
WINDOW A
![[Pasted image 20240603145038.png]]





MariaDB [lab3]> UPDATE customers SET creditLimit = creditLimit - 1000 WHERE customerNumber = 496; -- c  
Query OK, 1 row affected (0.000 sec)  
Rows matched: 1  Changed: 1  Warnings: 0  
  
MariaDB [lab3]> UPDATE customers SET creditLimit = creditLimit + 1000 WHERE customerNumber = 495; -- c  
Query OK, 1 row affected (0.000 sec)  
Rows matched: 1  Changed: 1  Warnings: 0