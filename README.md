# The Quest for The Holy Bread - GDD

## Informacje

**Nazwa projektu:** The Quest for The Holy Bread  
**Użyte technologie:** C++ + SFML  

## Opis

### Cel gry

Celem gry będzie przedarcie się przez **X** *(to się zmieni)* poziomów lochów pełnych przeciwników w celu dotarcia do **skrzyni zawierającej chleb, gazety i dżem śliwkowy**, czyli **Dobra Konieczne**.

### Świat

**TBD**

## Informacje techniczne

### Rozgrywka

Rozgrywka turowa, gracz oraz przeciwnicy poruszają się po planszy złożonej z siatki.  
Po rozpoczęciu nowej gry gracz pojawia się w losowym punkcie pierwszego poziomu lochu, kamera wycentrowana na graczu podąża za nim.  
Po każdym ruchu gracza przeliczane są tury przeciwników.  
W losowych miejscach w lochu (ale w określonej minimalnej odległości od gracza) umieszczane są schody (lub dziura(?)) prowadzące do niższego poziomu lochu.

### Cechy

* Permadeath, brak zapisu stanu(?)
* Grafika złożona ze sprite'ów 32px x 32px
* Loch podzielony na poziomy z przejściami między nimi (brak możliwości powrotu(?))
* (Prosty) system ekwipunku, plecak ograniczony maksymalną ilością przedmiotów
* System statystyk (gracza, przeciwników i ekwipunku) i poziomów (gracza)
* Turowy system walki "wręcz", biorący pod uwagę statystyki, z elementami losowości

## Kompilacja

**Linux/Unix**

```
$ git clone --recurse-submodules https://umcs.schneiderp.ovh/norbert.budzynski/roguelike.git
$ cd roguelike
$ ./extern/vcpkg/bootstrap-vcpkg.sh
$ cmake -G Ninja -B build -S . -DCMAKE_TOOLCHAIN_FILE=extern/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE:STRING=Release
$ cmake --build build/
```

## Kamienie Milowe
* ~~**Milestone-1**~~ - Ekran wczytywania zasobów, wczytywanie testowej mapy z pliku, kolizje z polami, interaktywne pola (np. drzwi), kolejka akcji
* ~~**Milestone-2**~~ - "Wałęsające się" NPC, wczytywanie NPC z plików(?), statystyki
* ~~**Milestone-3**~~ - Przedmioty wczytywanie z plików, ekwipunek, plecak, przedmioty na ziemi
* ~~**Milestone-4**~~ - Prosty interfejs
* **Milestone-5** - Losowa generacja świata
* ...
* **Milestone-???** - Shadery żeby chlebek na ekranie wczytywania ładnie migał

## Licencje
Fonty:
- [Alagard by Pix3M](https://www.deviantart.com/pix3m/art/Bitmap-font-Alagard-381110713) - CC BY 3.0  
- [Noto Sans Mono](https://fonts.google.com/noto) - Open Font License

Tekstury: 
- [Dungeon Crawl Stone Soup](http://opengameart.org/content/dungeon-crawl-32x32-tiles-supplemental) - CC0
