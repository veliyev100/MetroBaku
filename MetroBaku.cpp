#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

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
std::vector <std::string> Purpleline = {
    "Xochasan",
    "Avtovogzal",
    "Memar Ajami",
    "8 Noyabr"
};
std::vector<std::string> Lightgreenline = {
     "28 May", "Xatai"
};

// Parameters
int travel_time = 5;
int stop_time = 2;
int turnaround_time = 3;
int train_start_delay = 2;
int max_round = 2;

void RedmetroTrain(int id, std::ofstream &outFile) {
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 7; i < Redline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Redline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "RedlineMetro " << id << " - Train departing for " << Redline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            outFile << "RedlineMetro " << id << " - Train turning around at " << Redline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Redline.size()) - 1; i >= 0; i--) {
            if (Redline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "RedlineMetro " << id << " - Train arrived at: " << Redline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0 && Redline[i - 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "RedlineMetro " << id << " - Train departing for " << Redline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }
}

void GreenmetroTrain(int id, std::ofstream &outFile) {
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 7; i < Greenline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "GreenlineMetro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Greenline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "GreenlineMetro " << id << " - Train departing for " << Greenline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            outFile << "GreenlineMetro " << id << " - Train turning around at " << Greenline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Greenline.size()) - 1; i >= 0; i--) {
            if (Greenline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "GreenlineMetro " << id << " - Train arrived at: " << Greenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0 && Greenline[i - 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "GreenlineMetro " << id << " - Train departing for " << Greenline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }
}

void PurplemetroTrain(int id, std::ofstream &outFile) {
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 0; i < Purpleline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "PurplelineMetro " << id << " - Train arrived at: " << Purpleline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Purpleline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "PurplelineMetro " << id << " - Train departing for " << Purpleline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            outFile << "PurplelineMetro " << id << " - Train turning around at " << Purpleline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Purpleline.size()) - 1; i >= 0; i--) {
            if (Purpleline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "PurplelineMetro " << id << " - Train arrived at: " << Purpleline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0 && Purpleline[i - 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "PurplelineMetro " << id << " - Train departing for " << Purpleline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }
}

void LightgreenTrainMetro(int id, std::ofstream &outFile) {
    std::this_thread::sleep_for(std::chrono::duration<double>(1.2 * id * train_start_delay));

    for (int m = 0; m < max_round; m++) {
        for (std::size_t i = 0; i < Lightgreenline.size(); i++) {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "LightgreenlineMetro " << id << " - Train arrived at: " << Lightgreenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i < Lightgreenline.size() - 1) {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "LightgreenlineMetro " << id << " - Train departing for " << Lightgreenline[i + 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            outFile << "LightgreenlineMetro " << id << " - Train turning around at " << Lightgreenline.back() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(turnaround_time));

        for (int i = static_cast<int>(Lightgreenline.size()) - 1; i >= 0; i--) {
            if (Lightgreenline[i] == "Bakmil") continue;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                outFile << "LightgreenlineMetro " << id << " - Train arrived at: " << Lightgreenline[i] << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(stop_time));

            if (i > 0 && Lightgreenline[i - 1] != "Bakmil") {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    outFile << "LightgreenlineMetro " << id << " - Train departing for " << Lightgreenline[i - 1] << "..." << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(travel_time));
            }
        }
    }
}