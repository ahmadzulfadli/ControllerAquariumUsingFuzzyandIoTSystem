CREATE DATABASE iot_aquarium;

use iot_aquarium;

DROP TABLE IF EXISTS `aquarium`;

CREATE TABLE `aquarium` (
  `id` int NOT NULL AUTO_INCREMENT,
  `data_temp` float NOT NULL,
  `data_ph` float NOT NULL,
  `timestamps` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
SELECT *FROM aquarium;

DESC aquarium;
