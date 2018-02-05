#!/bin/bash

############################################################################
#
#  Internal file to automatic upload files from my laptop
#  and send it to github.
#  You don't need it for this project
#
############################################################################

rm -rf libraries
rm -rf miniAsteroid

mkdir libraries

cd libraries/
cp -r /Users/marek/Documents/Arduino/libraries/Adafruit_Circuit_Playground .
cp -r /Users/marek/Documents/Arduino/libraries/Adafruit_GFX_Library .
cp -r /Users/marek/Documents/Arduino/libraries/Adafruit_ST7735_Library .
cp -r /Users/marek/Documents/Arduino/libraries/Bullet .
cp -r /Users/marek/Documents/Arduino/libraries/Opponent .
cp -r /Users/marek/Documents/Arduino/libraries/SD .

cd ../
cp -r /Users/marek/Documents/Arduino/libraries/Gra1 ./miniAsteroid


mv -r Gra1 miniAsteroid
mv miniAsteroid/Gra1.ino miniasteroid/miniAsteroid.ino

git add . --force
git add --all
git commit
git push -u origin master

echo "OK"


# git init
# git add README.md
# git commit -m "first commit"
# git remote add origin https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
# git push -u origin master
#
# git remote add origin https://github.com/marekurbanski/ArduinoNano-mini-asteroid.git
# git push -u origin master

