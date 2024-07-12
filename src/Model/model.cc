#include "model.h"


namespace s21 {
    Model::Model() {
        move_obj_ = new MoveObj();
        rotate_obj_ = new RotateObj();
        distance_obj_ = new DistanceObj();

        find_min_max_ = new FindMinMax();
        find_max_ = new FindMax();
        find_centre_ = new FindCentre();
    }
    Model::~Model() {
        delete move_obj_;
        delete rotate_obj_;
        delete distance_obj_;

        delete find_min_max_;
        delete find_max_;
        delete find_centre_;
    }
    void Model::Parsing(std::string &file_path) {
        parse_.ParseObjFile(file_path, &data_);
        error = parse_.error;
        
    }
    void Model::AffineProccess(Strategy::SelectionStrategy current_strategy,
                                Strategy::TypeCoordinate xyz, DataModel *data,
                                double step) {
        switch (current_strategy) {
            case Strategy::SelectionStrategy::kMove:
                affine_.SetStrategy(move_obj_);
                break;
            case Strategy::SelectionStrategy::kRotate:
                affine_.SetStrategy(rotate_obj_);
                break;
            case Strategy::SelectionStrategy::kDistance:
                affine_.SetStrategy(distance_obj_);
                break;
        }

        affine_.Transformations(data, step, xyz);
    }

    void Model::GiveCommand(DataModel *data, Event *event,
                        Event::Command command) {
        Event::VerifyExecution verify = event->Execute(data, command);

        if (verify == Event::VerifyExecution::kNotExecution) return;
    }
    void Model::SetCentre(DataModel *data) {
        if (data->GetAllVertex().empty()) return;
        find_min_max_->SetNextEvent(find_max_)->SetNextEvent(find_centre_);

        find_min_max_->centre_ = Event::MinMax();
        find_min_max_->min_ = Event::MinMax();
        find_min_max_->max_ = Event::MinMax();
        find_min_max_->scale_for_centre_ = 0;
        GiveCommand(data, find_min_max_, Event::Command::kFindMinMax);
        find_max_->Update(find_min_max_);
        GiveCommand(data, find_max_, Event::Command::kFindMax);
        find_centre_->Update(find_max_);
        GiveCommand(data, find_centre_, Event::Command::kFindCentre);
    }

    DataModel &Model::GetData() { return data_; }
}