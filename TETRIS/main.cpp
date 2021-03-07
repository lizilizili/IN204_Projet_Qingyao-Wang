#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "player.h"

//Speed of delay
const float SPEED_NORMAL = 0.5;
const float SPEED_QUICK = 0.05;
float delay = SPEED_NORMAL;

using namespace sf;

void keyEvent(RenderWindow * window, player *p)
    {
        Event e;
        while (window->pollEvent(e)) //pull an event from queue
        {
            if (e.type == Event::Closed)
                window->close();

            if (e.type == Event::KeyPressed)
            {
                switch (e.key.code)
                {
                case Keyboard::Up:
                    p->rotation();
                    break;
                case Keyboard::Left:
                    p->left();
                    break;
                case Keyboard::Right:
                    p->right();
                    break;
                default:
                    break;
                }
            }

            //When we press DOWN, we accelerate the speed.
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                delay = SPEED_QUICK;
            }

        }
    }

void drawBlocks(Sprite * spriteBlock, RenderWindow * window, player * p)
    {
    /*There 3 types of blocks:
            blocks fixed on the board
            present block
            next block
    */
        //Draw blocks which fixed on the board
        for (int i = 0; i < ROW_COUNT; i++)
        {
            for (int j = 0; j < COL_COUNT; j++)
            {
                if (p->getState(i,j)!= VIDE)
                {
                    spriteBlock->setTextureRect(IntRect(p->getState(i,j) * 20,0, 20, 20));
                    spriteBlock->setPosition(j * 20, i * 20);
                    spriteBlock->move(28, 33);
                    window->draw(*spriteBlock);
                }
            }
        }

        //Draw present block
        for (int i = 0; i < 4; i++)
        {
            spriteBlock->setTextureRect(IntRect(p->getBlockCode() * 20, 0, 20, 20));
            spriteBlock->setPosition(p->getBlockPosition_y(i) * 20,p->getBlockPosition_x(i) * 20);
            spriteBlock->move(28, 31);
            window->draw(*spriteBlock);
        }

        //Draw next block
        for (int i = 0; i < 4; i++)
        {
            spriteBlock->setTextureRect(IntRect(p->getNextBlockCode() * 20, 0, 20, 20));
            spriteBlock->setPosition(p->getNextBlockPosition_y(i) * 20,p->getNextBlockPosition_x(i) * 20);
            spriteBlock->move(300,60);
            window->draw(*spriteBlock);
        }
    }

void drawBackground(Sprite * spriteBG, RenderWindow * window,RectangleShape * rect){
     window->draw(*spriteBG);
     window->draw(*rect);
}

int main(int argc, char** argv)
{
      srand(time(0));

        //Create Window
        RenderWindow window(VideoMode(400, 480),"TETRIS");

        //Load Background
        Texture t1;
        t1.loadFromFile("images/background.jpg");
        Sprite spriteBG(t1);

        RectangleShape rect(Vector2f(210,410));
        rect.setPosition(Vector2f(23,26));
        //Load Blocks.png
        Texture t2;
        t2.loadFromFile("images/blocks.png");
        Sprite spriteBlock(t2);

        //Load Font
        Font font;
        if (!font.loadFromFile("font/comic.ttf"))
        {
            std::cout << "Can not load the font" << std::endl;
        }

        //Create texts
        Text textScores;
        textScores.setFont(font);
        textScores.setString("Scores: 0");
        textScores.setCharacterSize(20);
        textScores.setFillColor(sf::Color::White);
        textScores.setPosition(250,300);

        Text textLevel;
        textLevel.setFont(font);
        textLevel.setString("Level: 0");
        textLevel.setCharacterSize(20);
        textLevel.setFillColor(sf::Color::White);
        textLevel.setPosition(250,250);

        Text textGameOver;
        textGameOver.setFont(font);
        textGameOver.setString("GAME OVER!");
        textGameOver.setCharacterSize(40);
        textGameOver.setFillColor(sf::Color::White);
        textGameOver.setPosition(80,200);

        //New Player
        player * player1= new player();

        //Clock and timer
        Clock clock;
        float timer=0;

        // Run the program as long as the window is open
        while (window.isOpen())
        {
            //Flag turn false when block can't get down.
            bool flag=true;
            float time;
            while (!player1->endOfGame) {
                time= clock.getElapsedTime().asSeconds();
                timer += time;
                clock.restart();

                // Check all the window's events that were triggered since the last iteration of the loop
                keyEvent(&window,player1);

                //Drop of block
                if (timer > delay)
                {
                    flag = player1 -> down();
                    timer = 0;
                }

                //If the block touch the bottom or on other blocks
                if (flag == false){
                    flag = true;
                    //get the next block
                    player1->nextBlock();
                    //eliminate rows and update score/level
                    player1->removeRow();


                }
                //update delay
                delay = SPEED_NORMAL-(0.05*player1->level);
                //update texts
                String str = "Scores: ";
                str.insert(str.getSize(),std::to_string(player1->score));
                String str2 = "Level: ";
                str2.insert(str2.getSize(),std::to_string(player1->level));
                textLevel.setString(str2);
                textScores.setString(str);

                //draw background
                drawBackground(&spriteBG,&window,&rect);
                //draw blocks
                drawBlocks(&spriteBlock, &window,player1);
                //draw texts
                window.draw(textScores);
                window.draw(textLevel);

                //display the window
                window.display();
            }//end of game

            // When EndOfGame
            window.draw(spriteBG);
            window.draw(textGameOver);
            //Print scores
            textScores.setCharacterSize(30);
            textScores.setPosition(80,250);
            window.draw(textScores);
            //display the window
            window.display();
            system("pause");
            window.close();
        }


    return EXIT_SUCCESS;
}
