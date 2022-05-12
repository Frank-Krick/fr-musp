#include <catch2/catch_test_macros.hpp>

#include <fr_musp/envelope/envelope_chain.h>

using namespace fr_musp::envelope;
using namespace std::chrono;
using namespace Catch;

TEST_CASE("The envelope chain size calculations") {
    EnvelopeChain<5> envelopeChain;

    SECTION("Should return the size of one envelope if one envelope is set") {
        milliseconds length(1000);
        unsigned int sampleRate(40000);
        Constant constant(length, sampleRate);
        EnvelopeSegment envelopeSegment(constant, 0.0f, 0.0f);
        envelopeChain.set(0, envelopeSegment);
        REQUIRE(envelopeChain.size() == envelopeSegment.size());
    }

    SECTION("Should return the sum of the sizes of all set envelopes") {
        milliseconds length(1000);
        unsigned int sampleRate(40000);
        Constant constant(length, sampleRate);
        EnvelopeSegment envelopeSegment(constant, 0.0f, 0.0f);
        envelopeChain.set(1, envelopeSegment);
        envelopeChain.set(3, envelopeSegment);
        REQUIRE(envelopeChain.size() == envelopeSegment.size() * 2);
    }
}

TEST_CASE("The envelope chain index operator") {
    EnvelopeChain<5> envelopeChain;
    milliseconds length(1000);
    unsigned int sampleRate(40000);
    Constant constant(length, sampleRate);
    EnvelopeSegment constantEnvelopeSegment(constant, 1.0f, 0.0f);
    float curvature(6.0f);
    ExponentialFall exponentialFall(length, curvature, sampleRate);
    EnvelopeSegment exponentialEnvelopeSegment(exponentialFall, 1.0f, 0.0f);
    envelopeChain.set(1, constantEnvelopeSegment);
    envelopeChain.set(3, exponentialEnvelopeSegment);

    SECTION("Should access the envelope segments in order") {
        for (unsigned int i = 0; i < constant.size(); i++) {
            REQUIRE(envelopeChain[i] == constantEnvelopeSegment[i]);
        }

        for (unsigned int i = constant.size();
             i < constant.size() + exponentialFall.size(); i++) {
            REQUIRE(envelopeChain[i] ==
                    exponentialEnvelopeSegment[i - constant.size()]);
        }
    }

    SECTION("Should be iterable") {
        unsigned int index{};
        for (auto value : envelopeChain) {
            REQUIRE(envelopeChain[index] == value);
            ++index;
        }
    }
}
