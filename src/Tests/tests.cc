#include <gtest/gtest.h>

#include "../Controller/controller.h"

class AllTest : public ::testing::Test {
    protected:
        s21::Model model_;
        s21::Controller controller_;
        static constexpr double kEpsilon_ = 1e-6;
        
        void SetUp() override { controller_ = s21::Controller(&model_); }
};

TEST_F(AllTest, CorrectCube) {
    std::string file_path = "../src/tests/obj/correct/car.obj";
    controller_.SetCentre(&controller_.GetData());
    model_.Parsing(file_path);   
    EXPECT_EQ(model_.error.first, s21::StatusWork::CORRECT);
}

TEST_F(AllTest, ParserTest) {
    std::string file_path = "../src/tests/obj/correct/kek.obj";
    s21::DataModel dataModel; 
    s21::Parser testparser(file_path, &dataModel);
    EXPECT_EQ(testparser.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, CorrectCar) {
    std::string file_path = "../src/tests/obj/correct/car.obj";
    controller_.SetCentre(&controller_.GetData());
    model_.Parsing(file_path);
    EXPECT_EQ(model_.error.first, s21::StatusWork::CORRECT);
}

TEST_F(AllTest, CorrectNegativeCube) {
    std::string file_path = "../src/tests/obj/correct/cube_neg.obj";
    controller_.SetCentre(&controller_.GetData());
    model_.Parsing(file_path);   
    EXPECT_EQ(model_.error.first, s21::StatusWork::CORRECT);
    EXPECT_EQ(model_.error.second, "ok");
}

TEST_F(AllTest, IncorrectFileName) {
    std::string file_path = "../src/tests/obj/correct/lalalalalalal.obj";
    controller_.SetCentre(&controller_.GetData());
    model_.Parsing(file_path);   
    EXPECT_EQ(model_.error.second, "Не открылся файл");
}

TEST_F(AllTest, IncorrectFileExtention) {
    std::string file_path = "../src/tests/obj/correct/cube.org";
    controller_.SetCentre(&controller_.GetData());
    model_.Parsing(file_path);
    EXPECT_EQ(model_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, IncorrectFilePath) {
    std::string file_path = "../src/tests/obj/cor/cube.org";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, EmptyFilePath) {
    std::string file_path;
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}


TEST_F(AllTest, dot_error) {
    std::string file_path = "../src/tests/obj/incorrect/dot_error.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, facet_that_less_than_1) {
    std::string file_path =
        "../src/tests/obj/incorrect/first_minus.obj";
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, incorrect_notation) {
    std::string file_path =
        "../src/tests/obj/incorrect/incorrect_notation.obj";
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, first_minus) {
    std::string file_path = "../src/tests/obj/incorrect/facet_that_not_exist.obj";
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, facet_that_not_exist) {
    std::string file_path = "../src/tests/obj/incorrect/facet_that_less_than_1.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, incorrect_number) {
    std::string file_path = "../src/tests/obj/incorrect/incorrect_number.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, invalid_pretoken) {
    std::string file_path = "../src/tests/obj/incorrect/invalid_pretoken.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}
/////////////////////////////

TEST_F(AllTest, invalid_token) {
    std::string file_path = "../src/tests/obj/incorrect/invalid_token.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, more_than_1_dot_in_number) {
    std::string file_path =
        "../src/tests/obj/incorrect/more_than_1_dot_in_number.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, stash) {
    std::string file_path = "../src/tests/obj/incorrect/stash.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, stash_in_line) {
    std::string file_path = "../src/tests/obj/incorrect/stash_in_line.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, test_with_russian_symb) {
    std::string file_path =
        "../src/tests/obj/incorrect/test_with_russian_symb.obj";
    controller_.SetCentre(&controller_.GetData());
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}


TEST_F(AllTest, vertex_less_than_3) {
    std::string file_path = "../src/tests/obj/incorrect/vertex_less_than_3.obj";
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}

TEST_F(AllTest, zero_vertex) {
    std::string file_path = "../src/tests/obj/incorrect/zero_vertex.obj";
    controller_.ParseFile(file_path);
    EXPECT_EQ(controller_.error.first, s21::StatusWork::INCORRECT);
}


TEST_F(AllTest, MovePlusX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";

  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].x + 3, model_after[i].x);
  }
}

TEST_F(AllTest, MoveMinusX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";

  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].x - 3, model_after[i].x);
  }
}

TEST_F(AllTest, MovePlusY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].y + 3, model_after[i].y);
  }
}

TEST_F(AllTest, MoveMinusY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].y - 3, model_after[i].y);
  }
}

TEST_F(AllTest, MovePlusZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].z + 3, model_after[i].z);
  }
}

TEST_F(AllTest, MoveMinusZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].z - 3, model_after[i].z);
  }
}

TEST_F(AllTest, RotateX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, -model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, -model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, RotateY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, -model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, -model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, RotateZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, -model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, -model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SummaryXYZMirrorRotateTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     30);

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     -30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -30);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SummaryXRotateTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     30);

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -30);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, PlusSizeTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kDistance,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     1.1);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x * 1.1, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y * 1.1, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z * 1.1, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, MinusSizeTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.Parsing(file_path);

  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kDistance,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     0.9);

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x * 0.9, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y * 0.9, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z * 0.9, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SetCenterTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     20);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SetCenterAfterMovingZYTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SetCenterAfterMovingTest) {
  std::string file_path = "../src/tests/obj/correct/bison_pose.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(AllTest, SetCenterAfterZMovingTest) {
  std::string file_path = "../src/tests/obj/correct/katana.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetAllVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetAllVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}