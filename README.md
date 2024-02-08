# Zelda_II

***This repo includes both a 2D engine and the game Zelda II - The Adventure of Link (UnitTest3).***

*Developed with C++.*

*HY454 - Computer Science Department University Of Crete.*

| csd4336 Thodoris Pontzouksidis		|		

| csd4492 Dimitris Vlachos			|

| Honarable mention Nikos Iliakis	|

You need to run the game in Visual Studio 2022 with CMAKE lists.

## Run

**For including SDL2:**

- Step 1: Search enviroment variable in windows search bar
- step 2: Then press enviroment variables
- Step 3: Then press new in User variables
- Step 4: Set the enviroment variable name as CMAKE\_PREFIX\_PATH
- Step 5: Then press Browse directory and navigate to the folder where SDL is: <YOUR\_PATH>\CS454\CS454\ThirdParty\SDL2-devel-2.26.1-VC (we have it inside thirdparty)

**For including SDL2\_TTF:**

- step 1: Then press Browse directory and navigate to the folder where SDL\_TTF is: <YOUR\_PATH>\CS454\CS454\ThirdParty\SDL2\_ttf-2.22.0 (we have it inside thirdparty)
- step 2: added to the enciroment variable CMAKE\_PREFIX\_PATH the path to SDL\_TTF use ";" to seperate with previous paths

**For including SDL2\_MIX:**

- step 1: Then press Browse directory and navigate to the folder where SDL\_TTF is: <YOUR\_PATH>\CS454\CS454\ThirdParty\SDL2\_mixer-2.8.0 (we have it inside thirdparty)
- step 2: added to the enciroment variable CMAKE\_PREFIX\_PATH the path to SDL\_MIX use ";" to seperate with previous paths

**After you set the enviroment variables:**

- Step 1: Open Visual Studio 2022
- Step 2: select Open a Local folder
- Step 3: Browse to the first CS454 you see and click open (HIGHEST directory named CS454 the one before this README is located don't double click inside)
- Step 4: if Cmake Integration popup press Enable and set source directory
- Step 5: Then inside CS454/CS454 pick CmakeLists.txt and open it
- Step 6: Then Run UnitTest3 which has the final version of the game
- Step 7: If you get an error dont worry there is one last thing you need to do....

**Last step add sdl and sdl2\_ttf and sdl2\_mixer .dll files:**

- Step 1: Go in CS454\CS454\ThirdParty\SDL2-devel-2.26.1-VC\SDL2\lib\x64\ and copy the files SDL2.dll and SDL2\_image.dll
- Step 2: Then in CS454/CS454 go into out/build/x64-Debug
- Step 3: Then paste the files inside there

- Step 4: Go in CS454\CS454\ThirdParty\SDL2\_ttf-2.22.0\lib\x64 and copy the file SDL2\_ttf.dll
- Step 5: Then in CS454/CS454 go into out/build/x64-Debug
- Step 6 Then paste the files inside there

- Step 7: Go in CS454\CS454\ThirdParty\SDL2\_ttf-2.22.0\lib\x64 and copy the file SDL2\_mixer.dll
- Step 8: Then in CS454/CS454 go into out/build/x64-Debug
- Step 9: Then paste the files inside there


*The game should run fine if you have done everything correctly.*

