// lane combat
// this will be a game similar to a card game where players will fight to counter eachother while playing to try and take over the four lanes
// play will begin with each player drawing four cards from a fourteen card deck. each deck will have each color of the rainbow twice.
// the first player to go will ley down as may of their cards as they want. then the second player will have a chance to counter their cards with one of their own, as well as play on any open lanes.
// a counter can only be made with the next color of the rainbow (orange counters red, green counters yellow, etc).
// the game will end when one player makes four captures.
//
//currently working on makeing the lanes display who playd the cards and adding the damage system to the game
//problems wont show sides, wont change cards for player 1

#include <iostream>
#include <iomanip>
void startingMenu()
{
    int startingChoice;
    std::cout << "would you like to 1: start a game or 2: see the rules\n";
    std::cin >> startingChoice;
    if (startingChoice == 2)
    {
        std::cout << "play will begin with each player drawing four cards from a fourteen card deck. each deck will have each color of the rainbow twice.\nthe first player to go will lay down as may of their cards as they want. then the second player will have a chance to counter their cards with one of their own, as well as play on any open lanes.\na counter can only be made with the next color of the rainbow on eyther side of it (such as orange counters red and yellow).\nwhen a card is played by eyther team and left undefended, it will do one damage to its opponent.\n the game will end when one players helth reaches zero\n each card will also have a sigil that can give it a special effect \nthe sigils are: \n1. rail road, chamge any card on the field to your side \n2. jail, skip your opponents next turn by putting them in jail \n3. defend, stops you from dying your next turn\n4. turtle, has to be counterd twice to be overtaken \n5. wolf, does two damage per turn \n6. change, randomizes the color of any card on the field \n7. revive, gives back two points of life \nlets start a game!";
        std::cin.ignore();
        std::cin.get();
    }
}

void showHand(int player);

class cards
{
public:
    std::string sigils[8] = { "rail road", "jail", "defend", "turtle", "wolf", "change", "revive", "none" };
    std::string colors[14] = { "red", "orange", "yelow", "green", "blue", "indigo", "purple", "red", "orange", "yelow", "green", "blue", "indigo", "purple" };
};

