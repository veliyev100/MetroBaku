#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 1;
int stop_time = 1;
int turnaround_time = 4;
int train_start_delay = 18;
int max_round = 2;

std::mutex cout_mutex;
std::vector <std::string> Purpleline = {
    "8 Noyabr,"
    "Memar Ajami,"
    "Avtovogzal,"
    "Xochasan"
};
std::vector <std::string> Redline = {
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
        for (std::size_t i = 0; i < Redline.size(); i++) {
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

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.front() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }
}

int main() {
    std::vector<std::thread> metros;

    for (int i = 1; i <= 6; i++) {
        metros.emplace_back(RedmetroTrain, i);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}