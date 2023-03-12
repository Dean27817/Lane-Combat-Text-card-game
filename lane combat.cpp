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
        std::cout << "play will begin with each player drawing four cards from a fourteen card deck. each deck will have each color of the rainbow twice.\nthe first player to go will lay down as may of their cards as they want. then the second player will have a chance to counter their cards with one of their own, as well as play on any open lanes.\na counter can only be made with the next color of the rainbow on eyther side of it (such as orange counters red and yellow).\nwhen a card is played by eyther team and left undefended, it will do one damage to its opponent.\n the game will end when one players helth reaches zero\nlets start a game!";
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

void drawLanes(int lanes[2][4])
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
                    if (lanes[0][i] == 0)
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
        std::cout << std::setw(7) << deck.colors[lanes[1][i]] << ", " << std::setw(9) << deck.sigils[lanes[2][i]];
    }
    std::cout << "|\n";
    for (int a = 5; a > 0; a--)
    {
        for (int i = 0; i <= 4; i++)
        {
            std::cout << "|";
            for (int j = 18; j > 0; j--)
            {
                if (lanes[0][i] == 1)
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

void playCards(int lanes[2][4], int player)
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
            std::cout << "which card would you like to play\n(input the number in your hand 1 starts at the top)\n";
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

        std::cout << "you played " << deck.colors[smallCardPlayed] << " on a " << deck.colors[lanes[1][lanePlayed]] << "\n";


        if (avaliableCard1 == lanes[1][lanePlayed] || avaliableCard2 == lanes[1][lanePlayed])
        {
            std::cout << "you can play that card\n";
            lanes[1][lanePlayed] = smallCardPlayed;
            lanes[2][lanePlayed] = person[player].handSigilNum[cardPlayed];
            removeCards(cardPlayed, player);
            lanes[0][lanePlayed] = player;
            if (person[player].handSigilNum[cardPlayed] == 6)
            {
                person[player].revive = true;
                std::cout << "revive was played";
            }
        }
        else
        {
            std::cout << "you can't play that card\n";
            std::cout << "you can only play that card on a " << deck.colors[avaliableCard1] << " or a " << deck.colors[avaliableCard2] << " not " << deck.colors[lanes[1][lanePlayed]] << "\n";

        }
        std::cout << "can you play another card?\n";
        std::cin >> agein;
        if (agein == 'y')
        {
            showHand(player);
            drawLanes(lanes);
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

void playerTurn(int player, int lanes[2][4])
{
    std::cout << "player " << player + 1 << "'s turn\n";
    std::cin.ignore();
    std::cin.get();
    drawCards(player);
    showHand(player);
    drawLanes(lanes);
    playCards(lanes, player);
    for (int i = 0; i <= 3; i++)
    {
        if (lanes[0][i] == 0)
        {
            person[1].playerHelth--;
        }
        if (lanes[0][i] == 1)
        {
            person[0].playerHelth--;
        }
    }
    if (person[0].playerHelth <= 0 && person[0].revive == false)
    {
        person[1].victory = true;
    }
    if (person[1].playerHelth <= 0 && person[0].revive == false)
    {
        person[0].victory = true;
    }
    person[player].revive = false;
    system("cls");

}

int main()
{
    srand(time(0));
    int player = 0;
    int lanes[3][4] =
    {
        {3,3,3,3},
        {rand() % 7, rand() % 7, rand() % 7, rand() % 7},
        {rand() % 8, rand() % 8, rand() % 8, rand() % 8, }
    };
    ///////////////////////////////////////the four is for the four lanes, each lane has two parts. 1, who played the cards. 2, what color they are. 3, what the sigils are
    startingMenu();
    std::cout << "starting game\n";
    std::cin.ignore();
    std::cin.get();
    startGame(player);
    while (person[0].victory == false && person[1].victory == false)
    {
        playerTurn(player, lanes);
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

