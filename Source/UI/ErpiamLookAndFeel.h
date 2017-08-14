/*
  ==============================================================================

    ErpiamLookAndFeel.h
    Created: 6 Aug 2017 4:02:09pm
    Author:  Geert Bevin

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace erpiam
{
    class ErpiamLookAndFeel : public LookAndFeel_V3
    {
    public:
        ErpiamLookAndFeel();
        ~ErpiamLookAndFeel();
        
        Typeface::Ptr getTypefaceForFont(const Font& font);
        
        class Pimpl;
    private:
        ScopedPointer<Pimpl> pimpl_;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ErpiamLookAndFeel)
    };
}
