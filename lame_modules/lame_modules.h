/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             lame_modules
    vendor:         LameDSP
    version:        0.0.1
    name:           Landon Viator
    description:    Plugins and yadayada
    website:        https://www.patreon.com/LameGenieVGM
    license:        Proprietary

    dependencies:

    END_JUCE_MODULE_DECLARATION
*/

#pragma once
#define LAME_MODULES_H_INCLUDED

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

/** Lame DSP Headers*/
#include "CompModule.h"
#include "DelayModule.h"
#include "DriveModule.h"
#include "GateModule.h"
#include "WhammyModule.h"
