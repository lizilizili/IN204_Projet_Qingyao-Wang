#IN204 Qingyao-Wang

### Author: Qingyao Wang
## Exécution
C'est un projet de CodeBlocks.
Ouvriez directement le fichier ```./TETRIS/in204_p.cbp``` dans CodeBlocks.
Un makefile est aussi fourni par cbp2make

## Classes
### Classe Brick
    brick.h
Cette classe représente les pièces.

-  int bricks[7][4][4][2] contient des variation des carres dans les pièces
- int type;
- int direction;

### Classe Map
    map.hpp
Cette classe représente le plateau.

- int status[ROW_COUNT][COL_COUNT]; (VIDE=-1 COULEUR=0-6)
- brick brickPresent;
- brick brickNext;
- int brickCenter[2]={0,0};
- méthodes pour déplacer la pièce et éliminer les lignes

### Classe Player
    player.h
- map m;
- bool endOfGame=false;
- int level;
- int score;

