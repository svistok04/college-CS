-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 14, 2024 at 07:13 PM
-- Server version: 10.6.16-MariaDB-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cw_aud`
--

-- --------------------------------------------------------

--
-- Table structure for table `DetaleZamowien_2FN`
--

CREATE TABLE `DetaleZamowien_2FN` (
  `IDDetali` int(11) NOT NULL,
  `IDZamowienia` int(11) NOT NULL,
  `IDProduktu` int(11) NOT NULL,
  `LiczbaSztuk` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `DetaleZamowien_2FN`
--

INSERT INTO `DetaleZamowien_2FN` (`IDDetali`, `IDZamowienia`, `IDProduktu`, `LiczbaSztuk`) VALUES
(1, 101, 1, 4),
(2, 102, 2, 4),
(3, 103, 2, 4),
(4, 104, 3, 1),
(5, 105, 4, 1);

-- --------------------------------------------------------

--
-- Table structure for table `DetaleZamowien_3FN`
--

CREATE TABLE `DetaleZamowien_3FN` (
  `IDDetali` int(11) NOT NULL,
  `IDZamowienia` int(11) NOT NULL,
  `IDProduktu` int(11) NOT NULL,
  `LiczbaSztuk` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `DetaleZamowien_3FN`
--

INSERT INTO `DetaleZamowien_3FN` (`IDDetali`, `IDZamowienia`, `IDProduktu`, `LiczbaSztuk`) VALUES
(1, 101, 1, 4),
(2, 102, 2, 4),
(3, 103, 2, 4),
(4, 104, 3, 1),
(5, 105, 4, 1);

-- --------------------------------------------------------

--
-- Table structure for table `Klient_2FN`
--

CREATE TABLE `Klient_2FN` (
  `IDKlienta` int(11) NOT NULL,
  `Imie` varchar(255) NOT NULL,
  `Nazwisko` varchar(255) NOT NULL,
  `Adres` varchar(255) NOT NULL,
  `KodPocztowy` varchar(10) NOT NULL,
  `Miasto` varchar(255) NOT NULL,
  `Wojewodztwo` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Klient_2FN`
--

INSERT INTO `Klient_2FN` (`IDKlienta`, `Imie`, `Nazwisko`, `Adres`, `KodPocztowy`, `Miasto`, `Wojewodztwo`) VALUES
(1, 'Jan', 'Kowalski', 'ul. Jana Pawła 12', '61-600', 'Poznań', 'Wielkopolskie'),
(2, 'Anna', 'Dymna', 'ul. Staszica 1', '30-600', 'Kraków', 'Małopolskie'),
(3, 'Piotr', 'Wawrzyniak', 'al. Niepodległości 1', '30-600', 'Kraków', 'Małopolskie'),
(4, 'Jan', 'Kowalski', 'ul. Poznańska 8', '21-120', 'Wrocław', 'Dolnośląskie');

-- --------------------------------------------------------

--
-- Table structure for table `Klient_3FN`
--

