#ifndef METROBAKU_H
#define METROBAKU_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <fstream>  // Include for file output

extern int travel_time;
extern int stop_time;
extern int turnaround_time;
extern int train_start_delay;
extern int max_round;
extern int max_round_1;
extern int max_round_2;
extern int max_round_3;

extern std::mutex cout_mutex;

extern std::vector<std::string> Redline;
extern std::vector<std::string> Purplelin;
extern std::vector<std::string> Greenline;
extern std::vector<std::string> Lightgreenline;

void RedmetroTrain(int id, std::ofstream &outFile);
void PurplemetroTrain(int id, std::ofstream &outFile);
void GreenmetroTrain(int id, std::ofstream &outFile);
void LightgreenTrainMetro(int id, std::ofstream &outFile);

#endif
