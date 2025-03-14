#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 0.1;
int stop_time = 0.1;
int turnaround_time = 0.1;
int train_start_delay = 0.1;
int max_round = 1;
int max_round_1 = 1;

std::mutex cout_mutex;// избегаем перемешивания вывода
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
        for (std::size_t i = 7; i < Redline.size(); i++) {//size_t eto bezznakovaya peremennaya
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i + 1] << "..." << "\n";
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at " << Redline.back() << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {//static_cast eto preobrozovaniye odnoqo tipa v druqoy
            if (Redline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i - 1] << "..." << "\n";
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at Hazi Aslanov" << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (std::size_t i = 0; i < Redline.size(); i++) {
            if (Redline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1 && Redline[i + 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i + 1] << "..." << "\n";
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train is heading to depot: Bakmil." << "\n";

    if (Redline.back() == "Icherisheher") {
        for (int i = static_cast<int>(Redline.size()) - 1; i >= 7; i--) {
            if (i != static_cast<int>(Redline.size()) - 1) {
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    } else {
        for (std::size_t i = 0; i <= 7; i++) {
            if (i != 0) {
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." <<"\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    }


 std::cout << "Metro " << id << " - Train arrived at depot: Bakmil." << "\n";
}





std::vector <std::string> Purplelin = {
        "8 Noyabr",
        "Memar Ajami",
        "Avtovogzal",
        "Xochasan"
};

void PurplemetroTrain(int id) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train is departing from depot: Xochasan." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(travel_time));

    for (std::size_t i = 3; i >= 1; i--) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));

        if (i > 0) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train departing for " << Purplelin[i - 1] << "..." << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));
        }
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train turning around at 8 Noyabr and heading back to depot Xochasan." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

    for (int i = 1; i < 4; i++) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));

        if (i < 3) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train departing for " << Purplelin[i + 1] << "..." << "\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));
        }
    }


    std::cout << "Metro " << id << " - Train arrived at depot: Xochasan." << "\n";
}


int main() {
    std::vector<std::thread> metros;

    for (int a = 1; a <= 1; a++) {
        metros.emplace_back(PurplemetroTrain, a);
    }

//    for (int i = 1; i <= 1; i++) {
//        metros.emplace_back(RedmetroTrain, i);
//    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}