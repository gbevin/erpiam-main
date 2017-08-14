/*
  ==============================================================================

    ErpiamApplication.cpp
    Created: 6 Aug 2017 3:51:20pm
    Author:  Geert Bevin

  ==============================================================================
*/

#include "ErpiamApplication.h"

#include "UI/ErpiamLookAndFeel.h"
#include "UI/MainComponent.h"
#include "UI/MainWindow.h"

namespace erpiam
{
    struct ErpiamApplication::Pimpl
    {
        Pimpl()
        {
        }
        
        void printVersion()
        {
            std::cout << ProjectInfo::projectName << " v" << ProjectInfo::versionString << std::endl;
        }
        
        void printUsage()
        {
            printVersion();
            std::cout << std::endl;
            std::cout << "Usage: " << ProjectInfo::projectName << " [ commands ]" << std::endl << std::endl
            << "Commands:" << std::endl
            << "  --version              Displays version information" << std::endl
            << "  --help                 Displays this help" << std::endl;
        }
        
        void initialise(const String& commandLine)
        {
            // parse command line parameters
            for (String param : JUCEApplication::getInstance()->getCommandLineParameterArray())
            {
                if (param.startsWith("--version"))
                {
                    printVersion();
                    systemRequestedQuit();
                    return;
                }
                else if (param == "--help")
                {
                    printUsage();
                    systemRequestedQuit();
                    return;
                }
            }
            
            // update the default look and feel
            Desktop::getInstance().setDefaultLookAndFeel(&lookAndFeel_);
            
            // start the GUI
            mainWindow_ = new MainWindow(JUCEApplication::getInstance()->getApplicationName());
            
            // run the application in full screen when the main display has the exact target dimensions
            Rectangle<int> displayArea = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
            if (displayArea.getWidth() == 800 && displayArea.getHeight() == 480)
            {
                Desktop::getInstance().setKioskModeComponent(mainWindow_, false);
            }
        }
        
        void shutdown()
        {
            mainWindow_ = nullptr;
        }
        
        void systemRequestedQuit()
        {
            quit();
        }
        
        ScopedPointer<MainWindow> mainWindow_;
        ErpiamLookAndFeel lookAndFeel_;
    };
    
    ErpiamApplication::ErpiamApplication() : pimpl_(new Pimpl())              {}
    ErpiamApplication::~ErpiamApplication()                                   { pimpl_ = nullptr; }
    
    void ErpiamApplication::initialise(const String& commandLine)                  { pimpl_->initialise(commandLine); }
    void ErpiamApplication::shutdown()                                             { pimpl_->shutdown(); }
    void ErpiamApplication::systemRequestedQuit()                                  { pimpl_->systemRequestedQuit(); }
}
