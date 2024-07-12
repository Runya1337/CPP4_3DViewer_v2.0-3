#ifndef CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H
#define CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H
#include <iostream>
#include <utility>
#include <vector>

namespace s21 {
class DataModel {
 public:
  DataModel() = default;
  ~DataModel() = default;
  struct CoordinatePoint {
    CoordinatePoint() : x(0), y(0), z(0) {}
    double x, y, z;
  };
  std::vector<CoordinatePoint> &GetAllVertex();
  std::vector<std::pair<int, int>> &GetAllConnections();
  void ClearData();
  void PrintAllVertex();
  void PrintAllConnection();

 private:
  std::vector<CoordinatePoint> all_vertex_;
  std::vector<std::pair<int, int>> connections_;
};

}  // namespace s21

#endif