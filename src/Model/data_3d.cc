#include "data_3d.h"



namespace s21 {
    void DataModel::ClearData() {
        all_vertex_.clear();
        connections_.clear();
    }
    std::vector<DataModel::CoordinatePoint> &DataModel::GetAllVertex() {
        return all_vertex_;
    };

    std::vector<std::pair<int, int>> &DataModel::GetAllConnections() {
        return connections_;
    };
}
