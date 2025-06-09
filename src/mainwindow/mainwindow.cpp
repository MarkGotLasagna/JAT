#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Set the window title
    setWindowTitle("Welcome tour - JAT");
    
    // Connect the close button to our slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    
    // Connect the next button to our slot
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::onNextButtonClicked);
    
    // Connect the checkbox to our slot
    connect(ui->checkBoxDontShow, &QCheckBox::clicked, this, &MainWindow::onCheckBoxDontShowClicked);
}

MainWindow::~MainWindow()
{
    if (m_rainbowTimer) {
        m_rainbowTimer->stop();
        delete m_rainbowTimer;
    }
    delete ui;
}

void MainWindow::onCloseButtonClicked()
{
    close();
}

void MainWindow::onNextButtonClicked()
{
    std::string nextText = "Great! Let's get started with your job application tracking.\n\n"
                          "Here's what you can do next:\n\n"
                          "1. Add a new job application\n"
                          "2. View your existing applications\n"
                          "3. Update application status\n"
                          "4. Set reminders for follow-ups\n\n"
                          "Choose an option to continue...";
    
    updateWelcomeLabel(nextText);
}

void MainWindow::onCheckBoxDontShowClicked()
{
    m_checkBoxClickCount++;
    
    if (m_checkBoxClickCount >= 5 && !m_rainbowTimer) {
        startRainbowEffect();
    }
}

void MainWindow::startRainbowEffect()
{
    if (!m_rainbowTimer) {
        m_rainbowTimer = new QTimer(this);
        connect(m_rainbowTimer, &QTimer::timeout, this, &MainWindow::updateRainbowEffect);
        m_rainbowTimer->start(50); // Update every 50ms for smooth animation
    }
}

void MainWindow::stopRainbowEffect()
{
    if (m_rainbowTimer) {
        m_rainbowTimer->stop();
        delete m_rainbowTimer;
        m_rainbowTimer = nullptr;
    }
    
    // Reset all widgets to their default style
    qApp->setStyleSheet("");
}

void MainWindow::updateRainbowEffect()
{
    m_rainbowHue = fmod(m_rainbowHue + 0.01f, 1.0f);
    qApp->setStyleSheet(getRainbowStyleSheet(m_rainbowHue));
}

QString MainWindow::getRainbowStyleSheet(float hue)
{
    // Convert HSL to RGB for the current hue
    float h = hue;
    float s = 0.8f;
    float l = 0.5f;
    
    float c = (1 - fabs(2 * l - 1)) * s;
    float x = c * (1 - fabs(fmod(h * 6, 2) - 1));
    float m = l - c/2;
    
    float r, g, b;
    if (h < 1.0f/6.0f) { r = c; g = x; b = 0; }
    else if (h < 2.0f/6.0f) { r = x; g = c; b = 0; }
    else if (h < 3.0f/6.0f) { r = 0; g = c; b = x; }
    else if (h < 4.0f/6.0f) { r = 0; g = x; b = c; }
    else if (h < 5.0f/6.0f) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }
    
    r = (r + m) * 255;
    g = (g + m) * 255;
    b = (b + m) * 255;
    
    // Create a gradient style sheet that only affects buttons
    return QString(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 rgb(%1, %2, %3),"
        "       stop:1 rgb(%4, %5, %6));"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 rgb(%7, %8, %9),"
        "       stop:1 rgb(%10, %11, %12));"
        "   border: none;"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 rgb(%13, %14, %15),"
        "       stop:1 rgb(%16, %17, %18));"
        "   border: none;"
        "}"
    ).arg(r).arg(g).arg(b)
     .arg(b).arg(r).arg(g)
     .arg(g).arg(b).arg(r)
     .arg(r).arg(g).arg(b)
     .arg(b).arg(r).arg(g)
     .arg(g).arg(b).arg(r)
     .arg(r).arg(g).arg(b);
}

void MainWindow::updateWelcomeLabel(const std::string& text)
{
    // Convert std::string to QString and update the label
    ui->labelWelcome->setText(QString::fromStdString(text));
    
    // Enable word wrap for long text
    ui->labelWelcome->setWordWrap(true);
    
    // Adjust the label's size policy to allow it to grow
    ui->labelWelcome->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
