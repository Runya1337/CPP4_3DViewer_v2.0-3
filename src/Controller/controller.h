
#ifndef CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H

#include "../Model/model.h"

namespace s21 {

class Controller {
 public:
  std::pair<StatusWork, std::string> error = {StatusWork::CORRECT, "ok"};
  Controller() {}
  Controller(Model *m) : model_(m) {}

  void Affine(Strategy::SelectionStrategy select_strategy,
              Strategy::TypeCoordinate type, DataModel *data, double point);
  void ParseFile(std::string file_path);
  DataModel &GetData();
  void SetCentre(DataModel *data);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H