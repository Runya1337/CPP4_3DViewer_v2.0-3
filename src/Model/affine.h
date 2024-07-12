#ifndef CPP4_3DVIEWER_V2_MODEL_AFFINE_H
#define CPP4_3DVIEWER_V2_MODEL_AFFINE_H

#include <cmath>

#include "data_3d.h"

namespace s21 {
class Strategy {
 public:
  enum class TypeCoordinate { kX, kY, kZ };
  enum class SelectionStrategy { kMove, kRotate, kDistance };

  Strategy() = default;
  virtual ~Strategy() = default;

  virtual void Transformations(DataModel *data, double point,
                               TypeCoordinate coordinate_x_y_z) = 0;
};
class AffineTransformations {
 public:
  AffineTransformations() = default;
  ~AffineTransformations() = default;

  void SetStrategy(Strategy *concrete_strategy);
  void Transformations(DataModel *data, double point,
                       Strategy::TypeCoordinate coordinate_x_y_z);

 private:
  Strategy *strategy_;
};
class RotateObj : public Strategy {
  void Transformations(DataModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
  void Rotate(DataModel *data, double point,
              void (RotateObj::*SomeMethod)(DataModel::CoordinatePoint &,
                                            double));
  void RotateX(DataModel::CoordinatePoint &i, double point);
  void RotateY(DataModel::CoordinatePoint &i, double point);
  void RotateZ(DataModel::CoordinatePoint &i, double point);
};
class MoveObj : public Strategy {
  void Transformations(DataModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
};
class DistanceObj : public Strategy {
  void Transformations(s21::DataModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
};

}  // namespace s21

#endif