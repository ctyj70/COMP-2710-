/*
* CJ Young
*
* Project4_Young_cty0008
*
* Project 4 - Trivia Game
* 
* Comp 2710
*
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct Trivia {
    // Node Structure
    // String pointValue for how many points a question is worth

    struct TriviaNode {

        TriviaNode* next;

        string answer;

        string question;

        int pointValue;

        TriviaNode(string question_input, string answer_input, int value_input) {

            next = nullptr;

            answer = answer_input;

            question = question_input;

            pointValue = value_input;


        }
    };

    // Iterator
    struct TriviaIterator {

        TriviaNode* currentState;

        TriviaIterator(TriviaNode* node_input) {

            currentState = new TriviaNode("", "", 0);
            currentState->next = node_input;

        }

        bool has_next() {

            return currentState->next != nullptr;

        }

        TriviaNode next() {

            currentState = currentState->next;
            return (*currentState);

        }
    };

    // List Variables

    TriviaNode* beginning;
    TriviaNode* end;

    int size;
    int score;

    Trivia() {

        beginning = nullptr;
        end = nullptr;
        size = 0;
        score = 0;
    }

    bool add(string question_input, string answer_input, int value_input) {

        TriviaNode* new_triva_node = new TriviaNode(question_input, answer_input, value_input);
        if (size == 0) {

            beginning = new_triva_node;
        }
        else {

            end->next = new_triva_node;
        }

        end = new_triva_node;
        size++;
        return true;
    }

    TriviaIterator iterator() {

        return TriviaIterator(beginning);
    }

    // Prompt user to add a question
    void addQuestion() {

        string new_question;
        string new_answer;
        string point_Value_Response;
        int new_point_value;

        cout << "Enter a question: ";
        getline(cin, new_question);

        cout << "Enter an answer: ";
        getline(cin, new_answer);

        cout << "Enter award points: ";
        getline(cin, point_Value_Response);

        new_point_value = stoi(point_Value_Response);
        add(new_question, new_answer, new_point_value);
    }

    // Ask the specified number of questions

    bool askQuestion(int numberOfAsk) {

        if (numberOfAsk < 1) {

            cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << endl;
            return false;
        }

        else if (size < numberOfAsk) {

            cout << "Warning - there (is/are) only " << size << " trivia question(s) in the list." << endl;
            return false;
        }

        else {

            score = 0;
            TriviaIterator itr = iterator();
            int count = 0;

            while (itr.has_next() && count < numberOfAsk) {

                TriviaNode currentState = itr.next();
                string player_answer;
                cout << "\nQuestion: " << currentState.question;
                cout << "\nAnswer: ";
                getline(cin, player_answer);

                if (player_answer.compare(currentState.answer) == 0) {

                    cout << "Your answer is correct. You receive " << currentState.pointValue << " points." << endl;
                    score += currentState.pointValue;
                }

                else {

                    cout << "Your answer is wrong. The correct answer is: " << currentState.answer << endl;
                }

                cout << "Your total points: " << score << endl;
                count++;
            }
            return true;
        }
    }

    // Initialize a list with some example questions. Currently accepted versions are 0 and 1

    void promptQuestions(int version) {
        size = 0;
        score = 0;
        if (version > -1) {  // Version 0 selects this list only
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
        }
        if (version > 0) {  // Version 1 adds this block and the previous
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?", "Bank of Germany", 50);
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
        }
    }
};

// Conditional Compilation
#define trivia_quiz

//#define UNIT_TESTING

int main() {

    Trivia game = Trivia();

#ifdef trivia_quiz

    cout << "*** Welcome to CJ's trivia quiz game ***" << endl;

    bool add_more = false;
    do {

        game.addQuestion();
        string player_response = "";
        while (player_response == "") {
            cout << "Continue? (Y/N): ";
            getline(cin, player_response);
            if (player_response.at(0) == 'y' || player_response.at(0) == 'Y') {
                add_more = true;
            }
            else if (player_response.at(0) == 'n' || player_response.at(0) == 'N') {
                add_more = false;
            }
            else {
                cout << "Invalid Response" << endl;
                player_response = "";
            }
        }
    } while (add_more);

    cout << "\n\nWelcome to the Trivia Game!" << endl;
    game.askQuestion(game.size);

    cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***";

#endif


#ifdef UNIT_TESTING

    cout << "*** This is a debugging version ***" << endl;
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
    bool warning = game.askQuestion(0);
    assert(!warning);
    cout << "\nCase 1 Passed" << endl << endl;

    game.promptQuestions(1);
    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    game.askQuestion(1);
    assert(game.score == 0);
    cout << "\nCase 2.1 passed" << endl << endl;

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    game.askQuestion(1);
    assert(game.score == 100);
    cout << "\nCase 2.2 passed" << endl << endl;

    cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
    bool played = game.askQuestion(3);
    assert(played);
    cout << "\nCase 3 passed" << endl << endl;

    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    warning = game.askQuestion(5);
    assert(!warning);
    cout << "\nCase 4 passed" << endl << endl;

    cout << "*** End of debugging version ***";
#endif

    return 0;
}
