#ifndef CPP4_3DVIEWER_V2_MODEL_PARSEOBJ_H
#define CPP4_3DVIEWER_V2_MODEL_PARSEOBJ_H

#include <fstream>
#include <sstream>

#include "data_3d.h"

namespace s21 {
enum class StatusWork { CORRECT, INCORRECT };
class Parser {
 public:
  std::pair<StatusWork, std::string> error = {StatusWork::CORRECT, "ok"};
  Parser(std::string &file_path, DataModel *data);
  Parser() = default;
  ~Parser() = default;
  void ParseObjFile(std::string &file_path, DataModel *data);
  void NegativePolygons(int *num, std::vector<int> &vector_string,
                        DataModel *data, bool is_first);
  void ParseVertex(DataModel *data);
  void ParsePolygons(DataModel *data);
  bool IsDigit(const std::string &lex);

 private:
  std::string string_data_;
  DataModel::CoordinatePoint coordinate_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_PARSEOBJ_H