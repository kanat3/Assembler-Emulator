#include "texteditor.h"
#include "ui_texteditor.h"
#include <QMessageBox>

TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void TextEditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : "+file.errorString());
        return;

    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void TextEditor::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : "+file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void TextEditor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void TextEditor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void TextEditor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void TextEditor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void TextEditor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void TextEditor::on_actionRun_triggered() {
    QMessageBox result;
    freopen("output.txt", "w", stdout);
    if (currentFile == "") {
        result.setText("Nothing to run");
        result.exec();
        return;
    }
    std::string file_name = currentFile.toStdString();
    Assembler a(file_name);
    a.RunAssembler();
    QFile cons_file("output.txt");
    if ((cons_file.exists() && cons_file.open(QIODevice::ReadOnly))) {
       result.setText(cons_file.readAll());
       result.exec();
    } else {
        result.setText("Nothing to run");
        result.exec();
    }
}
