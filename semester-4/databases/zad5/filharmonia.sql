-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: May 23, 2024 at 10:25 AM
-- Server version: 10.6.16-MariaDB-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `filharmonia`
--

-- --------------------------------------------------------

--
-- Table structure for table `instrument`
--

CREATE TABLE `instrument` (
  `instrument_id` int(11) NOT NULL,
  `nazwa` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `kompozytor`
--

CREATE TABLE `kompozytor` (
  `kompozytor_id` int(11) NOT NULL,
  `imie` varchar(255) NOT NULL,
  `nazwisko` varchar(255) NOT NULL,
  `data_urodzenia` date NOT NULL,
  `data_smierci` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `koncert`
--

CREATE TABLE `koncert` (
  `koncert_id` int(11) NOT NULL,
  `nazwa` varchar(255) NOT NULL,
  `data_czas_rozpoczecia` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `czas_trwania` time NOT NULL,
  `lokalizacja_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `lokalizacja`
--

CREATE TABLE `lokalizacja` (
  `lokalizacja_id` int(11) NOT NULL,
  `nazwa` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `muzyk`
--

CREATE TABLE `muzyk` (
  `muzyk_id` int(11) NOT NULL,
  `imie` varchar(255) NOT NULL,
  `nazwisko` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `obsada`
--

CREATE TABLE `obsada` (
  `obsada_id` int(11) NOT NULL,
  `utwor_id` int(11) NOT NULL,
  `instrument_id` int(11) NOT NULL,
  `muzyk_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `program`
--

CREATE TABLE `program` (
  `program_id` int(11) NOT NULL,
  `koncert_id` int(11) NOT NULL,
  `utwor_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `utwor`
--

CREATE TABLE `utwor` (
  `utwor_id` int(11) NOT NULL,
  `kompozytor_id` int(11) NOT NULL,
  `nazwa` varchar(255) NOT NULL,
  `czas_trwania` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `instrument`
--
ALTER TABLE `instrument`
  ADD PRIMARY KEY (`instrument_id`);

--
-- Indexes for table `kompozytor`
--
ALTER TABLE `kompozytor`
  ADD PRIMARY KEY (`kompozytor_id`);

--
-- Indexes for table `koncert`
--
ALTER TABLE `koncert`
  ADD PRIMARY KEY (`koncert_id`),
  ADD KEY `lokalizacja_id` (`lokalizacja_id`);

--
-- Indexes for table `lokalizacja`
--
ALTER TABLE `lokalizacja`
  ADD PRIMARY KEY (`lokalizacja_id`);

--
-- Indexes for table `muzyk`
--
ALTER TABLE `muzyk`
  ADD PRIMARY KEY (`muzyk_id`);

--
-- Indexes for table `obsada`
--
ALTER TABLE `obsada`
  ADD PRIMARY KEY (`obsada_id`),
  ADD KEY `utwor_id` (`utwor_id`),
  ADD KEY `instrument_id` (`instrument_id`),
  ADD KEY `muzyk_id` (`muzyk_id`);

--
-- Indexes for table `program`
--
ALTER TABLE `program`
  ADD PRIMARY KEY (`program_id`),
  ADD KEY `koncert_id` (`koncert_id`),
  ADD KEY `utwor_id` (`utwor_id`);

--
-- Indexes for table `utwor`
--
ALTER TABLE `utwor`
  ADD PRIMARY KEY (`utwor_id`),
  ADD KEY `kompozytor_id` (`kompozytor_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `instrument`
--
ALTER TABLE `instrument`
  MODIFY `instrument_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `kompozytor`
--
ALTER TABLE `kompozytor`
  MODIFY `kompozytor_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `koncert`
--
ALTER TABLE `koncert`
  MODIFY `koncert_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `lokalizacja`
--
ALTER TABLE `lokalizacja`
  MODIFY `lokalizacja_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `muzyk`
--
ALTER TABLE `muzyk`
  MODIFY `muzyk_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `obsada`
--
ALTER TABLE `obsada`
  MODIFY `obsada_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `program`
--
ALTER TABLE `program`
  MODIFY `program_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `utwor`
--
ALTER TABLE `utwor`
  MODIFY `utwor_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `koncert`
--
ALTER TABLE `koncert`
  ADD CONSTRAINT `koncert_ibfk_1` FOREIGN KEY (`lokalizacja_id`) REFERENCES `lokalizacja` (`lokalizacja_id`);

--
-- Constraints for table `obsada`
--
ALTER TABLE `obsada`
  ADD CONSTRAINT `obsada_ibfk_1` FOREIGN KEY (`utwor_id`) REFERENCES `utwor` (`utwor_id`),
  ADD CONSTRAINT `obsada_ibfk_2` FOREIGN KEY (`instrument_id`) REFERENCES `instrument` (`instrument_id`),
  ADD CONSTRAINT `obsada_ibfk_3` FOREIGN KEY (`muzyk_id`) REFERENCES `muzyk` (`muzyk_id`);

--
-- Constraints for table `program`
--
ALTER TABLE `program`
  ADD CONSTRAINT `program_ibfk_1` FOREIGN KEY (`koncert_id`) REFERENCES `koncert` (`koncert_id`),
  ADD CONSTRAINT `program_ibfk_2` FOREIGN KEY (`utwor_id`) REFERENCES `utwor` (`utwor_id`);

--
-- Constraints for table `utwor`
--
ALTER TABLE `utwor`
  ADD CONSTRAINT `utwor_ibfk_1` FOREIGN KEY (`kompozytor_id`) REFERENCES `kompozytor` (`kompozytor_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
