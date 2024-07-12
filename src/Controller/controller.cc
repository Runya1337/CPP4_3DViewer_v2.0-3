#include "controller.h"

namespace s21 {

    void Controller::ParseFile(std::string file_path) {
        model_->Parsing(file_path);
        error = model_->error;
    }

    void Controller::SetCentre(s21::DataModel *data) { model_->SetCentre(data); }

    DataModel &Controller::GetData() { return model_->GetData(); }

    void Controller::Affine(Strategy::SelectionStrategy select_strategy,
                        Strategy::TypeCoordinate type, DataModel *data,
                        double point) {
        model_->AffineProccess(select_strategy, type, data, point);
    }

}  // namespace s21