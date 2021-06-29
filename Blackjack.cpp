/**
 * @file Blackjack.cpp
 * @author Braeden Kilburn
 * @brief 
 * @version 0.2
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <numeric>

using namespace std;

/**
 * @brief Displays the players current balance
 * 
 * @param playerBalance 
 */
void displayPlayerBalance(int &playerBalance)
{
    cout << "Current Balance: $" << playerBalance << endl;
}

/**
* @brief Displays the individual card values of the player's hand
*
* @param playersCards
*/
void displayIndividualCardsOfPlayer(vector<int> &playersCards)
{
    cout << "\nYour current hand consists of the following card values: " << endl;
    for (vector<int>::iterator i = playersCards.begin(); i != playersCards.end(); ++i)
        cout << "[" << *i << "] ";
    cout << endl;
}

/**
* @brief Displays the individual card values of the dealer's hand
*
* @param dealersCards
*/
void displayIndividualCardsOfDealer(vector<int> &dealersCards)
{
    cout << "\nThe dealer's current hand consists of the following card values: " << endl;
    for (vector<int>::iterator i = dealersCards.begin(); i != dealersCards.end(); ++i)
        cout << "[" << *i << "] ";
    cout << endl;
}

/**
* @brief Display the total value of the player's hand
*
* @param playerHandTotal
*/
void displayNewPlayerHandTotal(int &playerHandTotal)
{
    cout << "\nNew Hand Value: " << playerHandTotal << endl;
}

/**
 * @brief Set the player's current bet amount
 *  
 * @param playerBalance 
 * @return currentBet
 */
int setBetAmount(int &playerBalance)
{
    int currentBet = 0;

    while (true)
    {
        cout << "Bet amount: $";
        cin >> currentBet;
        cout << endl;

        // Player enters anything but an integer
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "You have entered wrong input, please enter a number!" << endl;
        }
        // Player doesn't have enough money to bet
        else if (currentBet > playerBalance)
        {
            cout << "You don't have sufficient funds!" << endl;
            displayPlayerBalance(playerBalance);
            cout << endl;
        }
        // Player bets a negative balance or nothing
        else if (currentBet <= 0)
        {
            if (currentBet == 0)
                cout << "This game isn't free, minimum bet is $1" << endl;
            else
                cout << "Invalid amount, minimum bet is $1" << endl;
        }
        // PLayer's bet is allowed
        else
            return currentBet;
    }
}

/**
 * @brief Prompt the player for the move option
 *   
 * @return Player's Desired Move
 */
int requestPlayerMove()
{
    int playerMove = 0;

    while (true)
    {
        cout << "\nWhat would you like to do? (Enter a number for your move):" << endl;
        cout << "[1] Hit" << endl;
        cout << "[2] Stand" << endl;
        cout << "[3] Double Down" << endl;
        cout << "Your move: ";
        cin >> playerMove;

        // Player enters anything but an integer
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "You have entered wrong input, please enter a number!" << endl;
        }
        // Player doesn't enter a valid move
        else if (playerMove < 1 || playerMove > 4)
        {
            cout << "Not a valid move!" << endl;
            cout << endl;
        }
        // PLayer's move is allowed
        else
            return playerMove;
    }
}

/**
* @brief Ask the user if they want to play again
*
* @param playAgain
*/
void requestPlayAgain(bool &playAgain)
{
    while (true)
    {
        cout << "\nWould you like to play again?" << endl;
        cout << "[0] Quit" << endl;
        cout << "[1] Play Again" << endl;
        cout << "Your move: ";
        cin >> playAgain;

        // Player enters anything but an integer
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "You have entered wrong input, please enter a number!" << endl;
        }
        // Player doesn't enter a choice
        else if (playAgain > 1 || playAgain < 0)
        {
            cout << "Not a valid choice!" << endl;
            cout << endl;
        }
        else
            break;
    }
}

/**
 * @brief Using RNG, "deal a card" with value between 1 and 11 (inclusive)
 * 
 * @return Card Value 
 */
int dealCard()
{
    // Random number generator (generate numbers 1-11)
    int card = rand() % 11 + 1;

    return card;
}

/**
* @brief Add card to someone's hand (either player or dealer)
*
* @param HittersHand
*/
void addCardTo(vector<int> &hittersHand)
{
    int newCard = dealCard();
    hittersHand.push_back(newCard);
}

/**
* @brief Display the total value of one's hand
*
* @param CurrentHand
*/
void displayHandTotalOf(vector<int> &currentHand)
{
    cout << accumulate(currentHand.begin(), currentHand.end(), 0) << endl;
}

