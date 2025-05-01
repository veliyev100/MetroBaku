#include "MetroBaku.h"

int main() {
    std::vector<std::thread> metros;

    int total_trains = 0;
    for (int i = 0; i <= total_trains; i++) {
        if (i % 2 == 1) {
            metros.emplace_back(RedmetroTrain, i);
        } else {
            metros.emplace_back(GreenmetroTrain, i);
        }
    }
    for (int j = 1; j <= 2; j++) {
        metros.emplace_back(PurplemetroTrain, j);
    }

    for (int k = 1; k <= 2; k++) {
        metros.emplace_back(LightgreenTrainMetro, k);
    }

    for (auto &t : metros) {
        t.join();
    }

    return 0;
}
