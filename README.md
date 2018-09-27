# Air Quality TTN.cat

![TTN.cat](./images/ttncat.logo.small.png)

Node de monitorització de qualitat de l'aire amb TTN.

[![license](https://img.shields.io/github/license/ttncat/airquality.svg)](LICENSE)
[![travis](https://travis-ci.org/ttncat/airquality.svg?branch=master)](https://travis-ci.org/ttncat/airquality)
[![twitter](https://img.shields.io/twitter/follow/ttncat.svg?style=social)](https://twitter.com/intent/follow?screen_name=ttncat)

Aquest repositori conté exemples de monitorització de la qualitat de l'aire
fent servir els següents sensors:

* MICS-4514 - CO i NO2
* BME280 - Temperatura, humitat i pressió ambiental

## Hardware

Cada carpeta conté informació sobre el hardware necessari per cada exemple,
així com el firmware específic per cada dispositiu.

## Configuració del *backend* de TTN

#### Configuració bàsica

Crea un nou aplicatiu i un dispositiu en aquest aplicatiu. Selecciona ABP o OTTA i anota les claus generades. Les hauràs d'incloure a l'arxiu `credentials.h` del codi més endavant.

## Llicència

Copyright (C) 2018 by Xose Pérez (@xoseperez)
for The Things Network Catalunya (@ttncat)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