/**
* @brief Update a player's hand total by adding all of their card values
*
* @param CurrentHand
* @param HandTotal
*/
void updateHandCountOf(vector<int> &currentHand, int &handTotal)
{
    // Update player hand count
    handTotal = accumulate(currentHand.begin(), currentHand.end(), 0);
}

// Line break function
void printSectionSeparator()
{
    cout << endl
         << "====================================================================" << endl;
}

int main()
{
    // Player starts with a set amount of money (i.e. how much they can bet)
    int playerBalance = 100;
    displayPlayerBalance(playerBalance);

    // Create seed for random number generator (RNG)
    srand(time(0));

    bool playAgain = true;

    while (playAgain)
    {
        // Player selects how much they want to bet ( 1 < betAmount < currentBalance)
        int currentBet = setBetAmount(playerBalance);
        playerBalance -= currentBet;
        displayPlayerBalance(playerBalance);

        // Player and Dealer Hand
        vector<int> playerHand;
        vector<int> dealerHand;

        // Add two cards to the player's hand
        addCardTo(playerHand);
        addCardTo(playerHand);

        if (playerHand[0] == 11 && playerHand[1] == 11)
            playerHand[1] = 1;

        displayIndividualCardsOfPlayer(playerHand);
        cout << "\nYour current hand total: ";
        displayHandTotalOf(playerHand);

        // Add two cards to the dealer's hand
        addCardTo(dealerHand);
        addCardTo(dealerHand);

        cout << "Dealer's first card: " << dealerHand[0] << endl;

        // Player can choose to hit, stand, or double down
        int playerMove = requestPlayerMove();

        // Player's hand summed up
        int playerHandTotal = 0;
        updateHandCountOf(playerHand, playerHandTotal);

        // Dealer's hand summed up
        int dealerHandTotal = 0;
        updateHandCountOf(dealerHand, dealerHandTotal);

        if (playerHandTotal == 21)
            playerMove = 2;

        bool continuePlaying = true;
        bool playerWins = false;
        bool playerTies = false;
        bool firstMove = true;
        bool doubleDown = false;

        while (continuePlaying)
        {
            printSectionSeparator();

            // Update player hand count
            updateHandCountOf(playerHand, playerHandTotal);

            switch (playerMove)
            {
            // If the player hits, give another card
            case 1:
            {
                // Deal a card to the player
                addCardTo(playerHand);

                // Reveal what the card is
                if (playerHand.back() == 1 || playerHand.back() == 11)
                {
                    cout << "You drew an Ace (1 or 11)" << endl;
                }
                else
                    cout << "You drew a " << playerHand.back() << endl;

                // Change the way we count depending on aces
                if (playerHand.back() == 1 && playerHandTotal < 11)
                {
                    playerHand.back() = 11;
                }
                else if (playerHand.back() == 11 && playerHandTotal > 10)
                {
                    playerHand.back() = 1;
                }

                // Update player hand count
                updateHandCountOf(playerHand, playerHandTotal);

                // Player goes over 21
                if (playerHandTotal > 21)
                {
                    displayIndividualCardsOfPlayer(playerHand);
                    displayNewPlayerHandTotal(playerHandTotal);
                    cout << "BUST!\nBetter luck next time!" << endl;
                    continuePlaying = false;
                }
                // Player gets a blackjack
                else if (playerHandTotal == 21)
                {
                    displayIndividualCardsOfPlayer(playerHand);
                    displayNewPlayerHandTotal(playerHandTotal);
                    cout << "Blackjack! You must stand now." << endl;
                    playerMove = 2;
                }
                // Player is not doubling down
                else if (!doubleDown)
                {
                    displayIndividualCardsOfPlayer(playerHand);
                    displayNewPlayerHandTotal(playerHandTotal);
                    playerMove = requestPlayerMove();
                }
                // Player wants to double down
                if (doubleDown)
                {
                    displayIndividualCardsOfPlayer(playerHand);
                    cout << "Your final hand value: " << playerHandTotal << endl;
                    playerMove = 2;
                }

                break;
            }
            // If the player stands, dealer will draw until they at least reach 17 (or bust)
            case 2:
            {
                continuePlaying = false;

                // Update dealer hand count
                updateHandCountOf(dealerHand, dealerHandTotal);

                // Reveal dealer's second card and new total
                cout << "\nDealer flips over second card and reveals a " << dealerHand.back() << endl;
                cout << "The dealer now has a total card sum of " << dealerHandTotal << endl;

                // Draw until the dealer reaches at least a total of 17
                while (dealerHandTotal < 17)
                {
                    // Dealer draws a card
                    addCardTo(dealerHand);

                    // Reveal new card to player
                    if (dealerHand.back() == 1 || dealerHand.back() == 11)
                    {
                        cout << "Dealer drew an Ace (1 or 11)" << endl;
                    }
                    else
                        cout << "Dealer drew a " << dealerHand.back() << endl;

                    // Update dealer hand count
                    updateHandCountOf(dealerHand, dealerHandTotal);

                    // Adjust card weight if its an ace
                    if (dealerHand.back() == 1 && dealerHandTotal < 11)
                    {
                        dealerHand.back() = 11;
                    }
                    else if (dealerHand.back() == 11 && dealerHandTotal >= 11)
                    {
                        dealerHand.back() = 1;
                    }
                }

                // Show dealer's final hand
                displayIndividualCardsOfDealer(dealerHand);
                cout << "Dealer's final hand: " << dealerHandTotal << endl;

                // Show player's final hand
                displayIndividualCardsOfPlayer(playerHand);
                cout << "Your hand total is ";
                displayHandTotalOf(playerHand);

                // Change bool to exit this round's loop
                continuePlaying = false;

                // Dealer busts
                if (dealerHandTotal > 21)
                {
                    playerWins = true;
                }
                // Player ties dealer
                else if (dealerHandTotal == playerHandTotal)
                {
                    playerTies = true;
                }
                // Player finishes with a better hand
                else if (dealerHandTotal < playerHandTotal)
                {
                    playerWins = true;
                }

                break;
            }
            // If the player doubles down
            case 3:
            {
                // Not the first move, can't double down
                if (firstMove == false)
                {
                    cout << "You can't double down after your first move!" << endl;
                    playerMove = requestPlayerMove();
                    break;
                }

                // Change bool
                doubleDown = true;

                // If the player doesn't have enough to double down, go all in
                if (playerBalance < currentBet)
                {
                    currentBet += playerBalance;
                    playerBalance = 0;
                    playerMove = 1;
                }
                // If the player has enough to double down
                else
                {
                    playerBalance -= currentBet;
                    currentBet *= 2;
                    playerMove = 1;
                }

                break;
            }
            // Any other case (should never get here but just in case...)
            default:
                break;
            }

            firstMove = false;
        }

        // Update player hand count
        updateHandCountOf(playerHand, playerHandTotal);

        // If player wins with a blackjack, pay them 3:2
        if (playerWins && playerHandTotal == 21)
        {
            int payout = currentBet * (3 / 2) + currentBet;
            playerBalance += payout;

            printSectionSeparator();

            cout << "\nCongratulations! You won!" << endl;
            cout << "You earned $" << currentBet * (3 / 2) << " from that round!\n"
                 << endl;
            displayPlayerBalance(playerBalance);
        }
        // If player wins without a blackjack
        else if (playerWins)
        {
            int payout = currentBet * 2;
            playerBalance += payout;

            printSectionSeparator();

            cout << "\nCongratulations! You win!" << endl;
            cout << "You earned $" << currentBet << " from that round!\n"
                 << endl;
            displayPlayerBalance(playerBalance);
        }
        // If player ties the dealer, no payout (bet gets returned)
        else if (playerTies)
        {
            playerBalance += currentBet;

            printSectionSeparator();

            cout << "\nYou tied! You get your money back!" << endl;
            displayPlayerBalance(playerBalance);
        }
        // If player lost (don't give back the bet)
        else
        {
            printSectionSeparator();

            cout << "\nYou lost, better luck next time!" << endl;
            displayPlayerBalance(playerBalance);
        }

        // No more money to bet
        if (playerBalance == 0)
        {
            printSectionSeparator();

            // No money, no play
            cout << "\nYou ran out of money! Thanks for playing, come again next time!" << endl;
            cout << "\nPress ENTER to exit." << endl;

            // Clear cin to get the "press any key to continue effect"
            cin.clear();
            cin.ignore(256, '\n');

            // Get a character/keystroke to continue
            char c = getchar();

            // Exit program
            return 0;
        }

        // If the player has money, ask if they'd like to play again
        requestPlayAgain(playAgain);
        printSectionSeparator();
    }

    // Goodbye Message
    cout << "\nThank you for playing at our casino!" << endl;
    cout << "You finished with a balance of $" << playerBalance << endl;

    // Exit instructions
    cout << "\nPress ENTER to exit." << endl;

    // Clear cin to get the "press any key to continue effect"
    cin.clear();
    cin.ignore(256, '\n');

    // Get a character/keystroke to continue
    char d = getchar();

    // Exit program
    return 0;
}