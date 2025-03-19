#include "MetroBaku.h"
#include <fstream>

int main() {
    std::ofstream redlineFile("Redline_output.txt");
    std::ofstream greenlineFile("Greenline_output.txt");
    std::ofstream purplelineFile("Purpleline_output.txt");
    std::ofstream lightgreenlineFile("Lightgreenline_output.txt");

    if (!redlineFile.is_open() || !greenlineFile.is_open() || !purplelineFile.is_open() || !lightgreenlineFile.is_open()) {
        std::cerr << "Failed to open output files!" << std::endl;
        return 1;
    }

    std::vector<std::thread> metros;
    int total_trains = 2;

    for (int i = 1; i <= total_trains; i++) {
        if (i % 2 == 1) {
            metros.emplace_back(RedmetroTrain, i, std::ref(redlineFile));  // Pass redlineFile by reference
        } else {
            metros.emplace_back(GreenmetroTrain, i, std::ref(greenlineFile));
        }
    }

    for (int j = 1; j <= 2; j++) {
        metros.emplace_back(PurplemetroTrain, j, std::ref(purplelineFile));
    }

    for (int k = 1; k <= 2; k++) {
        metros.emplace_back(LightgreenTrainMetro, k, std::ref(lightgreenlineFile));
    }

    for (auto& t : metros) {
        t.join();
    }

    redlineFile.close();
    greenlineFile.close();
    purplelineFile.close();
    lightgreenlineFile.close();

    return 0;
}
