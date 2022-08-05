#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>

#include "hangman.h"

using namespace std;

//g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic hangman.cpp -o hangman

/*
~ Blank
    -----
    |   |
    |
    |
    |
________

~ Head
    -----
    |   |
    |   o
    |
    |
________

~ Torso
    -----
    |   |
    |   o
    |   |
    |
________

~ Left Arm
    -----
    |   |
    |   o
    |  /|
    |
________

~ Right Arm
    -----
    |   |
    |   o
    |  /|\
    |
________

~ Left leg
    -----
    |   |
    |   o
    |  /|\
    |  /
________

~ Full
    -----
    |   |
    |   o
    |  /|\
    |  /\
________

*/

vector<string> words = {"abruptly", "absurd", "abyss", "affix", "askew", "avenue", "awkward", "axiom", "azure", "bagpipes", "bandwagon", "banjo", "bayou", "beekeeper", "bikini", "blitz", "blizzard", "boggle", "bookworm", "boxcar", "boxful", "buckaroo", "buffalo", "buffoon", "buxom", "buzzard", "buzzing", "buzzwords", "caliph", "cobweb", "cockiness", "croquet", "crypt", "curve", "cycle", "daiquiri", "dirndl", "disavow", "dizzying", "duplex", "dwarves", "embezzle", "equip", "espionage", "eviction", "exodus", "faking", "fishhook", "fixable", "fjord", "flapjack", "flopping", "fluffiness", "flyby", "foxglove", "frazzled", "frizzled", "fuchsia", "funny", "galaxy", "galvanize", "gazebo", "gizmo", "glowworm", "glyph", "gnarly", "gnostic", "gossip", "grogginess", "haiku", "haphazard", "hyphen", "iatrogenic", "icebox", "injury", "ivory", "ivy", "jackpot", "jaundice", "jawbreaker", "jaywalk", "jazziest", "jazzy", "jelly", "jigsaw", "jinx", "jiujitsu", "jockey", "jogging", "joking", "jovial", "joyful", "juicy", "jukebox", "jumbo", "kayak", "kazoo", "keyhole", "khaki", "kilobyte", "kiosk", "kitsch", "kiwifruit", "klutz", "knapsack", "larynx", "lengths", "lucky", "luxury", "lymph", "marquis", "matrix", "megahertz", "microwave", "mnemonic", "mystify", "naphtha", "nightclub", "nowadays", "numbskull", "nymph", "onyx", "oxidize", "oxygen", "pajama", "peekaboo", "phlegm", "pixel", "pizazz", "pneumonia", "polka", "psyche", "puppy", "puzzling", "quartz", "queue", "quips", "quixotic", "quiz", "quizzes", "quorum", "razzmatazz", "rhubarb", "rhythm", "rickshaw", "schnapps", "scratch", "shiv", "snazzy", "sphinx", "spritz", "squawk", "staff", "strength", "strengths", "stretch", "stronghold", "stymied", "subway", "swivel", "syndrome", "thriftless", "thumbscrew", "topaz", "transcript", "transgress", "transplant", "twelfth", "twelfths", "unknown", "unworthy", "unzip", "uptown", "vaporize", "vixen", "vodka", "voodoo", "vortex", "voyeurism", "walkway", "waltz", "wave", "wavy", "waxy", "wellspring", "wheezy", "whiskey", "whizzing", "whomever", "wimpy", "witchcraft", "wizard", "woozy", "wristwatch", "xylophone", "yachtsman", "yippee", "yoked", "youthful", "yummy", "zephyr" ,"zigzag", "zigzagging", "zipper", "zodiac", "zombie"};

string blank = "    -----\n    |   |\n    |\n    |\n    |\n________";
string head = "    -----\n    |   |\n    |   o\n    |\n    |\n________";
string torso = "    -----\n    |   |\n    |   o\n    |   |\n    |\n________";
string left_arm = "    -----\n    |   |\n    |   o\n    |  /|\n    |\n________";
string right_arm = "    -----\n    |   |\n    |   o\n    |  /|\\\n    |\n________";
string left_leg = "    -----\n    |   |\n    |   o\n    |  /|\\\n    |  /\n________";
string full = "    -----\n    |   |\n    |   o\n    |  /|\\\n    |  /\\\n________";

//~ blank -> head -> torso -> left_arm -> right_arm -> left_leg -> full


//@ Starting hangman class functions
//DONE
//* Executes a hangman game
void Hangman::play() {play(words[size_t((size_t)rand() % words.size())]);}

