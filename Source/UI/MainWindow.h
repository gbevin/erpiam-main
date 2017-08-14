/*
  ==============================================================================

    MainWindow.h
    Created: 6 Aug 2017 3:45:49pm
    Author:  Geert Bevin

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace erpiam
{
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(String name);
        
        void closeButtonPressed() override;
        
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
}
