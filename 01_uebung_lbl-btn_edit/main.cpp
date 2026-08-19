#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QButtonGroup>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget window;
    window.setWindowTitle("Qt6 Übung Labels & Buttons");
    window.resize(600, 150);

    // Main layout is a horizontal row
    auto *mainLayout = new QHBoxLayout(&window);

    // Elements
    auto *label1 = new QLabel("Label 1", &window);
    auto *label2 = new QLabel("Label 2", &window);

    auto *selectBtn1 = new QPushButton("Select 1", &window);
    auto *selectBtn2 = new QPushButton("Select 2", &window);
    selectBtn1->setCheckable(true);
    selectBtn1->setMaximumWidth(100);
    selectBtn2->setCheckable(true);
    selectBtn2->setMaximumWidth(100);

    auto *buttonGroup = new QButtonGroup(&window);
    buttonGroup->addButton(selectBtn1);
    buttonGroup->addButton(selectBtn2);
    buttonGroup->setExclusive(true);

    auto *lineEdit = new QLineEdit(&window);
    auto *saveBtn = new QPushButton("Speichern", &window);
    lineEdit->setPlaceholderText("Text eingeben...");
    lineEdit->setMaximumWidth(100);
    saveBtn->setMaximumWidth(100);

    // Group 1: Label1 + Button
    auto *group1 = new QVBoxLayout();
    group1->addWidget(label1);
    group1->addWidget(selectBtn1);

    // Group 2: Label2 + Button
    auto *group2 = new QVBoxLayout();
    group2->addWidget(label2);
    group2->addWidget(selectBtn2);

    // Group 3: Input + Button
    auto *group3 = new QVBoxLayout();
    group3->addWidget(lineEdit);
    group3->addWidget(saveBtn);

    // Assemble main horizontal layout
    mainLayout->addLayout(group1);
    mainLayout->addLayout(group2);
    mainLayout->addLayout(group3);

    QObject::connect(saveBtn, &QPushButton::clicked, [lineEdit, label1, label2, selectBtn1, selectBtn2, &window]() {
        QLabel* activeLabel = nullptr;
        if (selectBtn1->isChecked()) {
            activeLabel = label1;
        } else if (selectBtn2->isChecked()) {
            activeLabel = label2;
        }

        if (!activeLabel) {
            QMessageBox::warning(&window, "Fehler", "Bitte erst ein Label auswählen!");
            return;
        }

        activeLabel->setText(lineEdit->text());
        lineEdit->clear();
    });

    window.show();
    return QApplication::exec();
}
