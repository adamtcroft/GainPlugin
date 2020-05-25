/*
  ==============================================================================

    GlobalDefines.h
    Created: 28 Apr 2020 11:04:00pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PLUGIN_WIDTH    170
#define PLUGIN_HEIGHT   325
#define SLIDER_WIDTH    50
#define SLIDER_HEIGHT   250

const Typeface::Ptr oswald = Typeface::createSystemTypefaceFor(BinaryData::OswaldStencil_ttf, BinaryData::OswaldStencil_ttfSize);

const Font labelFont = Font(oswald).withPointHeight(14.f).withStyle(1);

