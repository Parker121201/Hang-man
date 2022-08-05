#include <string>

//~ blank -> head -> torso -> left_arm -> right_arm -> left_leg -> full
enum class State {
    Blank,
    Head,
    Torso,
    Left_arm,
    Right_arm,
    Left_leg,
    Full
};

class Hangman {
//~ Public functions
public:
//Executes a hangman game
void play();

//Overloaded play function with user-given word option
void play(std::string &user_given_word);

//~ Private functions
private:
//Displays hangman with newline character at end
void display_hangman(State &state);

//Displays current word with appropriate spaces and newline character at end
void display_word(const std::vector<std::pair<char, bool> > &curr_word);

//Displays remaining letters underneath word being guessed and hangman
void display_letters(const std::vector<char> &letters);

//Checks letter guess against word, modifies word if appropriate
//if modified, returns true, else returns false
bool check_guess(char letter, std::vector<std::pair<char, bool> > &curr_word, State &hangman_state);

//Returns true if letter is a valid guess (i.e. hasn't been guessed before)
bool is_valid_guess(char letter, const std::vector<char> &letters);

//Returns true if word is fully guessed, else false
bool is_word_completed(std::vector<std::pair<char, bool> > &curr_word);

//~ Public data
public:


//~ Private data
private:
};