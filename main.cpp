#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 0.1;
int stop_time = 0.1;
int turnaround_time = 0.2;
int train_start_delay = 0.1;
int max_round = 1;
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
        for (std::size_t i = 7; i < Redline.size(); i++) {

            if (i > 7) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << "\n";
            }

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.back() << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {
            if (Redline[i] == "Bakmil") continue; // Исключаем Bakmil

            if (i < static_cast<int>(Redline.size()) - 1) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << "\n";
            }

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at Hazi Aslanov" << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (std::size_t i = 0; i < Redline.size(); i++) {
            if (Redline[i] == "Bakmil") continue; // Исключаем Bakmil

            if (i > 0) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << "\n";
            }

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train is heading to depot: Bakmil." << "\n";

    for (std::size_t i = 7; i < Redline.size(); i++) {
        if (Redline[i] == "Bakmil") continue; // Исключаем Bakmil

        if (i > 7 && Redline[i - 1] != "Bakmil") {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << "\n";
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }

    std::cout << "Metro " << id << " - Train arrived at depot: Bakmil." << "\n";
}


// void PurplemetroTrain(int id) {
//     std::this_thread::sleep_for(std::chrono::seconds(id * train_start_delay));
//
//     for (int n = 0; n < max_round_1; n++) {
//         for (std::size_t i = 0; i < Purplelin.size(); i++) {
//             {
//                 std::lock_guard<std::mutex> lock(cout_mutex);
//                 std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
//             }
//             std::this_thread::sleep_for(std::chrono::seconds(stop_time));
//
//             if (i < Purplelin.size() - 1) {
//                 {
//                     std::lock_guard<std::mutex> lock(cout_mutex);
//                     std::cout << "Metro " << id << " - Train departing for " << Purplelin[i + 1] << "..." << std::endl;
//                 }
//                 std::this_thread::sleep_for(std::chrono::seconds(travel_time));
//             }
//         }
//
//         {
//             std::lock_guard<std::mutex> lock(cout_mutex);
//             std::cout << "Metro " << id << " - Train turning around at " << Purplelin.back() << std::endl;
//         }
//         std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
//
//         for (int i = static_cast<int>(Purplelin.size()) - 1; i >= 0; i--) {
//             {
//                 std::lock_guard<std::mutex> lock(cout_mutex);
//                 std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
//             }
//             std::this_thread::sleep_for(std::chrono::seconds(stop_time));
//
//             if (i > 0) {
//                 {
//                     std::lock_guard<std::mutex> lock(cout_mutex);
//                     std::cout << "Metro " << id << " - Train departing for " << Purplelin[i - 1] << "..." << std::endl;
//                 }
//                 std::this_thread::sleep_for(std::chrono::seconds(travel_time));
//             }
//         }
//
//         {
//             std::lock_guard<std::mutex> lock(cout_mutex);
//             std::cout << "Metro " << id << " - Train turning around at " << Purplelin.front() << std::endl;
//         }
//         std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
//     }
// }


int main() {
    std::vector<std::thread> metros;

    // for (int a = 1; a <= 6; a++) {
    //     metros.emplace_back(PurplemetroTrain, a);
    // }

    for (int i = 1; i <= 1; i++) {
        metros.emplace_back(RedmetroTrain, i);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}