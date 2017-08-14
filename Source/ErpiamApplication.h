/*
  ==============================================================================

    ErpiamApplication.h
    Created: 6 Aug 2017 3:51:20pm
    Author:  Geert Bevin

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define LApp ErpiamApplication::getErpiamInstance()

namespace erpiam
{
    class ErpiamApplication  : public JUCEApplication
    {
    public:
        ErpiamApplication();
        virtual ~ErpiamApplication();
        
        static ErpiamApplication* getErpiamInstance() noexcept { return (ErpiamApplication*)ErpiamApplication::getInstance(); }
        
        const String getApplicationName() override       { return ProjectInfo::projectName; }
        const String getApplicationVersion() override    { return ProjectInfo::versionString; }
        bool moreThanOneInstanceAllowed() override       { return false; }
        
        void initialise(const String& commandLine) override;
        void shutdown() override;
        void systemRequestedQuit() override;
        
        class Pimpl;
    private:
        ScopedPointer<Pimpl> pimpl_;
    };
}
