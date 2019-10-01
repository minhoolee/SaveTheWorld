# SaveTheWorld
By Mark Lee (Fall 2019)

## Project Description
This is a game that I made for my college's writing course WCWP 10A. The topic
of the class was "climate change doubt," so my goal with this project was to
inform the user of climate change effects (hurricanes and forest fires) and
preventive measures (composting, dieting, and unplugging electronics).

The project was just for fun and I got to play around with inheritance as I
revisted and cleaned up old code that I used for my 
[Galaga2.0 project](https://github.com/minhoolee/Galaga2.0) which turns out to
have spaghetti code. I didn't get to refactor everything but it should be
cleaner.

## Demos
### Full Gameplay (GIF, wait a few seconds)
![Full Gameplay](https://user-images.githubusercontent.com/10465228/65932224-95a01380-e3c1-11e9-8a4b-478ee702c8aa.gif)

## Steps for Reproducing

The game is written in C++ and uses SFML for graphics and bazel for building. 
If you wish to run the game on your computer, follow the following steps:

#### Step 1
Run `git clone https://github.com/minhoolee/SaveTheWorld.git`

#### Step 2
[Install bazel](https://bazel.build/versions/master/docs/install.html)

#### Step 3
[Install SFML 2.4+](https://www.sfml-dev.org/tutorials/2.4/start-linux.php) 

#### Step 4
Run `bazel run //:save-the-world-main` in the SaveTheWorld directory
