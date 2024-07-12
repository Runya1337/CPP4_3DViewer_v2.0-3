#include "parser.h"

namespace s21 {
    Parser::Parser(std::string &file_path, DataModel *data) {
        ParseObjFile(file_path, data);
    }
    void Parser::ParseObjFile(std::string &file_path, DataModel *data) {
        std::ifstream file;
        file.open(file_path);
        error = {StatusWork::CORRECT, "ok"};
        if (file.is_open()) {
            while (std::getline(file, string_data_)) {
                if (string_data_[0] == 'v' && string_data_[1] == ' ') {
                    ParseVertex(data);
                }
                else if (string_data_[0] == 'f' && string_data_[1] == ' ') {
                    ParsePolygons(data);
                }
                if (data->GetAllVertex().empty()) data->ClearData();
            }
            file.close();
        } else {
            error = {StatusWork::INCORRECT, "Не открылся файл"};
        }
    }

    void Parser::ParseVertex(DataModel *data) {
        char symble = '\0';
        std::stringstream ss(string_data_);
        std::string x_string, y_string, z_string;
        if (ss >> symble >> x_string>> y_string >> z_string && symble == 'v' && IsDigit(x_string) && IsDigit(y_string) && IsDigit(z_string)) {
            coordinate_.x = std::stod(x_string);
            coordinate_.y = std::stod(y_string);
            coordinate_.z = std::stod(z_string);
            data->GetAllVertex().push_back(coordinate_);
        }
         else {
             //qDebug() << string_data_;
//             qDebug() << "1e-06" << (std::stod("1e-06")*2);
             error = {StatusWork::INCORRECT, "Точка считалась неккоректно"};
         }
        //printf("%c   %lf  %lf  %lf\n", symble, coordinate_.x, coordinate_.y, coordinate_.z);
    }
    void Parser::ParsePolygons(DataModel *data) {
        bool is_first = true;
        std::pair<int, int> final_pair;
        std::vector<int> vector_string;
        int num = 0;
        size_t id = 0, i = 2;
        for (; i < string_data_.length(); ++i) {
            if (string_data_[i] == '\r') continue;
            else if (std::isdigit(string_data_[i]) || string_data_[i] == '-') {
                //qDebug() << "string_data_1"  << string_data_;
                num = std::stoi(&string_data_[i], &id);
                i += id;
                NegativePolygons(&num, vector_string, data, is_first);
                if (is_first == true) {
                    final_pair.second = num;
                    is_first = false;
                }
                for (; i < string_data_.length() && string_data_[i] != ' ';
                    ++i) {
                }
                if (vector_string.size() >= 2) {
                    data->GetAllConnections().push_back({vector_string[0], vector_string[1]});
                    vector_string.erase(vector_string.begin());
                    vector_string.erase(vector_string.begin());
                }
            }
            else {
                //qDebug() << "string_data_2"  << string_data_;
                error = {StatusWork::INCORRECT, "Фигня какая-то подается а не полигон"};
            }
        final_pair.first = num;
        data->GetAllConnections().push_back(final_pair);
        }
    }

    void Parser::NegativePolygons(int *num, std::vector<int> &vector_string, DataModel *data, bool is_first) {
        if (*num > 0) {
            if (*num > (int)data->GetAllVertex().size()) {
                //qDebug() << "*num"  << *num << " GetAllVertex()" << (int)data->GetAllVertex().size();
                error = {StatusWork::INCORRECT, "При считывании полигонов, обнаружилась несуществующая точка (1)"};
            }
            else {
                *num -= 1;
            }
        } else if (*num == 0){
            error = {StatusWork::INCORRECT, "При считывании полигонов, обнаружилась несуществующая точка (2)"};
        }
        else {
            *num = data->GetAllVertex().size() - abs(*num);
        }
        if (is_first == false) {
            vector_string.push_back(*num);
            vector_string.push_back(*num);
        }
        else {
            vector_string.push_back(*num);
        }
    }
    bool Parser::IsDigit(const std::string& lex) {
        bool status = true;
        bool find_number = false;
        size_t counter_index = 0;
        int counter_dot = 0;
        if (lex[0] == '-') {
            counter_index++;
        }
        else if (!isdigit(lex[0])){
            return false;
        }
        for (; counter_index < lex.size(); counter_index++) {
            if (isdigit(lex[counter_index]) || lex[counter_index] == 'e' || lex[counter_index] == '-') {
                find_number = true;
            } else if (lex[counter_index] == '.') {
                if (!isdigit(lex[counter_index + 1])) {
                    status = false;
                }
                counter_dot++;
            } else {
                status = false;
                break;
            }
        }
        if (counter_dot > 1) {
            status = false;
        }
        if (find_number == false) {
            status = false;
        }
        return status;
    }

}