class player
{
public:
    bool drawnCards[14] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    int handNum[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
    int handSigilNum[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int numOfCards = 0;
    bool victory = false;
    int playerHelth = 10;
    bool revive = false;
    bool jail = false;
};

class field {
public:
    int played = 3;
    int laneColor = rand() % 7;
    int laneSigil = rand() % 8;
    bool turtle = false;
    int wolf = false;
};

field lane[4];
cards deck;
player person[2];

void removeCards(int cardPlayed, int player)
{
    for (int i = cardPlayed; i < 14; i++)
    {
        person[player].handNum[i] = person[player].handNum[i + 1];
        person[player].handSigilNum[i] = person[player].handSigilNum[i + 1];
    }
    person[player].numOfCards--;
}

void drawLanes()
{
    std::cout << "player 1 health: " << person[0].playerHelth << "\n";
    for (int a = 5; a > 0; a--)
    {
        for (int i = 0; i <= 4; i++)
        {
            std::cout << "|";
            for (int j = 18; j > 0; j--)
            {
                if (i < 4)
                {
                    if (lane[i].played == 0)
                    {
                        std::cout << "-";
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }
            }
        }
        std::cout << "\n";
    }
    for (int i = 0; i <= 3; i++)
    {
        std::cout << "|";
        std::cout << std::setw(7) << deck.colors[lane[i].laneColor] << ", " << std::setw(9) << deck.sigils[lane[i].laneSigil];
    }
    std::cout << "|\n";
    for (int a = 5; a > 0; a--)
    {
        for (int i = 0; i <= 4; i++)
        {
            std::cout << "|";
            for (int j = 18; j > 0; j--)
            {
                if (lane[i].played == 1)
                {
                    std::cout << "-";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "player 2 health: " << person[1].playerHelth << "\n";
}

void playCards(int player)
{
    int cardPlayed = 0;
    int lanePlayed = 0;
    int avaliableCard1 = 0;
    int avaliableCard2 = 0;
    int smallCardPlayed = 0;
    char agein = 'y';
    std::cout << "can you play a card?\n(y/n)\n";
    std::cin >> agein;
    while (agein == 'y')
    {
        while (1)
        {
            std::cout << "which card would you like to play\n(input the number in your hand 1 starts at the top. press 0 for sigil dictonary)\n";
            std::cin >> cardPlayed;
            cardPlayed--;
            if (cardPlayed < person[player].numOfCards)
            {
                break;
            }
            else
            {
                std::cout << "invalid card number\n";
            }
        }
        if (cardPlayed != -1)
        {
            while (1)
            {
                std::cout << "wich lane would you like to play it in\n";
                std::cin >> lanePlayed;
                lanePlayed--;
                if (lanePlayed <= 3 && lanePlayed >= 0)
                {
                    break;
                }
                else
                {
                    std::cout << "invalid lane number\n";
                }
            }
            if (person[player].handNum[cardPlayed] >= 7)
            {
                smallCardPlayed = person[player].handNum[cardPlayed] - 7;
            }
            else
            {
                smallCardPlayed = person[player].handNum[cardPlayed];
            }


            avaliableCard1 = smallCardPlayed + 1;

            if (avaliableCard1 >= 7)
            {
                avaliableCard1 = 0;
            }
            avaliableCard2 = smallCardPlayed - 1;

            if (avaliableCard2 < 0)
            {
                avaliableCard2 = 6;
            }

            std::cout << "you played " << deck.colors[smallCardPlayed] << " (sigil, " << deck.sigils[person[player].handSigilNum[cardPlayed]] << "), on a " << deck.colors[lane[lanePlayed].laneColor] << " (sigil, " << deck.sigils[lane[lanePlayed].laneSigil] << ")\n";


            if (avaliableCard1 == lane[lanePlayed].laneColor || avaliableCard2 == lane[lanePlayed].laneColor)
            {
                std::cout << "you can play that card\n";
                if (lane[lanePlayed].turtle == false)
                {
                    lane[lanePlayed].laneColor = smallCardPlayed;
                    lane[lanePlayed].laneSigil = person[player].handSigilNum[cardPlayed];
                    lane[lanePlayed].played = player;
                }
                else
                {
                    std::cout << "the turle is vulnerable";
                    lane[lanePlayed].turtle = false;
                }
                switch (person[player].handSigilNum[cardPlayed])
                {
                case 0:
                    int laneControll;
                    std::cout << "which lane would you like to take controll of\n";
                    std::cin >> laneControll;
                    laneControll--;
                    lane[laneControll].played = player;
                    break;
                case 1:
                    if (player == 1)
                    {
                        person[0].jail = true;
                    }
                    else
                    {
                        person[1].jail = true;
                    }
                    std::cout << "you put the other player in jail for one turn";
                    break;
                case 2:
                    person[player].revive = true;
                    std::cout << "you will not die this turn";
                    break;
                case 3:
                    lane[lanePlayed].turtle = true;
                    break;
                case 4:
                    lane[lanePlayed].wolf = true;
                    break;
                case 5:
                    int laneChange;
                    std::cout << "what card would you like to change\n";
                    std::cin >> laneChange;
                    laneChange--;
                    lane[laneChange].laneColor = rand() % 7;
                    std::cout << "it changed to a " << deck.colors[lane[laneChange].laneColor] << "\n";
                    break;
                case 6:
                    person[player].playerHelth += 2;
                    std::cout << "your health increased by two";
                    break;
                }
                removeCards(cardPlayed, player);
            }
            else
            {
                std::cout << "you can't play that card\n";
                std::cout << "you can only play that card on a " << deck.colors[avaliableCard1] << " or a " << deck.colors[avaliableCard2] << " not " << deck.colors[lane[lanePlayed].laneColor] << "\n";

            }
            std::cout << "would you like to play another card?\n";
            std::cin >> agein;
        }
        else
        {
        std::cout << "sigil dictonary\n1. rail road, chamge any card on the field to your side \n2. jail, skip your opponents next turn by putting them in jail \n3. defend, stops you from dying your next turn\n4. turtle, has to be counterd twice to be overtaken \n5. wolf, does two damage per turn \n6. change, randomizes the color of any card on the field \n7. revive, gives back two points of life \n";
        }
        if (agein == 'y')
        {
            showHand(player);
            drawLanes();
        }
    }
}

void drawCards(int player)
{
    bool test = false;
    int cardTest;
    while (test == false)
    {
        cardTest = rand() % 14;
        if (person[player].drawnCards[cardTest] == false)
        {
            person[player].drawnCards[cardTest] = true;
            person[player].handNum[person[player].numOfCards] = cardTest;
            if (rand() % 4 != 1)
            {
                person[player].handSigilNum[person[player].numOfCards] = rand() % 7;
            }
            else
            {
                person[player].handSigilNum[person[player].numOfCards] = 7;
            }
            test = true;
            person[player].numOfCards++;
        }
    }
}

void showHand(int player)
{
    std::cout << "your hand has\n";
    for (int i = 0; i <= person[player].numOfCards - 1; i++)
    {
        std::cout << i + 1 << ". color: " << deck.colors[person[player].handNum[i]];
        std::cout << ", sigil: " << deck.sigils[person[player].handSigilNum[i]] << "\n";
    }
}

void startGame(int player)
{
    system("cls");
    std::cout << "only for player 1";
    std::cin.get();
    for (int i = 4; i > 0; i--)
    {
        drawCards(0);
    }
    showHand(0);
    std::cin.get();
    system("cls");
    std::cout << "only for player 2";
    std::cin.get();
    for (int i = 4; i > 0; i--)
    {
        drawCards(1);
    }
    showHand(1);
    std::cin.get();
    system("cls");

}

void playerTurn(int player)
{
    std::cout << "player " << player + 1 << "'s turn\n";
    std::cin.ignore();
    std::cin.get();
    drawCards(player);
    if (person[player].jail == true)
    {
        std::cout << "sorry, you are in jail";
        person[player].jail = false;
        std::cin.ignore();
        std::cin.get();
    }
    else
    {
        showHand(player);
        drawLanes();
        playCards(player);
    }
    
    for (int i = 0; i <= 3; i++)
    {
        if (lane[i].played == 0)
        {
            if (lane[i].laneSigil == 4)
            {
                person[1].playerHelth -= 2;
            }
            else
            {
                person[1].playerHelth--;
            }
        }
        if (lane[i].played == 1)
        {
            if (lane[i].laneSigil == 4)
            {
                person[0].playerHelth -= 2;
            }
            else
            {
                person[0].playerHelth--;
            }
        }
    }
    if (person[0].playerHelth <= 0)
    {
        if (person[0].revive == false)
        {
            person[1].victory = true;
        }
        else
        {
            person[0].playerHelth = 2;
        }
    }
    if (person[1].playerHelth <= 0)
    {
        if (person[1].revive == false)
        {
            person[0].victory = true;
        }
        else
        {
            person[1].playerHelth = 2;
        }
    }
    if (player == 0)
    {
        person[1].revive = false;
    }
    else if (player == 1)
    {
        person[0].revive = false;
    }
    person[player].revive = false;
    system("cls");

}

int main()
{
    srand(time(0));
    int player = 0;
    
    startingMenu();
    std::cout << "starting game\n";
    std::cin.ignore();
    std::cin.get();
    startGame(player);
    while (person[0].victory == false && person[1].victory == false)
    {
        playerTurn(player);
        player += 1;
        if (player == 2)
        {
            player = 0;
        }
    }
    if (person[0].victory == true)
    {
        std::cout << "player one wins!!!!!!";
    }
    else if (person[1].victory == true)
    {
        std::cout << "player two wins!!!!!!!!";
    }

}

