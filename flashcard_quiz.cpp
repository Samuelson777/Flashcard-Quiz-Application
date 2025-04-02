#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower
#include <limits>    // For std::numeric_limits
#include <sstream>   // For std::stringstream

struct Flashcard {
    std::string question;
    std::string answer;
};

// Function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& str) {
    std::stringstream ss(str);
    std::string trimmed;
    ss >> trimmed; // This will ignore leading whitespace
    return trimmed;
}

void addFlashcard(std::vector<Flashcard>& flashcards) {
    Flashcard newCard;
    std::cout << "Enter the question: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, newCard.question);
    std::cout << "Enter the answer: ";
    std::getline(std::cin, newCard.answer);
    flashcards.push_back(newCard);
    std::cout << "Flashcard added!\n";
}

void takeQuiz(const std::vector<Flashcard>& flashcards) {
    if (flashcards.empty()) {
        std::cout << "No flashcards available. Please add some first.\n";
        return;
    }

    int score = 0;
    for (const auto& card : flashcards) {
        std::string userAnswer;
        std::cout << "Question: " << card.question << "\n";
        std::cout << "Your answer: ";
        
        // Clear the input buffer before reading the answer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, userAnswer);

        // Trim whitespace and convert to lowercase for comparison
        std::string trimmedUser = trim(userAnswer); 
        std::string correctAnswer = toLower(card.answer);

        if (toLower(trimmedUser) == correctAnswer) {
            std::cout << "Correct!\n";
            score++;
        } else {
            std::cout << "Wrong! The correct answer is: " << card.answer << "\n";
        }
    }
    std::cout << "You scored " << score << " out of " << flashcards.size() << ".\n";
}

void saveFlashcards(const std::vector<Flashcard>& flashcards) {
    std::ofstream outFile("flashcards.txt");
    for (const auto& card : flashcards) {
        outFile << card.question << "\n" << card.answer << "\n";
    }
    outFile.close();
    std::cout << "Flashcards saved to flashcards.txt.\n";
}

void loadFlashcards(std::vector<Flashcard>& flashcards) {
    std::ifstream inFile("flashcards.txt");
    if (!inFile) {
        std::cout << "No saved flashcards found.\n";
        return;
    }
    Flashcard card;
    while (std::getline(inFile, card.question) && std::getline(inFile, card.answer)) {
        flashcards.push_back(card);
    }
    inFile.close();
    std::cout << "Flashcards loaded from flashcards.txt.\n";
}

int main() {
    std::vector<Flashcard> flashcards;
    loadFlashcards(flashcards);

    int choice;
    do {
        std::cout << "\n1. Add Flashcard\n2. Take Quiz\n3. Save Flashcards\n4. Load Flashcards\n5. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFlashcard(flashcards);
                break;
            case 2:
                takeQuiz(flashcards);
                break;
            case 3:
                saveFlashcards(flashcards);
                break;
            case 4:
                loadFlashcards(flashcards);
                break;
            case 5:
                std::cout << "Exiting the application. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}