#include <iostream>
#include <limits>
#include <random>


// PRNG code
namespace Random
{
    // Picks a number from the ran_device of the os
    std::random_device rd;

    // Initialize seed_seq with 8 random numbers, let the rest be filled by seed_seq
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), };

    // Create PRNG with seed_seq as seed
    std::mt19937 mt{ ss };

    // Function to let users call to get a random number(aka the next sequence)
    int getRandomNumber(int min, int max)
    {
        std::uniform_int_distribution die(min, max);
        return die(mt);
    }

}


void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// return true if play won, else return false
bool play_game(int num_guess, int random_number)
{
    for (int i{ 1 }; i <= num_guess; ++i)
    {
        int user_guess{ 0 };
        std::cout << "Guess #" << i << ": ";
        std::cin >> user_guess;

        
        // error handling: extraction fails + overflow
        if (std::cin.fail() == true)
        {
            std::cin.clear();
            ignoreLine();
        }
        else
        {
            ignoreLine();
        }
        
        std::cout << "You've guessed: " << user_guess << '\n';


        // Check if user guess is within range
        if (user_guess <= 0 || user_guess > 100)
        {
            ignoreLine(); // remove bad input
            std::cout << "Error: your guess is out of range. Try Again.\n";
            --i;
            continue;
        }

        // Check if the user got it right
        if (user_guess == random_number)
            return true;

        // Check if the user guess is too high or low
        if (user_guess > random_number)
            std::cout << "Your guess is too high.\n";
        else
            std::cout << "Your guess is too low.\n";

    }
    // the user ran out of guesses
    return false;
}


bool play_again() {
    
    while (true) // error handling: extraction succeeds but it's meaningless
    {
        char input_yes_or_no{};
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> input_yes_or_no;
        ignoreLine();

        // make user type 'y' or 'n'
        switch (input_yes_or_no)
        {
        case 'y':
            return true;
        case 'n':
            return false;
        }
    
    }

}


int main()
{
    constexpr int number_of_guesses{ 7 };

    do
    {
        int random_number{ Random::getRandomNumber(1,100) };
        std::cout << random_number << "Let's play a game. I'm thinking of a number between 1 and 100. You have " << number_of_guesses << " tries to guess what it is.\n";
        
        bool win_status{ play_game(number_of_guesses, random_number) };

        if (win_status)
            std::cout << "Correct! You win!\n";
        else
            std::cout << "Sorry, you lose. The correct number was " << random_number << ".\n";

    } while (play_again());
 

    std::cout << "Thank you for playing\n";
    return 0;
}