#ifndef CPP4_3DVIEWER_V2_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_MODEL_MODEL_H

#include "affine.h"
#include "data_3d.h"
#include "parser.h"
#include "set_centre.h"

namespace s21 {
class Model {
 public:
  std::pair<StatusWork, std::string> error = {StatusWork::CORRECT, "ok"};
  Model();
  ~Model();
  DataModel &GetData();
  void Parsing(std::string &file_path);
  void AffineProccess(Strategy::SelectionStrategy current_strategy,
                      Strategy::TypeCoordinate xyz, DataModel *data,
                      double step);
  void GiveCommand(DataModel *data, Event *event, Event::Command command);
  void SetCentre(DataModel *data);

 private:
  DataModel data_;
  Parser parse_;
  AffineTransformations affine_;
  Strategy *move_obj_;
  Strategy *rotate_obj_;
  Strategy *distance_obj_;
  FindMinMax *find_min_max_;
  FindMax *find_max_;
  FindCentre *find_centre_;
};
}  // namespace s21

#endif