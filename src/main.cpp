#include <QApplication>
#include "mainwindow/mainwindow.h"
#include "include/toml.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    
    // // Example of updating the welcome label with a long text
    // std::string welcomeText = "Welcome to the Job Application Tracker!\n\n"
    //                          "This application helps you keep track of your job applications "
    //                          "by automatically editing text files. You can use it to:\n\n"
    //                          "• Track application status\n"
    //                          "• Store company information\n"
    //                          "• Keep notes about interviews\n"
    //                          "• Monitor follow-up dates\n\n"
    //                          "Get started by adding your first job application!";
    
    // window.updateWelcomeLabel(welcomeText);

    
    window.show();
    
    return app.exec();
}
