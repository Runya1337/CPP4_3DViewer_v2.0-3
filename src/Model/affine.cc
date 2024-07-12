#include "affine.h"

namespace s21 {
    void AffineTransformations::SetStrategy(Strategy *concrete_strategy) {
        strategy_ = concrete_strategy;
    };
    void AffineTransformations::Transformations(DataModel *data, double point, Strategy::TypeCoordinate coordinate_x_y_z) {
        strategy_->Transformations(data, point, coordinate_x_y_z);
    };
    void MoveObj::Transformations(DataModel *data, double point, TypeCoordinate coordinate_x_y_z) {
        for (auto &i : data->GetAllVertex()) {
            if (coordinate_x_y_z == TypeCoordinate::kX) i.x += point;
            if (coordinate_x_y_z == TypeCoordinate::kY) i.y += point;
            if (coordinate_x_y_z == TypeCoordinate::kZ) i.z += point;
        }
    }
    void RotateObj::Transformations(DataModel *data, double point,
                                Strategy::TypeCoordinate coordinate_x_y_z) {
        switch (coordinate_x_y_z) {
            case Strategy::TypeCoordinate::kX:
                Rotate(data, point, &RotateObj::RotateX);
                break;
            case Strategy::TypeCoordinate::kY:
                Rotate(data, point, &RotateObj::RotateY);
                break;
            case Strategy::TypeCoordinate::kZ:
                Rotate(data, point, &RotateObj::RotateZ);
                break;
        }
    }
    void RotateObj::Rotate(DataModel *data, double point,
                       void (RotateObj::*SomeMethod)(DataModel::CoordinatePoint &,
                                                     double)) {
        point *= M_PI / 180;
        for (auto &i : data->GetAllVertex()) {
            (this->*SomeMethod)(i, point);
        }
    }
    void RotateObj::RotateX(DataModel::CoordinatePoint &i, double point) {
        double tmp_y = i.y;
        double tmp_z = i.z;
        i.y = tmp_y * cos(point) + tmp_z * sin(point);
        i.z = -tmp_y * sin(point) + tmp_z * cos(point);
    }
    void RotateObj::RotateY(DataModel::CoordinatePoint &i, double point) {
        double tmp_x = i.x;
        double tmp_z = i.z;
        i.x = tmp_x * cos(point) + tmp_z * sin(point);
        i.z = -tmp_x * sin(point) + tmp_z * cos(point);
    }

    void RotateObj::RotateZ(DataModel::CoordinatePoint &i, double point) {
        double tmp_x = i.x;
        double tmp_y = i.y;
        i.x = tmp_x * cos(point) + tmp_y * sin(point);
        i.y = -tmp_x * sin(point) + tmp_y * cos(point);
    }
    void DistanceObj::Transformations(
        s21::DataModel *data, double point,
        s21::Strategy::TypeCoordinate coordinate_x_y_z) {
        if (coordinate_x_y_z == Strategy::TypeCoordinate::kZ) {
            for (auto &i : data->GetAllVertex()) {
                i.x *= point;
                i.y *= point;
                i.z *= point;
            }
        }
    }
}