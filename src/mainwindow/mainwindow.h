#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include <string>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Function to update the welcome label
        void updateWelcomeLabel(const std::string& text);

    private slots:
        void onCloseButtonClicked();
        void onNextButtonClicked();
        void onCheckBoxDontShowClicked();
        void updateRainbowEffect();

    private:
        Ui::MainWindow *ui;
        int m_checkBoxClickCount = 0;
        QTimer* m_rainbowTimer = nullptr;
        float m_rainbowHue = 0.0f;
        
        void startRainbowEffect();
        void stopRainbowEffect();
        QString getRainbowStyleSheet(float hue);
};

#endif // MAINWINDOW_HH
