#include "LearningWindow.h"
#include "ui_LearningWindow.h"
#include "Card.h"
#include "CoursesManager.h"

LearningWindow::LearningWindow(CoursesManager &cManager, QString courseName, QFont font, QWidget *parent)
    : QDialog(parent)
    , ui_(new Ui::LearningWindow)
{
    coursesManager_ = &cManager;
    if(courseName.isEmpty())
        course_ = coursesManager_->createCourse();
    else
        course_ = coursesManager_->createCourse(courseName);
    this->font_ = font;
    setDefaultValues();
}

LearningWindow::LearningWindow(CoursesManager &cManager, int numberOfSelectedCourse, QFont font, QWidget *parent)
    : QDialog(parent)
    , ui_(new Ui::LearningWindow)
{
    coursesManager_ = &cManager;
    this->font_ = font;
    setDefaultValues();
    course_ = coursesManager_->getCourse(numberOfSelectedCourse);
    course_->checkCards();
    updateProgressBar();
    updateStatusLabel();
    if (course_->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

LearningWindow::~LearningWindow() {
    delete ui_;
}

void LearningWindow::on_showAnswerButton_clicked() {
    ui_->showAnswerButton->setEnabled(false);
    ui_->answerTextBrowser->setText(card_->getAnswer());
    ui_->yesButton->setEnabled(true);
    ui_->noButton->setEnabled(true);
    ui_->almostButton->setEnabled(true);
    ui_->deleteButton->setEnabled(false);
}

void LearningWindow::on_newQuestionAdded(QString question, QString answer, QPixmap image, QString soundPath) {
    Card *newCard = new Card(question, answer, image, soundPath, QDate::currentDate());
    course_->addCardToRepeat(newCard);
    course_->incrementCardsCounter();
    updateProgressBar();
    updateStatusLabel();
    if (course_->getSizeCardsToRepeat() == 1)
        emit questionAvailable();
}
void LearningWindow::setDefaultImage() {
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui_->verticalLayout_4->geometry();
    ui_->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

void LearningWindow::setDefaultValues() {
    ui_->setupUi(this);
    ui_->showAnswerButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    ui_->stopButton->setEnabled(false);
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    ui_->deleteButton->setEnabled(false);
    connect(this, &LearningWindow::questionAvailable, this, &LearningWindow::on_startLearning);
    checkImage();
    QPixmap img1(":/images/Icons/smile.png");
    QPixmap img2(":/images/Icons/neutral.png");
    QPixmap img3(":/images/Icons/sad.png");
    ui_->yesButton->setIcon(img1);
    ui_->almostButton->setIcon(img2);
    ui_->noButton->setIcon(img3);
    QSize iconSize(ui_->noButton->height(),ui_->noButton->height());
    ui_->yesButton->setIconSize(iconSize);
    ui_->almostButton->setIconSize(iconSize);
    ui_->noButton->setIconSize(iconSize);
    ui_->answerTextBrowser->setFont(font_);
    ui_->questionTextBrowser->setFont(font_);
}

void LearningWindow::setImage(QPixmap image) {
    QRect rect = ui_->verticalLayout_4->geometry();
    ui_->imageLabel->setPixmap(image.scaled(rect.height(), rect.height()));
}

void LearningWindow::updateProgressBar() {
    if(course_->getCardsCounter() > 0 && course_->getCardsCounter() == course_->getSizeCardsRepeated())
         ui_->progressBar->setValue(100);
    else if (course_->getCardsCounter() > 0) {
        int val = 100 - course_->getSizeCardsToRepeat() * 100 / course_->getCardsCounter();
        ui_->progressBar->setValue(val);
    }
    else
        ui_->progressBar->setValue(0);
}

void LearningWindow::updateStatusLabel() {
    if(course_->getCardsCounter() == course_->getSizeCardsRepeated() && course_->getCardsCounter() != 0) {
        ui_->statusLabel->setText("Gratulacje, ukończyłeś cały kurs :)");
        QPixmap img(":/images/congratulations.png");
        setImage(img);
    }
    else
        ui_->statusLabel->setText(QString("Wszystkie pytania: " + QString::number(course_->getCardsCounter()) + " Jeszcze nie zapamiętane: " + QString::number(course_->getSizeCardsToRepeat()) +
                                         " Już zapamiętane: " + QString::number(course_->getSizeCardsRepeated())));
}

void LearningWindow::on_startLearning() {
    card_ = course_->getFirstCardToRepeat();
    ui_->showAnswerButton->setEnabled(true);
    ui_->questionTextBrowser->setText(card_->getQuestion());
    ui_->deleteButton->setEnabled(true);
    if(!card_->getImage().isNull())
        setImage(card_->getImage());
    else
        setDefaultImage();
    if(!card_->getSoundPath().isEmpty())
        ui_->playButton->setEnabled(true);
}

void LearningWindow::on_yesButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(5));
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    if(card_->getSoundPath().length() != 0)
        sound_->stop();
    ui_->stopButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    course_->removeFirstCardToRepeat();
    course_->addCardRepeated(card_);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui_->questionTextBrowser->clear();
    ui_->answerTextBrowser->clear();
    if (course_->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_noButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(2));
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    if(card_->getSoundPath().length() != 0)
        sound_->stop();
    ui_->stopButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    course_->removeFirstCardToRepeat();
    course_->addCardToRepeat(card_);
    setDefaultImage();
    ui_->questionTextBrowser->clear();
    ui_->answerTextBrowser->clear();
    emit questionAvailable();
}

void LearningWindow::on_almostButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(3));
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    if(card_->getSoundPath().length() != 0)
        sound_->stop();
    ui_->stopButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    course_->removeFirstCardToRepeat();
    course_->addCardRepeated(card_);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui_->questionTextBrowser->clear();
    ui_->answerTextBrowser->clear();
    if (course_->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_playButton_clicked() {
    sound_ = new QSound(card_->getSoundPath());
    sound_->setLoops(1000);
    sound_->play();
    ui_->playButton->setEnabled(false);
    ui_->stopButton->setEnabled(true);
}

void LearningWindow::on_stopButton_clicked() {
    sound_->stop();
    ui_->stopButton->setEnabled(false);
    ui_->playButton->setEnabled(true);
}

void LearningWindow::on_newQuestionButton_clicked() {
    NewQuestion dialog(this);
    dialog.setWindowTitle("Dodaj nowe pytanie");
    if(dialog.exec() ) {
        on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }
}

void LearningWindow::on_deleteButton_clicked() {
    QMessageBox msg;
    msg.setText("Jesteś pewny że chcesz usunąć to pytanie?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes) {
        if(card_->getSoundPath().length() != 0)
            sound_->stop();
        course_->removeFirstCardToRepeat();
        course_->decrementCardsCounter();
        ui_->showAnswerButton->setEnabled(false);
        ui_->playButton->setEnabled(false);
        ui_->stopButton->setEnabled(false);
        setDefaultImage();
        updateProgressBar();
        updateStatusLabel();
        ui_->questionTextBrowser->clear();
        ui_->answerTextBrowser->clear();
        if (course_->getSizeCardsToRepeat() >= 1)
            emit questionAvailable();
    }
}

void LearningWindow::on_endButton_clicked() {
    accept();
}
void LearningWindow::checkImage() {
//    if(course->getSizeCardsToRepeat() >= 1)
//    {
//        if(!course->getFirstCardToRepeat()->image().isNull())
//        {
//            setImage(course->getFirstCardToRepeat()->image());
//            return;
//        }
//    }
//    setDefaultImage();
}

bool LearningWindow::isEqualToCurrentDate(QDate date) {
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}


