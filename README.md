# Dobra Konieczne - GDD

## Informacje

**Nazwa projektu:** Dobra Konieczne: The Dungeon-crawling Videogame  
**Użyte technologie:** C++ + SFML  

## Opis

### Cel gry

Celem gry będzie przedarcie się przez **X** *(to się zmieni)* poziomów lochów w celu dotarcia do **skrzyni zawierającej chleb, gazety i dżem śliwkowy**, czyli tytułowe **Dobra Konieczne**.

### Świat

**TBD**

## Informacje techniczne

### Rozgrywka

Rozgrywka turowa, gracz oraz przeciwnicy poruszają się po planszy złożonej z siatki.

## Kompilacja

**Linux/Unix**

```
$ git clone --recurse-submodules https://umcs.schneiderp.ovh/norbert.budzynski/roguelike.git
$ cd roguelike
$ ./extern/vcpkg/bootstrap-vcpkg.sh
$ cmake -G Ninja -B build -S . -DCMAKE_TOOLCHAIN_FILE=extern/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE:STRING=Release
$ cmake --build build/
```

## Licencje
Użyty font: [Alagard by Pix3M](https://www.deviantart.com/pix3m/art/Bitmap-font-Alagard-381110713) - CC BY 3.0
