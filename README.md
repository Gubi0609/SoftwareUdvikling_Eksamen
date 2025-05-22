# Dungeon Crawler spil til Softwareudvikling F25
### Civ. Ing. RobTek F25 SDU Odense

## Udvikler:
- [August Tranberg](https://github.com/Gubi0609)

## Beskrivelse af system.
En simpel tekst baseret dungeon crawler med mulighed for at gemme og analysere spildata i en SQL-database via sqlite3.
Spillet inddrager inspiration fra både Hobbiten og lidt Legend of Zelda.

## Databasen
Databasen forefindes under
```bash
./SQL/database.db
```
Hvis databasen enten ikke findes eller har fejl, kan man manuelt genskabe den fra bunden ved at kopiere teksten i
```bash
./SQL/database_init.txt
```
og køre den manuelt i sqlite3 ved først at køre:
```bash
sqlite3 ./SQL/database.db
```
Og derefter indsætte teksten fra `database_init.txt`

## Kompilering
Der er inkluderet en `CMakeLists.txt` som sørger for at alt bliver kompileret rigtigt.

#### Hvis dit download ikke inkluderer `./build/`
Husk at lav et build directory, hvis det ikke er inkluderet i dit download:
```bash
mkdir build
cd build
```
Når du har et build directory og er placeret i det, køres:
```bash
cmake ..
make
```
Spillet kan nu køres ved at køre følgende kommando:
```bash
./dungeonGame
```

### God fornøjelse!