CREATE TABLE `Klient_3FN` (
  `IDKlienta` int(11) NOT NULL,
  `Imie` varchar(255) NOT NULL,
  `Nazwisko` varchar(255) NOT NULL,
  `Adres` varchar(255) NOT NULL,
  `KodPocztowy` varchar(10) NOT NULL,
  `IDMiasta` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Klient_3FN`
--

INSERT INTO `Klient_3FN` (`IDKlienta`, `Imie`, `Nazwisko`, `Adres`, `KodPocztowy`, `IDMiasta`) VALUES
(1, 'Jan', 'Kowalski', 'ul. Jana Pawła 12', '61-600', 1),
(2, 'Anna', 'Dymna', 'ul. Staszica 1', '30-600', 2),
(3, 'Piotr', 'Wawrzyniak', 'al. Niepodległości 1', '30-600', 1),
(4, 'Jan', 'Kowalski', 'ul. Poznańska 8', '21-120', 3);

-- --------------------------------------------------------

--
-- Table structure for table `Miasta_3FN`
--

CREATE TABLE `Miasta_3FN` (
  `IDMiasta` int(11) NOT NULL,
  `NazwaMiasta` varchar(255) NOT NULL,
  `IDWojewodztwa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Miasta_3FN`
--

INSERT INTO `Miasta_3FN` (`IDMiasta`, `NazwaMiasta`, `IDWojewodztwa`) VALUES
(1, 'Poznań', 1),
(2, 'Kraków', 2),
(3, 'Wrocław', 3);

-- --------------------------------------------------------

--
-- Table structure for table `Produkty_2FN`
--

CREATE TABLE `Produkty_2FN` (
  `IDProduktu` int(11) NOT NULL,
  `ModelTowaru` varchar(255) NOT NULL,
  `CenaZaSzt` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Produkty_2FN`
--

INSERT INTO `Produkty_2FN` (`IDProduktu`, `ModelTowaru`, `CenaZaSzt`) VALUES
(1, 'Opony 205 R16', '300.00'),
(2, 'Alufelgi Silver', '550.00'),
(3, 'Komplet żarówek', '80.00'),
(4, 'Trójkąt ostrzegawczy', '15.00');

-- --------------------------------------------------------

--
-- Table structure for table `Produkty_3FN`
--

CREATE TABLE `Produkty_3FN` (
  `IDProduktu` int(11) NOT NULL,
  `ModelTowaru` varchar(255) NOT NULL,
  `CenaZaSzt` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Produkty_3FN`
--

INSERT INTO `Produkty_3FN` (`IDProduktu`, `ModelTowaru`, `CenaZaSzt`) VALUES
(1, 'Opony 205 R16', '300.00'),
(2, 'Alufelgi Silver', '550.00'),
(3, 'Komplet żarówek', '80.00'),
(4, 'Trójkąt ostrzegawczy', '15.00');

-- --------------------------------------------------------

--
-- Table structure for table `Wojewodztwa_3FN`
--

CREATE TABLE `Wojewodztwa_3FN` (
  `IDWojewodztwa` int(11) NOT NULL,
  `NazwaWojewodztwa` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Wojewodztwa_3FN`
--

INSERT INTO `Wojewodztwa_3FN` (`IDWojewodztwa`, `NazwaWojewodztwa`) VALUES
(1, 'Wielkopolskie'),
(2, 'Małopolskie'),
(3, 'Dolnośląskie');

-- --------------------------------------------------------

--
-- Table structure for table `Zamowienia_1FN`
--

CREATE TABLE `Zamowienia_1FN` (
  `NumerZam` int(11) NOT NULL,
  `NazwaKlienta` varchar(255) DEFAULT NULL,
  `Adres` varchar(255) DEFAULT NULL,
  `KodPocztowy` varchar(10) DEFAULT NULL,
  `Miasto` varchar(255) DEFAULT NULL,
  `Wojewodztwo` varchar(255) DEFAULT NULL,
  `DataZamowienia` date DEFAULT NULL,
  `ModelTowaru` varchar(255) DEFAULT NULL,
  `LiczbaSztuk` int(11) DEFAULT NULL,
  `CenaZaSzt` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Zamowienia_1FN`
--

INSERT INTO `Zamowienia_1FN` (`NumerZam`, `NazwaKlienta`, `Adres`, `KodPocztowy`, `Miasto`, `Wojewodztwo`, `DataZamowienia`, `ModelTowaru`, `LiczbaSztuk`, `CenaZaSzt`) VALUES
(101, 'Jan Kowalski', 'ul. Jana Pawła 12', '61-600', 'Poznań', 'Wielkopolskie', '2012-01-02', 'Opony 205 R16', 4, '300.00'),
(102, 'Anna Dymna', 'ul. Staszica 1', '30-600', 'Kraków', 'Małopolskie', '2012-03-22', 'Alufelgi Silver', 4, '550.00'),
(103, 'Piotr Wawrzyniak', 'al. Niepodległości 1', '30-600', 'Kraków', 'Małopolskie', '2012-03-22', 'Alufelgi Silver', 4, '550.00'),
(104, 'Jan Kowalski', 'ul. Jana Pawła 12', '61-600', 'Poznań', 'Wielkopolskie', '2012-10-22', 'Komplet żarówek', 1, '80.00'),
(105, 'Jan Kowalski', 'ul. Poznańska 8', '21-120', 'Wrocław', 'Dolnośląskie', '2012-05-22', 'Trójkąt ostrzegawczy', 1, '15.00');

-- --------------------------------------------------------

--
-- Table structure for table `Zamowienia_2FN`
--

CREATE TABLE `Zamowienia_2FN` (
  `IDZamowienia` int(11) NOT NULL,
  `IDKlienta` int(11) NOT NULL,
  `DataZamowienia` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Zamowienia_2FN`
--

INSERT INTO `Zamowienia_2FN` (`IDZamowienia`, `IDKlienta`, `DataZamowienia`) VALUES
(101, 1, '2012-01-02'),
(102, 2, '2012-03-22'),
(103, 3, '2012-03-22'),
(104, 1, '2012-10-22'),
(105, 4, '2012-05-22');

-- --------------------------------------------------------

--
-- Table structure for table `Zamowienia_3FN`
--

CREATE TABLE `Zamowienia_3FN` (
  `IDZamowienia` int(11) NOT NULL,
  `IDKlienta` int(11) NOT NULL,
  `DataZamowienia` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Zamowienia_3FN`
--

INSERT INTO `Zamowienia_3FN` (`IDZamowienia`, `IDKlienta`, `DataZamowienia`) VALUES
(101, 1, '2012-01-02'),
(102, 2, '2012-03-22'),
(103, 3, '2012-03-22'),
(104, 1, '2012-10-22'),
(105, 4, '2012-05-22');

-- --------------------------------------------------------

--
-- Table structure for table `Zamowienia_UNF`
--

CREATE TABLE `Zamowienia_UNF` (
  `NumerZam` int(11) NOT NULL,
  `NazwaKlienta` varchar(30) DEFAULT NULL,
  `AdresKlienta` varchar(255) DEFAULT NULL,
  `DataZamowienia` date NOT NULL,
  `SzczegolyZamowienia` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Zamowienia_UNF`
--

INSERT INTO `Zamowienia_UNF` (`NumerZam`, `NazwaKlienta`, `AdresKlienta`, `DataZamowienia`, `SzczegolyZamowienia`) VALUES
(101, 'Jan Kowalski', 'ul. Jana Pawła 12, 61-600 Poznań, woj. Wielkopolskie', '2012-01-02', 'Opony 205 R16 4szt, koszt 1200 PLN'),
(102, 'Anna Dymna', 'ul. Staszica 1, 30-600 Kraków, Małopolska', '2012-03-22', 'Alufelgi Silver 4 szt, koszt 2200 PLN'),
(103, 'Piotr Wawrzyniak', 'al. Niepodległości 1, 30-600 Kraków, woj. Małopolskie', '2012-03-22', 'Alufelgi Silver 4 szt, koszt 2200 PLN'),
(104, 'Jan Kowalski', 'ul. Jana Pawła 12, 61-600 Poznań, woj. Wielkopolskie', '2012-10-22', 'Komplet żarówek, koszt 80 PLN'),
(105, 'Jan Kowalski', 'ul. Poznańska 8, 21-120 Wrocław, Dolnośląskie', '2012-05-22', 'Trójkąt ostrzegawczy 1szt, koszt 15 PLN');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `DetaleZamowien_2FN`
--
ALTER TABLE `DetaleZamowien_2FN`
  ADD PRIMARY KEY (`IDDetali`),
  ADD KEY `IDZamowienia` (`IDZamowienia`),
  ADD KEY `IDProduktu` (`IDProduktu`);

--
-- Indexes for table `DetaleZamowien_3FN`
--
ALTER TABLE `DetaleZamowien_3FN`
  ADD PRIMARY KEY (`IDDetali`),
  ADD KEY `IDZamowienia` (`IDZamowienia`),
  ADD KEY `IDProduktu` (`IDProduktu`);

--
-- Indexes for table `Klient_2FN`
--
ALTER TABLE `Klient_2FN`
  ADD PRIMARY KEY (`IDKlienta`);

--
-- Indexes for table `Klient_3FN`
--
ALTER TABLE `Klient_3FN`
  ADD PRIMARY KEY (`IDKlienta`),
  ADD KEY `IDMiasta` (`IDMiasta`);

--
-- Indexes for table `Miasta_3FN`
--
ALTER TABLE `Miasta_3FN`
  ADD PRIMARY KEY (`IDMiasta`),
  ADD KEY `IDWojewodztwa` (`IDWojewodztwa`);

--
-- Indexes for table `Produkty_2FN`
--
ALTER TABLE `Produkty_2FN`
  ADD PRIMARY KEY (`IDProduktu`);

--
-- Indexes for table `Produkty_3FN`
--
ALTER TABLE `Produkty_3FN`
  ADD PRIMARY KEY (`IDProduktu`);

--
-- Indexes for table `Wojewodztwa_3FN`
--
ALTER TABLE `Wojewodztwa_3FN`
  ADD PRIMARY KEY (`IDWojewodztwa`);

--
-- Indexes for table `Zamowienia_1FN`
--
ALTER TABLE `Zamowienia_1FN`
  ADD PRIMARY KEY (`NumerZam`);

--
-- Indexes for table `Zamowienia_2FN`
--
ALTER TABLE `Zamowienia_2FN`
  ADD PRIMARY KEY (`IDZamowienia`),
  ADD KEY `IDKlienta` (`IDKlienta`);

--
-- Indexes for table `Zamowienia_3FN`
--
ALTER TABLE `Zamowienia_3FN`
  ADD PRIMARY KEY (`IDZamowienia`),
  ADD KEY `IDKlienta` (`IDKlienta`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `DetaleZamowien_2FN`
--
ALTER TABLE `DetaleZamowien_2FN`
  MODIFY `IDDetali` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `DetaleZamowien_3FN`
--
ALTER TABLE `DetaleZamowien_3FN`
  MODIFY `IDDetali` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `Klient_2FN`
--
ALTER TABLE `Klient_2FN`
  MODIFY `IDKlienta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `Klient_3FN`
--
ALTER TABLE `Klient_3FN`
  MODIFY `IDKlienta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `Miasta_3FN`
--
ALTER TABLE `Miasta_3FN`
  MODIFY `IDMiasta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `Produkty_2FN`
--
ALTER TABLE `Produkty_2FN`
  MODIFY `IDProduktu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `Produkty_3FN`
--
ALTER TABLE `Produkty_3FN`
  MODIFY `IDProduktu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `Wojewodztwa_3FN`
--
ALTER TABLE `Wojewodztwa_3FN`
  MODIFY `IDWojewodztwa` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `Zamowienia_2FN`
--
ALTER TABLE `Zamowienia_2FN`
  MODIFY `IDZamowienia` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=106;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `DetaleZamowien_2FN`
--
ALTER TABLE `DetaleZamowien_2FN`
  ADD CONSTRAINT `DetaleZamowien_2FN_ibfk_1` FOREIGN KEY (`IDZamowienia`) REFERENCES `Zamowienia_2FN` (`IDZamowienia`),
  ADD CONSTRAINT `DetaleZamowien_2FN_ibfk_2` FOREIGN KEY (`IDProduktu`) REFERENCES `Produkty_2FN` (`IDProduktu`);

--
-- Constraints for table `DetaleZamowien_3FN`
--
ALTER TABLE `DetaleZamowien_3FN`
  ADD CONSTRAINT `DetaleZamowien_3FN_ibfk_1` FOREIGN KEY (`IDZamowienia`) REFERENCES `Zamowienia_3FN` (`IDZamowienia`),
  ADD CONSTRAINT `DetaleZamowien_3FN_ibfk_2` FOREIGN KEY (`IDProduktu`) REFERENCES `Produkty_3FN` (`IDProduktu`);

--
-- Constraints for table `Klient_3FN`
--
ALTER TABLE `Klient_3FN`
  ADD CONSTRAINT `Klient_3FN_ibfk_1` FOREIGN KEY (`IDMiasta`) REFERENCES `Miasta_3FN` (`IDMiasta`);

--
-- Constraints for table `Miasta_3FN`
--
ALTER TABLE `Miasta_3FN`
  ADD CONSTRAINT `Miasta_3FN_ibfk_1` FOREIGN KEY (`IDWojewodztwa`) REFERENCES `Wojewodztwa_3FN` (`IDWojewodztwa`);

--
-- Constraints for table `Zamowienia_2FN`
--
ALTER TABLE `Zamowienia_2FN`
  ADD CONSTRAINT `Zamowienia_2FN_ibfk_1` FOREIGN KEY (`IDKlienta`) REFERENCES `Klient_2FN` (`IDKlienta`);

--
-- Constraints for table `Zamowienia_3FN`
--
ALTER TABLE `Zamowienia_3FN`
  ADD CONSTRAINT `Zamowienia_3FN_ibfk_1` FOREIGN KEY (`IDKlienta`) REFERENCES `Klient_3FN` (`IDKlienta`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
