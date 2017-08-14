/*
  ==============================================================================

    MainWindow.cpp
    Created: 6 Aug 2017 3:45:49pm
    Author:  Geert Bevin

  ==============================================================================
*/

#include "MainWindow.h"

#include "MainComponent.h"

namespace erpiam
{
    MainWindow::MainWindow(String name) : DocumentWindow(name, Colours::white, DocumentWindow::closeButton)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), false);
        centreWithSize(800, 480);
        setVisible(true);

        setWantsKeyboardFocus(false);
    }

    void MainWindow::closeButtonPressed()
    {
        JUCEApplication::getInstance()->systemRequestedQuit();
    }
}
