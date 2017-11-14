-- phpMyAdmin SQL Dump
-- version 4.7.3
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Nov 14, 2017 at 05:24 PM
-- Server version: 10.1.23-MariaDB-9+deb9u1
-- PHP Version: 7.0.19-1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `breakermindkomunikator`
--
CREATE DATABASE IF NOT EXISTS `breakermindkomunikator` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `breakermindkomunikator`;

-- --------------------------------------------------------

--
-- Table structure for table `allowedIP`
--

DROP TABLE IF EXISTS `allowedIP`;
CREATE TABLE IF NOT EXISTS `allowedIP` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `email` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ip_addr` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL,
  `time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `allowedIP`
--

INSERT INTO `allowedIP` (`id`, `email`, `ip_addr`, `time`) VALUES
(1, 'info@qflash.pl', '127.0.0.1', '2017-09-26 21:10:12'),
(2, 'info@qflash.pl', '92.222.7.98', '2017-09-26 21:10:12'),
(3, 'info@qflash.pl', '0.0.0.0', '2017-09-26 21:23:28');

-- --------------------------------------------------------

--
-- Table structure for table `banip`
--

DROP TABLE IF EXISTS `banip`;
CREATE TABLE IF NOT EXISTS `banip` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `ip_address` text COLLATE utf8mb4_unicode_ci,
  `time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `banip`
--

INSERT INTO `banip` (`id`, `ip_address`, `time`) VALUES
(1, '127.0.0.1', '2017-09-27 13:04:28'),
(2, '127.0.0.1', '2017-09-27 13:06:47'),
(3, '127.0.0.1', '2017-09-27 13:22:23'),
(4, '127.0.0.1', '2017-09-27 13:22:40'),
(5, '127.0.0.1', '2017-09-27 13:22:45'),
(6, '127.0.0.1', '2017-09-27 13:22:54'),
(7, '127.0.0.1', '2017-10-02 14:27:12'),
(8, '127.0.0.1', '2017-10-02 14:33:57'),
(9, '127.0.0.1', '2017-10-02 14:37:37'),
(10, '127.0.0.1', '2017-10-02 14:45:41'),
(11, '127.0.0.1', '2017-10-02 14:47:49'),
(12, '127.0.0.1', '2017-10-02 14:49:36'),
(13, '127.0.0.1', '2017-10-02 14:50:46'),
(14, '127.0.0.1', '2017-10-02 14:52:03'),
(15, '127.0.0.1', '2017-10-02 14:52:23'),
(16, '127.0.0.1', '2017-10-02 14:52:54'),
(17, '127.0.0.1', '2017-10-02 15:30:17'),
(18, '127.0.0.1', '2017-10-02 15:34:59'),
(19, '127.0.0.1', '2017-10-02 15:35:58'),
(20, '127.0.0.1', '2017-10-02 15:37:06');

-- --------------------------------------------------------

--
-- Table structure for table `contacts`
--

DROP TABLE IF EXISTS `contacts`;
CREATE TABLE IF NOT EXISTS `contacts` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `mailboxid` bigint(20) NOT NULL DEFAULT '0',
  `name` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci,
  `time` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `domains`
--

DROP TABLE IF EXISTS `domains`;
CREATE TABLE IF NOT EXISTS `domains` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `domainname` varchar(180) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT '',
  `active` int(11) DEFAULT '1',
  `ban` int(11) DEFAULT '0',
  `time` datetime DEFAULT CURRENT_TIMESTAMP,
  `dkim_key` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `dkim_selector` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `dkim_active` int(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `domainname` (`domainname`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `domains`
--

INSERT INTO `domains` (`id`, `domainname`, `description`, `active`, `ban`, `time`, `dkim_key`, `dkim_selector`, `dkim_active`) VALUES
(1, 'qflash.pl', 'Domena demo', 1, 0, '2017-09-21 12:21:09', '', '', 1);

-- --------------------------------------------------------

--
-- Table structure for table `mailbox`
--

DROP TABLE IF EXISTS `mailbox`;
CREATE TABLE IF NOT EXISTS `mailbox` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `email` varchar(255) NOT NULL,
  `pass` varchar(255) NOT NULL,
  `name` varchar(255) DEFAULT '',
  `active` int(11) DEFAULT '1',
  `ban` int(11) DEFAULT '0',
  `time` datetime DEFAULT CURRENT_TIMESTAMP,
  `auth_ip_list` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=91 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `mailbox`
--

INSERT INTO `mailbox` (`id`, `email`, `pass`, `name`, `active`, `ban`, `time`, `auth_ip_list`) VALUES
(1, 'demo@breakermind.com', '1a1dc91c907325c69271ddf0c944bc72', 'BreakermindSMTP', 1, 0, '2017-08-17 12:54:40', ''),
(9, 'hello@qflash.pl', '1a1dc91c907325c69271ddf0c944bc72', 'Hello qflash', 1, 0, '2017-08-20 15:51:06', ''),
(90, 'info@qflash.pl', '1a1dc91c907325c69271ddf0c944bc72', 'Info', 1, 0, '2017-08-24 20:01:46', '');

-- --------------------------------------------------------

--
-- Table structure for table `messages`
--

DROP TABLE IF EXISTS `messages`;
CREATE TABLE IF NOT EXISTS `messages` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `efrom` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `efromname` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `subject` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `message` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `seen` int(1) NOT NULL DEFAULT '0',
  `active` int(1) NOT NULL DEFAULT '1',
  `hide_from` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `messages`
--

INSERT INTO `messages` (`id`, `efrom`, `efromname`, `subject`, `message`, `time`, `seen`, `active`, `hide_from`) VALUES
(1, 'info@qflash.pl', 'Qflash.pl', 'hello@qflash.pl', 'asf safsafas fsa fsa fas fsa fsa fas fas', '2017-11-14 16:53:05', 1, 1, 0);

-- --------------------------------------------------------

--
-- Table structure for table `messages_single`
--

DROP TABLE IF EXISTS `messages_single`;
CREATE TABLE IF NOT EXISTS `messages_single` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `efrom` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `efromname` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `eto` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `etoname` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL,
  `subject` varchar(250) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `seen` int(1) NOT NULL DEFAULT '0',
  `active` int(1) NOT NULL DEFAULT '1',
  `hide_from` int(1) NOT NULL DEFAULT '0',
  `hide_to` int(1) NOT NULL DEFAULT '0',
  `messageid` bigint(22) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `messages_single`
--

INSERT INTO `messages_single` (`id`, `efrom`, `efromname`, `eto`, `etoname`, `subject`, `time`, `seen`, `active`, `hide_from`, `hide_to`, `messageid`) VALUES
(1, 'info@qflash.pl', 'Qflash.pl', 'hello@qflash.pl', 'Zeno', 'Hello message', '2017-11-14 16:54:03', 0, 1, 0, 0, 1);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
