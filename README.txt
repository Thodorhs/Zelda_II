HY454 Zelda Game And Engine Developed by:
=======================================
|csd4336 Thodoris Pontzouksidhs		|		
|csd4492 Dimitris Vlaxos			|
|Honarable mention Nikos Iliakis	|
=======================================

You need to run the game in Visual Studio 2022.
The project runs with CMAKE lists.

Steps needed to compile the project:

for including SDL2:
-Step 1: Search enviroment variable in windows search bar
-step 2: Then press enviroment variables
-Step 3: Then press new in User variables
-Step 4: Set the enviroment variable name as CMAKE_PREFIX_PATH
-Step 5: Then press Browse directory and navigate to the folder where SDL is: <YOUR_PATH>\CS454\CS454\ThirdParty\SDL2-devel-2.26.1-VC (we have it inside thirdparty)

for including SDL2_TTF:
-step 11: Then press Browse directory and navigate to the folder where SDL_TTF is: <YOUR_PATH>\CS454\CS454\ThirdParty\SDL2_ttf-2.22.0 (we have it inside thirdparty)
-step 12: added to the enciroment variable CMAKE_PREFIX_PATH the path to SDL_TTF use ";" to seperate with previous paths

for including SDL2_MIX:
-step 11: Then press Browse directory and navigate to the folder where SDL_TTF is: <YOUR_PATH>\CS454\CS454\ThirdParty\SDL2_mixer-2.8.0 (we have it inside thirdparty)
-step 12: added to the enciroment variable CMAKE_PREFIX_PATH the path to SDL_MIX use ";" to seperate with previous paths

After you set the enviroment variables:
-Step 1: Open Visual Studio 2022
-Step 2: select Open a Local folder
-Step 3: Browse to the first CS454 you see and click open (HIGHEST directory named CS454 the one before this README is located don't double click inside)
-Step 4: if Cmake Integration popup press Enable and set source directory
-Step 5: Then inside CS454/CS454 pick CmakeLists.txt and open it
-Step 6: Then Run UnitTest3 which has the final version of the game 
-Step 7: If you get an error dont worry there is one last thing you need to do....

Last step add sdl and sdl2_ttf and sdl2_mixer .dll files:
-Step 8: Go in CS454\CS454\ThirdParty\SDL2-devel-2.26.1-VC\SDL2\lib\x64\ and copy the files SDL2.dll and SDL2_image.dll
-Step 9: Then in CS454/CS454 go into out/build/x64-Debug
-Final 10: Then paste the files inside there

-Step 11: Go in CS454\CS454\ThirdParty\SDL2_ttf-2.22.0\lib\x64 and copy the file SDL2_ttf.dll
-Step 12: Then in CS454/CS454 go into out/build/x64-Debug
-Final 13: Then paste the files inside there

-Step 11: Go in CS454\CS454\ThirdParty\SDL2_ttf-2.22.0\lib\x64 and copy the file SDL2_mixer.dll
-Step 12: Then in CS454/CS454 go into out/build/x64-Debug
-Final 13: Then paste the files inside there


The game should run fine if you have done everything correctly.
select executable UnitTest3.exe it is the most we could implement.

