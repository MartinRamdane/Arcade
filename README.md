# Arcade  documentation

Arcade is a core game which uses graphic lib and game lib.
So you can create your own graphic or game lib and can use it with arcade project.

## Usage

- rename your cpp file with the good type like : "Display" for graphic lib or "Game" for game lib.

- put your code in src directory and add your files in the root CMake like this:
```CMake
add_library(_libname SHARED src/TYPELibName.cpp)
```

## How to make game library

You should use AGameModule class for inheritance on your own game class.

Your class have a infos map with an Entity object.

Entity description:

### file
A string with the sprite's path.

### text
A string for ncurse lib and represent the entity (like a character or other thing).

### color
Foreground color of entity.

### background_color
Background color of entity.

### spriteColor
The color of the sprite.

### fontSize
Change the fontSize if the Entity is a text.

### x
The x position.

### y
The y position.

### xSprite
The sprite's x position (0=x).

### ySprite
The sprite's y position (0=y).

### type
The entity type (SPRITE, TEXT, SPRITE_TEXT if it should be render as a sprite and a text, BACKGROUND, TEXTURE, NONE)

### toUpdate
If the entity should be updated by the graphic lib.

AGameModule methods to implement :
### getInfos()
Return the infos map.
```C++
std::map<std::string, IGameModule::Entity> &getInfos();
```

### createEntity()
To create a entity and return it.
```C++
 IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, ENTITY_TYPE type, float xSprite, float ySprite, int fontSize);
```

### getGameStatus()
To get the game status.
Game status can be MENU, PAUSED, IN_GAME, FINISHED.

In your class constructor, your should define these :
- areaWidth
- areaHeight
- score
- selectMenu (button menu value)

## How to make a graphic library

To make a graphic library you should implement the IDisplayModule methods.

### init(entities)
To init the graphic library with a entities map (infos) in argument.
```C++
void init(std::map<std::string, IGameModule::Entity> &entites);
```

### stop()
To stop your graphic library.

### update(entities)
To update your render in your graphic library.
```C++
void update(std::map<std::string, IGameModule::Entity> &entities);
```

### draw()
To draw your sprites.
```C++
void draw();
```

### getEvent()
To return a key event, see the doc about [KeyEvent](#key-event).
```C++
std::string getEvent();
```

### getName()
To get the name library.
```C++
const std::string &getName();
```
### KeyEvent
For letters:

Return just the letter with ASCII value if possible.

For special key:
Use just the name of the key in capitalize like :
```
        case KEY_UP:
            return std::string("UP");
        case KEY_DOWN:
            return std::string("DOWN");
        case KEY_LEFT:
            return std::string("LEFT");
        case KEY_RIGHT:
            return std::string("RIGHT");
        case 27:
            return std::string("ESCAPE");
        case 127:
            return std::string("BACKSPACE");
        case 10:
            return std::string("ENTER");
```
You can use a library to get inputs.

# Contributors

### Florian GRIMA
### Martin RAMDANE