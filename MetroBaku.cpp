#include "MetroBaku.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

int travel_time = 3;
int stop_time = 2;
int turnaround_time = 2;
int train_start_delay = 3;
int max_round = 1;//red
int max_round_1 = 1;//purple
int max_round_2 = 1;//green
int max_round_3 = 2;//lightgreen

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
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 7; i < Redline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "RedlineMetro " << id << " - Train departing for " << Redline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "RedlineMetro " << id << " - Train turning around at " << Redline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {
            if (Redline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (Redline[i] == "Nariman Narimanov" && i > 0) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "RedlineMetro " << id << " - RedlineMetro departing for Ulduz..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }

            if (i > 0 && Redline[i - 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "RedlineMetro " << id << " - Train departing for " << Redline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "RedlineMetro " << id << " - Train turning around at Hazi Aslanov" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (std::size_t i = 0; i < Redline.size(); i++) {
            if (Redline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            // Добавлена проверка для Nariman Narimanov в прямом направлении
            if (Redline[i] == "Ulduz" && i < Redline.size() - 1) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "RedlineMetro " << id << " - Train departing for Nariman Narimanov..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }

            if (i < Redline.size() - 1 && Redline[i + 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "RedlineMetro " << id << " - Train departing for " << Redline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "RedlineMetro " << id << " - Train is heading to depo: Bakmil." << std::endl;

    if (Redline.back() == "Icherisheher") {
        for (int i = static_cast<int>(Redline.size()) - 1; i >= 7; i--) {
            if (i != static_cast<int>(Redline.size()) - 1) {
                std::cout << "RedlineMetro " << id << " - Train departing for " << Redline[i] << "..." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    } else {
        for (std::size_t i = 0; i <= 7; i++) {
            if (i != 0) {
                std::cout << "RedlineMetro " << id << " - Train departing for " << Redline[i] << "..." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(travel_time));

            std::cout << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
        }
    }

    std::cout << "RedlineMetro " << id << " - Train arrived at depo: Bakmil." << std::endl;
}


std::vector <std::string> Purplelin = {
        "8 Noyabr",
        "Memar Ajami",
        "Avtovogzal",
        "Xochasan"
};

void PurplemetroTrain(int id) {
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round_1; m++) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "PurplelineMetro " << id << " - Train is departing from depo: Xochasan." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));

        for (int i = static_cast<int>(Purplelin.size()) - 1;i >= 0; i--) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "PurplelineMetro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "PurplelineMetro " << id << " - Train departing for " << Purplelin[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "PurplelineMetro " << id << " - Train turning around at 8 Noyabr" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = 0; i < 4; i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "PurplelineMetro " << id << " - Train arrived at: " << Purplelin[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < 3) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "PurplelineMetro " << id << " - Train departing for " << Purplelin[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "PurplelineMetro " << id << " - Train arrived at depo: Xochasan." << std::endl;
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
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));
    for (int m = 0; m < max_round_2; m++) {
        for (std::size_t i = 7; i < Greenline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "GreenlineMetro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Greenline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "GreenlineMetro " << id << " - Train departing for " << Greenline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "GreenlineMetro " << id << " - Train turning around at Darnagul" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Greenline.size()) - 1; i >= 0; i--) {
            if (Greenline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "GreenlineMetro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));
            if (Greenline[i] == "Nariman Narimanov" && i > 0) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "GreenlineMetro " << id << " - Train departing for Ulduz..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }

            if (i > 0 && Greenline[i-1] != "Bakmil" ) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "GreenlineMetro " << id << " - Train departing for " << Greenline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "GreenlineMetro " << id << " - Train turning around at Hazi Aslanov" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "GreenlineMetro " << id << " - Train is heading to depo: Bakmil." << std::endl;

    for (std::size_t i = 0; i <= 7; i++) {
        if (i != 0) {
            std::cout << "GreenlineMetro " << id << " - Train departing for " << Greenline[i] << "..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));

        std::cout << "GreenlineMetro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }

    std::cout << "GreenlineMetro " << id << " - Train arrived at depo: Bakmil." << std::endl;
}

std::vector<std::string> Lightgreenline = {
        "28 May",
        "Xatai"
};


std::mutex line_mutex;

void LightgreenTrainMetro(int id) {
    for (int h = 0; h < max_round_3; h++) {
        int start_index = id % 2;
        int end_index = (id + 1) % 2;

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "LightGreenlineMetro " << id << " departing for " << Lightgreenline[end_index] << "..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(travel_time));
        {
            std::lock_guard<std::mutex> lock(line_mutex);
            std::lock_guard<std::mutex> lock2(cout_mutex);
        }

        std::this_thread::sleep_for(std::chrono::seconds(travel_time));

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "LightGreenlineMetro " << id << " arrived at: " << Lightgreenline[end_index] << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(stop_time));
    }
}
