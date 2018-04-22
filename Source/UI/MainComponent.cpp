/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
namespace
{
    struct MidiMessageCallback : public CallbackMessage
    {
        MidiMessageCallback(Label* l, const String& txt) : label_(l), txt_(txt) {}

        void messageCallback()
        {
            String txt = label_->getText();
            txt += txt_;
            StringArray array = StringArray::fromLines(txt);
            if (array.size() > 14)
            {
                array.removeRange(0, array.size()-14);
            }
            label_->setText(array.joinIntoString("\n"), dontSendNotification);
        }

        Label* const label_;
        const String txt_;
    };
}
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    setWantsKeyboardFocus(false);

    for (int c = 0; c < getNumChildComponents(); ++c)
    {
        getChildComponent(c)->setVisible(false);
    }
    //[/Constructor_pre]

    addAndMakeVisible (textEditor_ = new TextEditor (String()));
    textEditor_->setMultiLine (true);
    textEditor_->setReturnKeyStartsNewLine (true);
    textEditor_->setReadOnly (false);
    textEditor_->setScrollbarsShown (true);
    textEditor_->setCaretVisible (true);
    textEditor_->setPopupMenuEnabled (true);
    textEditor_->setText (String());

    textEditor_->setBounds (16, 280, 768, 184);

    addAndMakeVisible (label_ = new Label (String(),
                                           String()));
    label_->setFont (Font ("DejaVu Sans Mono", 15.00f, Font::plain).withTypefaceStyle ("Book"));
    label_->setJustificationType (Justification::topLeft);
    label_->setEditable (false, false, false);
    label_->setColour (Label::backgroundColourId, Colour (0x33333333));
    label_->setColour (Label::textColourId, Colours::black);
    label_->setColour (TextEditor::textColourId, Colours::black);
    label_->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_->setBounds (16, 56, 768, 208);

    addAndMakeVisible (title_ = new Label ("new label",
                                           TRANS("ERPIAM - Embedded Raspberry PI for Audio and MIDI")));
    title_->setFont (Font ("DejaVu Sans", 23.00f, Font::plain).withTypefaceStyle ("Bold"));
    title_->setJustificationType (Justification::centred);
    title_->setEditable (false, false, false);
    title_->setColour (Label::textColourId, Colours::black);
    title_->setColour (TextEditor::textColourId, Colours::black);
    title_->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    textEditor_->setScrollbarsShown(true);
    textEditor_->setFont(Font ("DejaVu Sans", 23.00f, Font::plain));
    label_->setMinimumHorizontalScale(1);
    //[/UserPreSize]

    setSize (800, 480);


    //[Constructor] You can add your own custom stuff here..
    startTimer(2000);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    for (MidiInput* input : midiInputs_)
    {
        input->stop();
        delete input;
    }
    midiInputs_.clear();
    //[/Destructor_pre]

    textEditor_ = nullptr;
    label_ = nullptr;
    title_ = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    for (int i = 0; i < getNumChildComponents(); ++i)
    {
        Component* c = getChildComponent(i);
        c->setBounds((getWidth() - c->getWidth()) / 2, 10, c->getWidth(), c->getHeight());
    }
    //[/UserPreResize]

    title_->setBounds ((getWidth() / 2) - (proportionOfWidth (1.0000f) / 2), 16, proportionOfWidth (1.0000f), 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::visibilityChanged()
{
}

void MainComponent::showPanel(Component* panel)
{
    if (panel)
    {
        Component* parent = panel->getParentComponent();
        // hide all sibling panels
        if (parent)
        {
            for (int i = 0; i < parent->getNumChildComponents(); ++i)
            {
                Component* child = parent->getChildComponent(i);
                if (child && child != panel)
                {
                    child->setVisible(false);
                }
            }
        }

        panel->setVisible(true);
    }
}

void MainComponent::timerCallback()
{
    String audio;
    OwnedArray<AudioIODeviceType> types;
    adm_.createAudioDeviceTypes(types);
    for (int i = 0; i < types.size(); ++i)
    {
        String typeName (types[i]->getTypeName());
        types[i]->scanForDevices();
        StringArray deviceNames (types[i]->getDeviceNames());
        for (int j = 0; j < deviceNames.size(); ++j)
        {
            audio += typeName + ": " + deviceNames[j] + "\n";
        }
    }

    String midi;
    StringArray midi_devices = MidiInput::getDevices();
    if (!midi_devices.isEmpty())
    {
        midi = midi_devices.joinIntoString("\n");
    }

    if (lastAudio_ != audio || lastMidi_ != midi)
    {
        for (MidiInput* input : midiInputs_)
        {
            input->stop();
            delete input;
        }
        midiInputs_.clear();

        for (int i = 0; i < midi_devices.size(); ++i)
        {
            MidiInput* input = MidiInput::openDevice(i, this);
            if (input != nullptr)
            {
                input->start();
                midiInputs_.add(input);
            }
        }
        textEditor_->setText(audio + midi + "\n");
        label_->setText("", dontSendNotification);
        lastAudio_ = audio;
        lastMidi_ = midi;
    }
}

String output7Bit(int v)
{
    return String::toHexString(v).paddedLeft('0', 2).toUpperCase();
}

String output14Bit(int v)
{
    return String::toHexString(v).paddedLeft('0', 4).toUpperCase();
}

String outputNote(const MidiMessage& msg)
{
    return MidiMessage::getMidiNoteName(msg.getNoteNumber(), true, true, 3).paddedLeft(' ', 4);
}

String outputChannel(const MidiMessage& msg)
{
    return output7Bit(msg.getChannel()).paddedLeft(' ', 2);
}

void MainComponent::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& msg)
{
    String txt;

    Time t = Time::getCurrentTime();
    txt << String(t.getHours()).paddedLeft('0', 2) << ":"
    << String(t.getMinutes()).paddedLeft('0', 2) << ":"
    << String(t.getSeconds()).paddedLeft('0', 2) << "."
    << String(t.getMilliseconds()).paddedLeft('0', 3) << "   ";

    txt << source->getName() + "   ";
    if (msg.isNoteOn())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "note-on         " << outputNote(msg) << " " << output7Bit(msg.getVelocity()).paddedLeft(' ', 3) << "\n";
    }
    else if (msg.isNoteOff())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "note-off        " << outputNote(msg) << " " << output7Bit(msg.getVelocity()).paddedLeft(' ', 3) << "\n";
    }
    else if (msg.isAftertouch())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "poly-pressure   " << outputNote(msg) << " " << output7Bit(msg.getAfterTouchValue()).paddedLeft(' ', 3) << "\n";
    }
    else if (msg.isController())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "control-change   " << output7Bit(msg.getControllerNumber()).paddedLeft(' ', 3) << " "
        << output7Bit(msg.getControllerValue()).paddedLeft(' ', 3) << "\n";
    }
    else if (msg.isProgramChange())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "program-change   " << output7Bit(msg.getProgramChangeNumber()).paddedLeft(' ', 7) << "\n";
    }
    else if (msg.isChannelPressure())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "channel-pressure " << output7Bit(msg.getChannelPressureValue()).paddedLeft(' ', 7) << "\n";
    }
    else if (msg.isPitchWheel())
    {
        txt << "channel "  << outputChannel(msg) << "   " <<
        "pitch-bend       " << output14Bit(msg.getPitchWheelValue()).paddedLeft(' ', 7) << "\n";
    }
    else if (msg.isMidiClock())
    {
        txt << "midi-clock" << "\n";
    }
    else if (msg.isMidiStart())
    {
        txt << "start" << "\n";
    }
    else if (msg.isMidiStop())
    {
        txt << "stop" << "\n";
    }
    else if (msg.isMidiContinue())
    {
        txt << "continue" << "\n";
    }
    else if (msg.isActiveSense())
    {
        txt << "active-sensing" << "\n";
    }
    else if (msg.getRawDataSize() == 1 && msg.getRawData()[0] == 0xff)
    {
        txt << "reset" << "\n";
    }
    else if (msg.isSysEx())
    {
        txt << "system-exclusive";

        int size = msg.getSysExDataSize();
        const uint8* data = msg.getSysExData();
        while (size--)
        {
            uint8 b = *data++;
            txt << " " << output7Bit(b);
        }

        txt << "\n";
    }
    else if (msg.isQuarterFrame())
    {
        txt << "time-code " << output7Bit(msg.getQuarterFrameSequenceNumber()).paddedLeft(' ', 2) << " " << output7Bit(msg.getQuarterFrameValue()) << "\n";
    }
    else if (msg.isSongPositionPointer())
    {
        txt << "song-position " << output14Bit(msg.getSongPositionPointerMidiBeat()).paddedLeft(' ', 5) << "\n";
    }
    else if (msg.getRawDataSize() == 2 && msg.getRawData()[0] == 0xf3)
    {
        txt << "song-select " << output7Bit(msg.getRawData()[1]).paddedLeft(' ', 3) << "\n";
    }
    else if (msg.getRawDataSize() == 1 && msg.getRawData()[0] == 0xf6)
    {
        txt << "tune-request" << "\n";
    }

    (new MidiMessageCallback(label_, txt))->post();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public Timer, public MidiInputCallback"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="0" overlayOpacity="0.330" fixedSize="1" initialWidth="800"
                 initialHeight="480">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="" id="4586c223bde2d7a" memberName="textEditor_" virtualName=""
              explicitFocusOrder="0" pos="16 280 768 184" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="" id="a8aa1e160e2f09ee" memberName="label_" virtualName=""
         explicitFocusOrder="0" pos="16 56 768 208" bkgCol="33333333"
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="DejaVu Sans Mono" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="9"
         typefaceStyle="Book"/>
  <LABEL name="new label" id="c5d1e84fdedf2ad6" memberName="title_" virtualName=""
         explicitFocusOrder="0" pos="0Cc 16 100% 32" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="ERPIAM - Embedded Raspberry PI for Audio and MIDI"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="DejaVu Sans" fontsize="23.00000000000000000000" kerning="0.00000000000000000000"
         bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
