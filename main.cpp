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

std::vector <std::string> Purpleline = {
        "8 Noyabr,"
        "Memar Ajami,"
        "Avtovogzal,"
        "Xochasan"
};

void RedmetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        // Первый этап: от Bakmil до Icherisheher
        for (std::size_t i = 7; i < Redline.size(); i++) {
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

        // Второй этап: от Icherisheher до Hazi Aslanov (не заезжая в Bakmil)
        for (int i = static_cast<int>(Redline.size()) - 2; i >= 0; i--) {
            if (Redline[i] == "Bakmil") continue; // Пропустить Bakmil

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
            std::cout << "Metro " << id << " - Train turning around at Hazi Aslanov" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        // Третий этап: от Hazi Aslanov до Icherisheher (минуя Bakmil)
        for (std::size_t i = 0; i < Redline.size(); i++) {
            if (Redline[i] == "Bakmil") continue; // Пропустить Bakmil

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1 && Redline[i + 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Redline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }

    // Поезд направляется в депо (Bakmil) после завершения кругов
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train is heading to depot: Bakmil." << std::endl;

    if (Redline.back() == "Icherisheher") {
        for (int i = static_cast<int>(Redline.size()) - 1; i >= 7; i--) {
            if (i != static_cast<int>(Redline.size()) - 1) {
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    } else {
        for (std::size_t i = 0; i <= 7; i++) {
            if (i != 0) {
                std::cout << "Metro " << id << " - Train departing for " << Redline[i] << "..." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "Metro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    }

    std::cout << "Metro " << id << " - Train arrived at depot: Bakmil." << std::endl;
}


int main() {
    std::vector<std::thread> metros;

    // Для запуска только красной линии
    for (int i = 1; i <= 1; i++) {
        metros.emplace_back(RedmetroTrain, i);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}
