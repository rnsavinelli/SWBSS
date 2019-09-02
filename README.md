# Simple Wave Based Space Shooter

SWBSS is a forked  version of GNASS (the acronym stands for GNASS is not another space shooter) aimed to improve it, clean the code and create a better game out of it. GNASS was a freshmen year university project coded by Savinelli Roberto Nicolás, Juan Ignacio Piccardi, José Daniel Taverso.

A lot of polish either on the handler side and the game side were made to release this version since it had a lot of bugs and little problems. Some of this problems still remain (like: if you run this game in HDPI all the bitmaps look really small) but can be solved in the future.

# Dependecies/Requisites

**Allegro 5.2 or newer is needed.**

For general installation information visit [allegro download webpage](https://liballeg.org/download.html).

If you're running a ubuntu based distro follow this simple steps:

```
sudo add-apt-repository ppa:allegro/5.2

sudo apt-get update

sudo apt-get install liballegro5-dev liballegro-acodec5-dev liballegro-audio5-dev liballegro-dialog5-dev liballegro-image5-dev liballegro-physfs5-dev liballegro-ttf5-dev liballegro-video5-dev
```

**Custom library libal_handler is needed**

libal_handler takes care of the allegro side of the program.

This library has been also open sourced and can be found inside ./lib

## How to compile and run the game:

To compile the game open a terminal inside this directory and run: 
```
make compile
```
To run the game run:
```
./exe
```
