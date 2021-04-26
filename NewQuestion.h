#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>

namespace Ui {
class NewQuestion;
}

class NewQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuestion(QWidget *parent = nullptr);
    ~NewQuestion();

private:
    Ui::NewQuestion *ui;
};

#endif // NEWQUESTION_H