//DONE
//Overloaded play function with user-given word option
void Hangman::play(string &user_given_word) {
    while (true) {
        //~ Create word vec
        vector<pair<char, bool> > curr_word;
        curr_word.resize(user_given_word.size());
        for (size_t i = 0; i < user_given_word.size(); ++i) {
            //If char is a space, set that to true (you don't guess spaces)
            if (user_given_word[i] == ' ') {
                curr_word[i] = {user_given_word[i], true};
            }
            else {
                curr_word[i] = {user_given_word[i], false};
            }
        }

        //~ Create letters vec
        vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        //~ Start game loop
        State hangman_state = State::Blank;
        while (hangman_state != State::Full) {

            //~ Displays
            display_hangman(hangman_state);
            display_word(curr_word);
            cout << "\n";
            display_letters(letters);
            cout << "\n";

            //~ Get guess
            char guess;
            while (true) {
                cout << "Enter a letter to guess: ";
                cin >> guess;
                if (is_valid_guess(guess, letters)) {
                    letters.erase(find(letters.begin(), letters.end(), guess));
                    break;
                }
                cout << "Invalid guess, try a letter you haven't used yet\n";
            }

            //~ Check guess against word
            //* This updates curr word bool and hangman_state
            check_guess(guess, curr_word, hangman_state);

            //~ Check for completed word, if completed send winning message, return
            if (is_word_completed(curr_word)) {
                cout << user_given_word << "\n";
                cout << "Congratulations! You win!\n";
                return;
            }
        }
        //~ If this point is reached, user lost

        //While loop to validate input
        char play_again;
        while (true) {
            cout << full;
            cout << "\n\n\n";
            cout << "You lost! Would you like to try the word again? (Y, N): ";
            cin >> play_again;

            if ((play_again == 'Y') || (play_again == 'N')) {
                break;
            }
            else {
                cout << "Invalid selection! Try again\n";
            }
        }

        if (play_again == 'Y') {
        }
        else if (play_again == 'N') {
            cout << "\n\nBetter luck next time! The word was: " << user_given_word << " \n\n\n";
            return;
        }
    }
}

//DONE
void Hangman::display_hangman(State &state) {
    if (state == State::Blank) {cout << blank << "\n";}
    else if (state == State::Head) {cout << head << "\n";}
    else if (state == State::Torso) {cout << torso << "\n";}
    else if (state == State::Left_arm) {cout << left_arm << "\n";}
    else if (state == State::Right_arm) {cout << right_arm << "\n";}
    else if (state == State::Left_leg) {cout << left_leg << "\n";}
    else if (state == State::Full) {cout << full << "\n";}
    cout << "\n";
}

//DONE
void Hangman::display_word(const vector<pair<char, bool> > &curr_word) {
    for (size_t i = 0; i < curr_word.size(); ++i) {
        if (curr_word[i].second) {cout << curr_word[i].first;}
        else {cout << "_";}
    }
    cout << "\n\n";
}

//DONE
void Hangman::display_letters(const vector<char> &letters) {
    for (auto letter : letters) {cout << letter << " ";}
    cout << "\n\n";
}

//IN-PROGRESS
bool Hangman::check_guess(char letter, vector<pair<char, bool> > &curr_word, State &hangman_state) {
    pair<char, bool> pair = {letter, false};
    auto it = find(curr_word.begin(), curr_word.end(), pair);
    
    //* Letter not found, update hangman state, (already guessed is handled elsewhere) return false
    if (it == curr_word.end()) {
        if (hangman_state == State::Blank) {hangman_state = State::Head;}
        else if (hangman_state == State::Head) {hangman_state = State::Torso;}
        else if (hangman_state == State::Torso) {hangman_state = State::Left_arm;}
        else if (hangman_state == State::Left_arm) {hangman_state = State::Right_arm;}
        else if (hangman_state == State::Right_arm) {hangman_state = State::Left_leg;}
        else if (hangman_state == State::Left_leg) {hangman_state = State::Full;}
        return false;
    }

    //* Else find all instances of letter and update the bool, return true
    while (it != curr_word.end()) {
        it->second = true;
        it = find(curr_word.begin(), curr_word.end(), pair);
    }
    return true;
}

//DONE
bool Hangman::is_valid_guess(char letter, const vector<char> &letters) {
    auto it = find(letters.begin(), letters.end(), letter);
    //* Returns true (!false) if letter is found in letters, returns false (!true) if letter is not found in letters
    return !(it == letters.end());
}


bool Hangman::is_word_completed(std::vector<std::pair<char, bool> > &curr_word) {
    for (auto pair : curr_word) {
        if (pair.second == false) {return false;}
    }
    return true;
}


//@ First give option of custom word, if chosen accept that word, then call play
int main() {
    Hangman hangman_game;

    char choice;
    string word;

    //While loop to validate input
    while(true) {
        cout << "Would you like to enter your own word/phrase? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'N') {
            break;
        }
        else {
            cout << "Invalid selection! Try again\n";
        }
    }
    
    if (choice == 'Y') {
        cout << "Enter your word: ";
        cin >> word;
        //* Clear the screen
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        hangman_game.play(word);
    }
    else {hangman_game.play();}
}

//TODO
//* Fix random word always being onyx