#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(s21::Controller* controller, QWidget* parent)
    : QMainWindow(parent , Qt::FramelessWindowHint),
    ui(new Ui::Viewer), controller_(controller)
{
  ui->setupUi(this);
  setFixedSize(size());
  ui->GLwidget->setControll(controller);
  connect(&gifTimer_, SIGNAL(timeout()), this, SLOT(CreatGif()));
  loadSettings();
}

Viewer::~Viewer() {
  saveSettings();
  delete ui;
}

void Viewer::clear() {
  ui->GLwidget->moveX_ = 0;
  ui->GLwidget->moveY_ = 0;
  ui->GLwidget->moveZ_ = 0;
  ui->GLwidget->rotationX_ = 0;
  ui->GLwidget->rotationY_ = 0.4;
  ui->GLwidget->rotationZ_ = 0;
  ui->GLwidget->size_ = 1;
}

void Viewer::on_chooseBackColor_clicked() {
  ui->GLwidget->colorWidget = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_chooseLineColor_clicked() {
  ui->GLwidget->colorLines = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_choosePointColor_clicked() {
  ui->GLwidget->colorVertices = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_buttonMoveX1_clicked() {
  double num = ui->GLwidget->moveX_ - 0.1;
  ui->GLwidget->moveX_ = num;
}

void Viewer::on_buttonMoveX2_clicked() {
  double num = ui->GLwidget->moveX_ + 0.1;
  ui->GLwidget->moveX_ = num;
}

void Viewer::on_buttonMoveY1_clicked() {
  double num = ui->GLwidget->moveY_ - 0.1;
  ui->GLwidget->moveY_ = num;
}

void Viewer::on_buttonMoveY2_clicked() {
  double num = ui->GLwidget->moveY_ + 0.1;
  ui->GLwidget->moveY_ = num;
}

void Viewer::on_buttonMoveZ1_clicked() {
  double num = ui->GLwidget->moveZ_ - 0.1;
  ui->GLwidget->moveZ_ = num;
}

void Viewer::on_buttonMoveZ2_clicked() {
  double num = ui->GLwidget->moveZ_ + 0.1;
  ui->GLwidget->moveZ_ = num;
}

void Viewer::on_buttonRotX1_clicked() {
  double num = ui->GLwidget->rotationX_ - 0.1;
  ui->GLwidget->rotationX_ = num;
}

void Viewer::on_buttonRotX2_clicked() {
  double num = ui->GLwidget->rotationX_ + 0.1;
  ui->GLwidget->rotationX_ = num;
}

void Viewer::on_buttonRotY1_clicked() {
  double num = ui->GLwidget->rotationY_ - 0.1;
  ui->GLwidget->rotationY_ = num;
}

void Viewer::on_buttonRotY2_clicked() {
  double num = ui->GLwidget->rotationY_ + 0.1;
  ui->GLwidget->rotationY_ = num;
}

void Viewer::on_buttonRotZ1_clicked() {
  double num = ui->GLwidget->rotationZ_ - 0.1;
  ui->GLwidget->rotationZ_ = num;
}

void Viewer::on_buttonRotZ2_clicked() {
  double num = ui->GLwidget->rotationZ_ + 0.1;
  ui->GLwidget->rotationZ_ = num;
}

void Viewer::on_buttonSizeMin_clicked() {
  double num = ui->GLwidget->size_ - 0.1;
  if (num > 0) {
    ui->GLwidget->size_ = num;
  }
}

void Viewer::on_buttonSizeMax_clicked() {
  double num = ui->GLwidget->size_ + 0.1;
  ui->GLwidget->size_ = num;
}

void Viewer::on_radioButtonCentrall_clicked() { ui->GLwidget->typeProect = 1; }

void Viewer::on_radioButtonParallel_clicked() { ui->GLwidget->typeProect = 2; }

void Viewer::on_radioButtonNoPoint_clicked() { ui->GLwidget->typeP = 1; }

void Viewer::on_radioButtonSquare_clicked() { ui->GLwidget->typeP = 2; }

void Viewer::on_radioButtonRound_clicked() { ui->GLwidget->typeP = 3; }

void Viewer::on_radioButtonNoLine_clicked() { ui->GLwidget->typeL = 1; }

void Viewer::on_radioButtonDotted_clicked() { ui->GLwidget->typeL = 2; }

void Viewer::on_radioButtonSolid_clicked() { ui->GLwidget->typeL = 3; }

void Viewer::on_buttonLineSize1_clicked() {
  double num = ui->sizeLine->text().toDouble() - 1;
  if (num > 0) {
    ui->sizeLine->setText(QString::number(num));
    ui->GLwidget->sizeL_ = num;
  }
}

void Viewer::on_buttonLineSize2_clicked() {
  double num = ui->sizeLine->text().toDouble() + 1;
  ui->sizeLine->setText(QString::number(num));
  ui->GLwidget->sizeL_ = num;
}

void Viewer::on_buttonPointSize1_clicked() {
  double num = ui->sizePoint->text().toDouble() - 1;
  if (num > 0) {
    ui->sizePoint->setText(QString::number(num));
    ui->GLwidget->sizeP_ = num;
  }
}

void Viewer::on_buttonPointSize2_clicked() {
  double num = ui->sizePoint->text().toDouble() + 1;
  ui->sizePoint->setText(QString::number(num));
  ui->GLwidget->sizeP_ = num;
}

void Viewer::ShowMessage(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(700, 300);
  messageBox.information(0, "Информация!", message);
}

void Viewer::on_buttonGif_clicked() {
  if (controller_->GetData().GetAllVertex().size() != 0) {
    gifFile_ = QFileDialog::getSaveFileName(this,tr("Save GIF"),"gif",tr("Gif Files (*.gif)"));
    if (!gifFile_.isEmpty()) {
      ui->buttonGif->setDisabled(true);
      gifImage_ = new QGifImage;
      gifImage_->setDefaultDelay(100);
      gifTimer_.setInterval(100);
      gifTimer_.start();
    }
  } else ShowMessage("Модель не выбрана!");
}

void Viewer::CreatGif() {
  if (!startTime_.isValid()) startTime_ = QTime::currentTime();

  QImage image_ = ui->GLwidget->grabFramebuffer();
  gifImage_->addFrame(image_);
  if (startTime_.msecsTo(QTime::currentTime()) >= 5000) {
    gifTimer_.stop();
    gifImage_->save(gifFile_);
    ShowMessage("Гифка сохранена");
    delete gifImage_;
    ui->buttonGif->setEnabled(true);
  }
  ui->buttonGif->setText("GIF");
}

void Viewer::on_buttonSnapshot_clicked() {
  if (controller_->GetData().GetAllVertex().size() != 0) {
    QFileDialog dialog_photo(this);
    QString picture_name = dialog_photo.getSaveFileName(
        this, "Save as ...", QDir::currentPath(), "*.bmp;; *.jpeg");
    ui->GLwidget->grabFramebuffer().save(picture_name);
  } else ShowMessage("Модель не выбрана.");
}

void Viewer::saveSettings() {
  QSettings settings("School21", "Viewer_v2");
  settings.setValue("colorWidget", ui->GLwidget->colorWidget);
  settings.setValue("colorLines", ui->GLwidget->colorLines);
  settings.setValue("colorVertices", ui->GLwidget->colorVertices);
  settings.setValue("typeProect", ui->GLwidget->typeProect);
  settings.setValue("typeP", ui->GLwidget->typeP);
  settings.setValue("typeL", ui->GLwidget->typeL);
  settings.sync();
}

void Viewer::loadSettings() {
  QSettings settings("School21", "Viewer_v2");
  ui->GLwidget->colorWidget = settings.value("colorWidget", QColor(Qt::gray)/*QColor(0.949035, 0.948959, 0.952941)*//*QColor('#f2f2f3')*/).value<QColor>();
  ui->GLwidget->colorLines = settings.value("colorLines", QColor(Qt::black)).value<QColor>();
  ui->GLwidget->colorVertices = settings.value("colorVertices", QColor(Qt::red)).value<QColor>();

  ui->GLwidget->typeProect = settings.value("typeProect", 1).toInt();
  if (ui->GLwidget->typeProect == 1) ui->radioButtonCentrall->setChecked(true);
  else if (ui->GLwidget->typeProect == 2) ui->radioButtonParallel->setChecked(true);

  ui->GLwidget->typeP = settings.value("typeP", 3).toInt();
  if (ui->GLwidget->typeP == 1) ui->radioButtonNoPoint->setChecked(true);
  else if (ui->GLwidget->typeP == 2) ui->radioButtonSquare->setChecked(true);
  else if (ui->GLwidget->typeP == 3) ui->radioButtonRound->setChecked(true);

  ui->GLwidget->typeL = settings.value("typeL", 3).toInt();
  if (ui->GLwidget->typeL == 1) ui->radioButtonNoLine->setChecked(true);
  else if (ui->GLwidget->typeL == 2) ui->radioButtonDotted->setChecked(true);
  else if (ui->GLwidget->typeL == 3) ui->radioButtonSolid->setChecked(true);
}


void Viewer::on_open_clicked() {
    file_ = QFileDialog::getOpenFileName(this, "Выбрать файл", "", "OBJ (*.obj)");
    if (file_ != "") {
      clear();
      ui->GLwidget->setFileName(file_);
      if (controller_->error.second == "ok") {
          ui->plainTextEdit->setPlainText(QString("  Файл: %1\n  Вершины: %2, Линии: %3").arg(QFileInfo(file_).fileName()).arg(QString::number(controller_->GetData().GetAllVertex().size())).arg(QString::number(controller_->GetData().GetAllConnections().size())));
          if ((controller_->GetData().GetAllVertex().size() == 0)) {
            ShowMessage("Неправильная модель!");
          }
      } else {
          ShowMessage(controller_->error.second.c_str());
          ui->plainTextEdit->setPlainText(QString(" "));
      }
    }
}

void Viewer::on_quit_clicked() {
    this->close();
}

void Viewer::on_save_clicked() {
    ShowMessage("Данная функция недоступна в бесплатной версии программы!");
}

