#include <Compare.h>
#include <Const.h>
#include <PluginProcessor.h>
#include <catch2/catch_all.hpp>

TEST_CASE ("Testing pass-through processing block", "[PluginProcessor]")
{
    /// outline
    int numChannelsToAllocate = 2;                                                /// stereo
    int numSamplesToAllocate = 8;                                                 /// mini buffer (good for testing, but should be larger for real-world applications)
    juce::AudioBuffer<float> input (numChannelsToAllocate, numSamplesToAllocate); /// create the buffer

    // float modifiyingVariable = {}; // this could be gain, pan, threshold (e.g. for distortion), etc
    juce::AudioBuffer<float>* expectedBuffer = {};

    SECTION ("When passing-through, then output is equal to input")
    {
        // modifiyingVariable = ...; // set this to some actual value here and decribe above with 'when...then...'
        expectedBuffer = &input;
    }

    /// prepare
    auto writePointers = input.getArrayOfWritePointers();
    for (int j = 0; j < numSamplesToAllocate; ++j)
    {
        /// random mono signal
        writePointers[MCR::Const::LEFT][j] = (juce::Random().nextFloat() * 2.f) - 1.f;
        writePointers[MCR::Const::RIGHT][j] = writePointers[MCR::Const::LEFT][j];
    }

    auto output = input;

    /// exercise
    juce::MidiBuffer midiMessages;

    AudioPluginAudioProcessor audioPluginAudioProcessor;

    // audioPluginAudioProcessor.setModifyingVariable(modifiyingVariable);
    audioPluginAudioProcessor.processBlock (output, midiMessages);

    /// evaluate
    auto expectedSamples = (*expectedBuffer).getArrayOfWritePointers();
    auto actualSamples = output.getArrayOfWritePointers();
    for (int i = 0; i < numSamplesToAllocate; ++i)
    {
        auto actualL = actualSamples[MCR::Const::LEFT][i];
        auto expectedL = expectedSamples[MCR::Const::LEFT][i];
        REQUIRE (MCR::Compare::equalFloat (actualL, expectedL));

        auto actualR = actualSamples[MCR::Const::RIGHT][i];
        auto expectedR = expectedSamples[MCR::Const::RIGHT][i];
        REQUIRE (MCR::Compare::equalFloat (actualR, expectedR));
    }
}
