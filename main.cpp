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

bool hasSlur(const std::string& userInput) {
    static const std::vector<std::string> slurs = {
        "fag",
        "fags",
        "faggot",
        "faggots",
        "nigger",
        "niggers",
        "nig",
        "nigs"
        // Add more slurs if needed
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

    for (const auto& pair : responseMap) {
        const std::string& keyword = pair.first;
        std::string pattern = "\\b" + keyword + "\\b";
        if (lowerCaseInput.find(keyword) != std::string::npos) {
            const std::vector<std::string>& possibleResponses = pair.second;
            int index = std::rand() % possibleResponses.size();
            response = possibleResponses[index];
            break;
        }
    }

    if (lowerCaseInput == previousQuery) {
        response = "We've already discussed that. Let's talk about something else.";
    }
    else if (lowerCaseInput == "ok" || lowerCaseInput == "okay") {
        response = "If you still have questions, feel free to ask!";
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
