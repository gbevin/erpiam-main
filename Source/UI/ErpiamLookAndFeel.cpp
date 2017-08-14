/*
  ==============================================================================

    ErpiamLookAndFeel.cpp
    Created: 6 Aug 2017 4:02:09pm
    Author:  Geert Bevin

  ==============================================================================
*/

#include "ErpiamLookAndFeel.h"

namespace erpiam
{
    struct ErpiamLookAndFeel::Pimpl
    {
        Pimpl() :
            dejaVuSans_(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSans_ttf, BinaryData::DejaVuSans_ttfSize)),
            dejaVuSansBold_(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansBold_ttf, BinaryData::DejaVuSansBold_ttfSize)),
            dejaVuSansMono_(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMono_ttf, BinaryData::DejaVuSansMono_ttfSize)),
            dejaVuSansMonoBold_(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMonoBold_ttf, BinaryData::DejaVuSansMonoBold_ttfSize))
        {
        }
        
        Typeface::Ptr getTypefaceForFont(const Font& font)
        {
            if (font.getTypefaceName() == "DejaVu Sans")
            {
                if (font.getTypefaceStyle() == "Bold")
                {
                    return dejaVuSansBold_;
                }
                else
                {
                    return dejaVuSans_;
                }
            }
            else if (font.getTypefaceName() == "DejaVu Sans Mono")
            {
                if (font.getTypefaceStyle() == "Bold")
                {
                    return dejaVuSansMonoBold_;
                }
                else
                {
                    return dejaVuSansMono_;
                }
            }

            return nullptr;
        }
        
        Typeface::Ptr dejaVuSans_;
        Typeface::Ptr dejaVuSansBold_;
        Typeface::Ptr dejaVuSansMono_;
        Typeface::Ptr dejaVuSansMonoBold_;
    };
        
    ErpiamLookAndFeel::ErpiamLookAndFeel() : pimpl_(new Pimpl())  {}
    ErpiamLookAndFeel::~ErpiamLookAndFeel()                       { pimpl_ = nullptr; }
    
    Typeface::Ptr ErpiamLookAndFeel::getTypefaceForFont(const Font& font)
    {
        Typeface::Ptr r = pimpl_->getTypefaceForFont(font);
        if (r)
        {
            return r;
        }
        return LookAndFeel::getTypefaceForFont(font);
    }
}

