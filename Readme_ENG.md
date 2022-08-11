# Conway's Game of Life
![kép](https://user-images.githubusercontent.com/60004480/175936500-d11faac1-7660-4d83-bd7e-2f46d1ebc714.png)
# About the Game
This game was created in c++ made whit Simple DirectMedia Layer (SDL). 
<br><br>
The program contains all the necessary algorithms defined by the Conway's method.
<br><br>
As a feature the game map is represented as a one dimensional vector instead of two dimensional vectors. 
# About Game Options / Buttons
| Button  | What it does |
| ------------- | ------------- |
| ![kép](https://user-images.githubusercontent.com/60004480/184091476-cd3428d9-096d-4bf9-84aa-c0f3e700c440.png)  | You can start the game by pressing this button. <br> If the game has started the button turns to grey and will be unavailable.  |
| ![kép](https://user-images.githubusercontent.com/60004480/184091854-e7634a14-cd57-43de-aee0-4dd6885e71ac.png)| You can reset the game map by pressing this button. <br> If the game is paused this button turns to grey and will not be able to press it again.  |
|![kép](https://user-images.githubusercontent.com/60004480/184092193-9dbca68d-0657-4350-87a2-5cb6f434906b.png)| Anytime you want to leave the game press this button and the program will close.|
|![kép](https://user-images.githubusercontent.com/60004480/184092305-a6ae37a3-01b6-45db-8868-773f92d9ab84.png)|By pressing this button the option bar will be available and you can customize the game. |
|![kép](https://user-images.githubusercontent.com/60004480/184092432-37dac152-af02-4a04-9618-25c4640d6554.png)|You can set the background colour of the map. <br> You just need to click on the chosen colour and the game immediately changes. |
|![kép](https://user-images.githubusercontent.com/60004480/184092661-281db94b-5b09-4cad-9b39-c426e2daf797.png)|You can set the color of the living cells. <br> You just need to click on the chosen colour and the game immediately changes.|
|![kép](https://user-images.githubusercontent.com/60004480/184092818-d2389c85-f07c-4f7b-8869-843031424a49.png)|You can set the size of the game map. <br> The current selected size is indicated by a red x. |

# Installation
1. Download SDL2 pack: https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip
2. Download SDL2_image pack: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip

# Setup Visual Studio Code / Terminal Compile
0. `The .cpp, .h, .png files are already int the main directory | SDL pack is already downloaded` <br>
1. `Create a "src" directory in the main directory` <br>
2. `Create a "include" directory in the src directory, and put the SDL header files there` <br>
3. `Create a "lib" directory in the src directory, and put the following librarys there: SDL2.lib, SDLmain.lib, SDL_image.lib` <br>
4. `Put the following dlls int the main direcotry: SDL2.dll, SDL_image.dll, libpng16-16.dll` <br>
5. `Open a terminal in the main library and copy this command and run a.exe:`<br> 
`g++ -Isrc/include -Lsrc/lib *.cpp -lSDL2main -lSDL2 -lSDL2_image -Wall -Wextra`

# Setup Visual Studio 2022 
1. Make a folder in local disk C:\ named as SDL.
2. In C:\SDL folder make folders named as bin, include and lib.
3. Extract the downloaded SDL2 folders and copy their x64 include content to the C:\SDL\include folder. Do the same thing with lib and bin folders (x64!!!). (If lib and bin files are in the same directory of the extracted SDL2 packs then sort them to the proper folds. )
4. Open a terminal and write this command: subst T: C:\SDL
5. Open Visual Studio 2022, make a project and open project settings.
6. Set the top bar like this.

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

11. Go back set this options like this and you are ready to go.

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756944-4628a035-eaed-4779-bc7a-f28d29cfb899.png)

</div>
