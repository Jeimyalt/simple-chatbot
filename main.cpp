#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <thread>
#include "responses.h"

std::string previousQuery = "";
bool isAskingMainResponse = false; // Added flag to track if a main response is being asked

bool hasSlur(const std::string& userInput) {
    static const std::vector<std::string> slurs = {
        "fag",
        "fags",
        "faggot",
        "faggots",
        "nigger",
        "niggers",
        "nig",
        "nigs",
        "kys",
        "kill yourself",
        "end yourself",
        "end it all"
    };

    std::string lowerCaseInput = userInput;
    std::transform(lowerCaseInput.begin(), lowerCaseInput.end(), lowerCaseInput.begin(), ::tolower);

    for (const std::string& slur : slurs) {
        if (lowerCaseInput.find(slur) != std::string::npos) {
            return true;
        }
    }

    return false;
}

std::string generateResponse(const std::string& userInput) {
    std::string response = "I'm sorry, I don't have an answer for that.";
    std::string lowerCaseInput = userInput;
    std::transform(lowerCaseInput.begin(), lowerCaseInput.end(), lowerCaseInput.begin(), ::tolower);

    int bestMatchCount = 0;
    std::string bestMatch;

    for (const auto& pair : responseMap) {
        const std::string& keyword = pair.first;
        int matchCount = 0;
        int mismatchCount = 0;

        for (size_t i = 0; i < keyword.length(); ++i) {
            if (i < lowerCaseInput.length() && keyword[i] == lowerCaseInput[i]) {
                matchCount++;
            }
            else {
                mismatchCount++;
            }
        }

        if (matchCount > bestMatchCount && mismatchCount <= 1) {
            bestMatchCount = matchCount;
            bestMatch = keyword;
        }
    }

    if (bestMatchCount >= lowerCaseInput.length() - 1 && !bestMatch.empty()) {
        const std::vector<std::string>& possibleResponses = responseMap[bestMatch];
        int index = std::rand() % possibleResponses.size();
        response = possibleResponses[index];
    }

    if (lowerCaseInput == previousQuery) {
        response = "We've already discussed that. Let's talk about something else.";
    }

    if (!isAskingMainResponse) {
        if (lowerCaseInput == "ok" || lowerCaseInput == "okay" || lowerCaseInput == "thx" || lowerCaseInput == "ty" || lowerCaseInput == "thank you" || lowerCaseInput == "thanks") {
            response = "If you still have questions, feel free to ask!";
            isAskingMainResponse = true;
        }

        if (lowerCaseInput == "my age" || lowerCaseInput == "what is my age" || lowerCaseInput == "what is my age?") {
            response = "Your age is " + std::to_string(std::rand() % 101);
            isAskingMainResponse = true;
        }
    }
    else {
        isAskingMainResponse = false;
    }

    previousQuery = lowerCaseInput;

    return response;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    SetConsoleTitleA("Fake-AI");
    std::cout << "Chat Application\n";
    std::cout << "Enter 'exit' to quit.\n";

    while (true) {
        std::string userInput;
        std::cout << "You: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            break;
        }

        if (hasSlur(userInput)) {
            std::cout << "Slur detected. Closing the program." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }

        if (userInput == "bye" || userInput == "goodbye" || userInput == "ciao") {
            std::cout << "Goodbye.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        }

        std::string response = generateResponse(userInput);
        std::cout << "Sammygpt: " << response << "\n";
    }

    return 0;
}
