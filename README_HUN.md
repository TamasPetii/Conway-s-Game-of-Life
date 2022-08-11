# Conway Élet Játéka
![kép](https://user-images.githubusercontent.com/60004480/175936500-d11faac1-7660-4d83-bd7e-2f46d1ebc714.png)
# A játékról
A program c++ programozási nyelv alatt készült az SDL-t felhasználva.
<br><br>
A játék minden fontos metódust tartalmaz amit Conway meghatározott a szabályok között.
<br><br>
Kis érdekességképpen egy dimenziós tömböket használtam kétdimenziós tömbök helyett, így matematikailag kellett visszafejtenem egy két esetben hogy mik az x,y koordináták.

# A játék beállításokról / gombokról.
| Gomb  | Mit csinál? |
| ------------- | ------------- |
| ![kép](https://user-images.githubusercontent.com/60004480/184091476-cd3428d9-096d-4bf9-84aa-c0f3e700c440.png)  | A gomb lenyomásával el tudod indítani a játékot. <br> Ha a játék elindult akkor a gomb azonnal szürkére vált és innentől kezdve elérhetetlen a gomb mindaddig, amíg nem lesz szüneteltetve a játék.  |
| ![kép](https://user-images.githubusercontent.com/60004480/184091854-e7634a14-cd57-43de-aee0-4dd6885e71ac.png)| A gomb lenyomásával szüneteltetni tudod a játékot. <br> Miközben a játék szüneteltetve van a gomb szürkére vált és nem lehet rákattintani amíg el nem indul újra a játék.  |
|![kép](https://user-images.githubusercontent.com/60004480/184092193-9dbca68d-0657-4350-87a2-5cb6f434906b.png)| Ha végeztél a játékkal és ki akarsz lépni, akkor nyomd meg ezt a gombot és azonnal bezárul a játék.|
|![kép](https://user-images.githubusercontent.com/60004480/184092305-a6ae37a3-01b6-45db-8868-773f92d9ab84.png)| Ha ezt a gombot megnyomod, akkor le fognak nyílni a játékbeállítási opciók, ahol testre tudod szabni tetszés szerint a játék kinézetét. |
|![kép](https://user-images.githubusercontent.com/60004480/184092432-37dac152-af02-4a04-9618-25c4640d6554.png)| Itt beállíthatod a háttér színét. <br> Kattints rá a kiválaszott színre és a játék automatikusan frissíti magát és már az új beállítással élvezheted a játékot. |
|![kép](https://user-images.githubusercontent.com/60004480/184092661-281db94b-5b09-4cad-9b39-c426e2daf797.png)| Az élő cellák színei is beállíthatóak itt. <br> Kattints rá a kiválaszott színre és a játék automatikusan frissíti magát és már az új beállítással élvezheted a játékot.|
|![kép](https://user-images.githubusercontent.com/60004480/184092818-d2389c85-f07c-4f7b-8869-843031424a49.png)| Továbbá a játékpálya mérete is beállítható. <br> A jelenleg kiválasztott pályaméretet piros x-el jelöltem. |

# Letöltés
1. SDL2 csomag letöltése: https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip
2. SDL2_image csomag letöltése: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip

# Visual Studio Code / Terminálos fordítás beállítása
0. `Az SDL csomagok már telepítve vannak. A .cpp és a .png fileok a fő mappában vannak.` <br>
1. `Hozz létre a fő mappában egy "src" nevű mappát` <br>
2. `Hozz létre az "src" mappán belül egy "include" nevű mappát, és rakd ebbe az include mappába az SDL és SDL_image csomagok header filejait` <br>
3. `Hozz létre az "src" mappán belül egy "lib" nevű mappát, és rakd bele a következő könyvtárakat: SDL2.lib, SDLmain.lib, SDL_image.lib` <br>
4. `A fő mappába rakd bele a következő dll-eket: SDL2.dll, SDL_image.dll, libpng16-16.dll` <br>
5. `Nyiss meg egy terminált a fő mappában és írd be a következő kódot:`<br> 
`g++ -Isrc/include -Lsrc/lib *.cpp -lSDL2main -lSDL2 -lSDL2_image -Wall -Wextra`
6. `Futtasd az a.exe állományt!`

# Visual Studio 2022 Beállítás 
1. Hozz létre a C:\ meghajtódon egy SDL nevű mappát.
2. Az így létrehozott SDL mappában hozzd létre az alábbi nevű mappákat: bin, include, lib.
3. A letöltött SDL csomagokat csomagold ki és az include mappájukból másolj át mindent a c meghajtón található SDL nevű mappádnak az include mappájába. Tedd meg ugyan ezt a letöltött csomagok lib és bin filejaival. Fontos!!! x64-es mappából másolj át mindent. Lehet hogy a .dll és .lib fájlok ugyanabban a mappában vannak, ekkor a .lib a lib mappába és a .dll fileok a bin mappába fognak kerülni.
4. Nyiss meg egy terminált és írd be ezt a kommandot: subst T: C:\SDL
5. Töltsd le a teljes Visaul Studio 2022 Version mappát innen a githubomról és kattints rá az sln filera. Majd nyisd meg a project beállításokat.
6. A beállításoknál a felső sornak így kell kinéznie.

<div align="center">
  
![kép](https://user-images.githubusercontent.com/60004480/183756201-ad72efa9-24f5-4ce0-93ca-4c6f3a25e4a1.png)

</div>
  
7. VC++ Directories >> Include directories >> T:\include;$(IncludePath)

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183755848-45156c5c-5283-4a82-a50d-2c31995a769b.png)

</div>

8. VC++ Directories >> Include directories >> T:\lib;$(LibraryPath)

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756057-69c29e07-f5ab-4154-87ff-cb18b109fd9a.png)

</div>

9. Debugging >> PATH=T:\bin;%PATH%

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756467-cce70722-d354-4400-aa8f-e5a40e635e6b.png)

</div>

10. Linker >> Input >> Additional Dependencies >> SDL2.lib;SDL2main.lib;SDL2_image.lib;

<div align="center">
  
![kép](https://user-images.githubusercontent.com/60004480/183758297-77e37605-df38-4407-a791-5add1374bb98.png)

</div>

11. Mentsd el a változásokat, majd zárd be és a futtatásnál állíts mindent úgy ahogy a képen van.

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756944-4628a035-eaed-4779-bc7a-f28d29cfb899.png)

</div>
