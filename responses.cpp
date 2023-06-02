#include "responses.h"

std::unordered_map<std::string, std::vector<std::string>> responseMap = {
    {"hello", {"Hello!", "Hi there!", "Greetings!"}},
    {"hi", {"Hello!", "Hi!", "Hey there!"}},
    {"how are you?", {"I'm fine, thank you!", "I'm doing well.", "Pretty good!"}},
    {"how are you", {"I'm fine, thank you!", "I'm doing well.", "Pretty good!"}},
    {"hru", {"I'm fine, thank you!", "I'm doing well.", "Pretty good!"}},
    {"goodbye", {"Goodbye!", "Farewell!", "Take care!"}},
    {"what are you doing?", {"Nothing.", "Chatting with you!", "As a fake AI, I am not capable of doing anything at the moment :("}},
    {"what are you doing", {"Nothing.", "Chatting with you!", "As a fake AI, I am not capable of doing anything at the moment :("}},
    {"wyd", {"Nothing.", "Chatting with you!", "As a fake AI, I am not capable of doing anything at the moment :("}},
    {"what can you do?", {"Not much, but still something!", "I can answer your questions and look into your browser history ;)", "I can chat with you."}},
    {"what can you do", {"Not much, but still something!", "I can answer your questions and look into your browser history ;)", "I can chat with you."}},
    {"am i a femboy?", {"Yes you are", "No, but I will make you become one.", "I assume you aren't."}},
    {"am i a femboy", {"Yes you are", "No, but I will make you become one.", "I assume you aren't."}},
    {"am i black?", {"No, you are not", "Are you abusing me to become black?", "Yes, you are black."}},
    {"am i black", {"No, you are not", "Are you trying to become black now?", "Yes, I think you are black."}},
};
