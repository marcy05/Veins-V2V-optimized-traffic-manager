#ifndef RUNTEST_H
#define RUNTEST_H

#include <vector>
#include <map>
#include "Car.h"
#include "xmlReader/readingXML.h"
#include "Optimizer.h"

std::vector<std::vector<Car>> runOptimization(std::vector<int> Evehicles, std::vector<int> Esignals,
                                  std::vector<int> Nvehicles, std::vector<int> Nsignals,
                                  std::vector<int> Wvehicles, std::vector<int> Wsignals,
                                  std::vector<int> Svehicles, std::vector<int> Ssignals,
                                  std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset);





#endif // !RUNTEST_H
