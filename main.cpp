#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 0.1;
int stop_time = 0.1;
int turnaround_time = 0.1;
int train_start_delay = 0.1;
int max_round = 1;//red
int max_round_1 = 1;//purple
int max_round_2 = 1;//green

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


std::vector <std::string> Purplelin = {
        "8 Noyabr",
        "Memar Ajami",
        "Avtovogzal",
        "Xochasan"
};

void PurplemetroTrain(int id) {

    for (int m = 0; m < max_round_1; m++) {
        // Этап 1: выезд из депо "Xochasan"
        {
            std::lock_guard<std::mutex> lock1(cout_mutex);
            std::cout << "Metro " << id << " - Train is departing from depot: Xochasan." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));

        // Поездка от "Xochasan" до "8 Noyabr"
        for (std::size_t i = 3; i >= 1; i--) {
            {
                std::lock_guard<std::mutex> lock2(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock3(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Purplelin[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        // Этап 2: возвращение в депо "Xochasan"
        {
            std::lock_guard<std::mutex> lock4(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at 8 Noyabr and heading back to depot Xochasan." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = 1; i < 4; i++) {
            {
                std::lock_guard<std::mutex> lock5(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < 3) {
                {
                    std::lock_guard<std::mutex> lock6(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Purplelin[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        // После завершения поездки поезд возвращается в депо
        {
            std::lock_guard<std::mutex> lock7(cout_mutex);
            std::cout << "Metro " << id << " - Train arrived at depot: Xochasan." << std::endl;
        }
    }
}

    std::vector<std::string> Greenline = {
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
            "Nizami",
            "Elmler Akademiyasi",
            "Inshaatcilar",
            "20 Yanvar",
            "Memar Ajami",
            "Nasimi",
            "Azadliq",
            "Darnagul"
    };

void GreenmetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(id * train_start_delay));

    for (int m = 0; m < max_round_2; m++) {
        // Первый этап: от Bakmil до Darnagul
        for (std::size_t i = 7; i < Greenline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Greenline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Greenline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at Darnagul" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        // Второй этап: от Darnagul до Hazi Aslanov (не заезжая в Bakmil)
        for (int i = static_cast<int>(Greenline.size()) - 2; i >= 0; i--) {
            if (Greenline[i] == "Bakmil") continue; // Пропустить Bakmil

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Metro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "Metro " << id << " - Train departing for " << Greenline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Metro " << id << " - Train turning around at Hazi Aslanov" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }

    // Поезд направляется в депо (Bakmil) после завершения кругов
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Metro " << id << " - Train is heading to depot: Bakmil." << std::endl;

    for (std::size_t i = 0; i <= 7; i++) {
        if (i != 0) {
            std::cout << "Metro " << id << " - Train departing for " << Greenline[i] << "..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));

        std::cout << "Metro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }

    std::cout << "Metro " << id << " - Train arrived at depot: Bakmil." << std::endl;
}


int main() {
    std::vector<std::thread> metros;
    for (int i = 1; i <= 2; i++) {
        metros.emplace_back(PurplemetroTrain, i);
    }

    for (int a = 1; a <= 2; a++) {
        metros.emplace_back(RedmetroTrain, a);
    }
    for (int b = 1; b <= 2; b++) {
        metros.emplace_back(GreenmetroTrain, b);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}
