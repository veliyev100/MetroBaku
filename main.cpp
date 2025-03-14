#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 4;
int stop_time = 5;
int turnaround_time = 4;
int train_start_delay = 6;
int max_round = 2;
int max_round_1 = 3;

std::mutex cout_mutex;
std::vector <std::string> Purpleline = {
        "8 Noyabr,"
        "Memar Ajami,"
        "Avtovogzal,"
        "Xochasan"
};
std::vector<std::string> Redline = {
    "Hazi Aslanov",
    "Ahmadli",
    "Xalqlar Dostlugu",
    "Nefchiler",
    "Qara Qarayev",
    "Koroglu",
    "Ulduz",
    "Bakmil",
    "Nariman Narimanov",
    "Ganjlik",
    "28 May",
    "Sahil",
    "Icherisheher"
};

void RedmetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        // First leg of the journey: Bakmil -> Icherisheher
        for (std::size_t i = 7; i < Redline.size(); i++) {  // Start from Bakmil (index 7)
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        // Turning around at Icherisheher
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        // Second leg of the journey: Icherisheher -> Hazi Aslanov, skipping Bakmil
        for (int i = static_cast<int>(Redline.size()) - 2; i >= 0; i--) {  // Start from Icherisheher and go backward
            if (Redline[i] == "Bakmil") {
                continue;  // Skip Bakmil on the return journey
            }

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0 && Redline[i - 1] != "Bakmil") {  // Skip Bakmil during departure
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        // Turning around at Hazi Aslanov (start of the line)
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.front() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }
}

std::vector <std::string> Purplelin = {
        "8 Noyabr",
        "Memar Ajami",
        "Avtovogzal",
        "Xochasan"
};

void PurplemetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(id * train_start_delay));

    for (int n = 0; n < max_round_1; n++) {
        for (std::size_t i = 0; i < Purplelin.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Purplelin.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Purplelin[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Purplelin.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Purplelin.size()) - 1; i >= 0; i--) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Purplelin[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Purplelin.front() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }
}


int main() {
    std::vector<std::thread> metros;

    for (int a = 1; a <= 6; a++) {
        metros.emplace_back(PurplemetroTrain, a);
    }

    for (int i = 1; i <= 6; i++) {
        metros.emplace_back(RedmetroTrain, i);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}