# Simple Wave Based Space Shooter

SWBSS is a forked  version of GNASS (the acronym stands for GNASS is not another space shooter) aimed to improve it, clean the code and create a better game out of it. GNASS was a freshmen year university project coded by Savinelli Roberto Nicolás, Juan Ignacio Piccardi, José Daniel Taverso.

A lot of polish either on the handler side and the game side were made to release this version since it had a lot of bugs and little problems. Some of this problems still remain (like: if you run this game in HDPI all the bitmaps look really small) but can be solved in the future.

### Gameplay

YouTube: https://www.youtube.com/watch?v=YEgkpkBWMQY

<a href="https://www.youtube.com/embed/YEgkpkBWMQY" target="_blank">
<img src="http://img.youtube.com/vi/YEgkpkBWMQY/0.jpg" width="240" border="2" /></a>

## Dependecies/Requisites

### Allegro 5.2 or newer is needed

For general installation information visit [allegro download webpage](https://liballeg.org/download.html).

If you're running a ubuntu based distro follow this simple steps:

```
sudo add-apt-repository ppa:allegro/5.2

sudo apt-get update

sudo apt-get install liballegro5-dev liballegro-acodec5-dev liballegro-audio5-dev liballegro-dialog5-dev liballegro-image5-dev liballegro-physfs5-dev liballegro-ttf5-dev liballegro-video5-dev
```

### A custom library libal_handler is needed

libal_handler takes care of the allegro side of the program.

This library has also been open sourced and can be found inside `./lib`

## How to Compile and Run the Game:

To compile the game open a terminal inside this directory and run: 
```
make compile
```
To run the game run:
```
./exe
```
## Feedback

All bugs, feedback, feature requests and pull requests are welcome.

Feel free to [create an issue](https://github.com/rnsavinelli/SWBSS/issues) or to contribute to the project.

## License

GPLv3 License: https://www.gnu.org/licenses/gpl-3.0.txt or see the 
[`LICENSE`](https://github.com/rnsavinelli/SWBSS/blob/master/LICENSE) file.
