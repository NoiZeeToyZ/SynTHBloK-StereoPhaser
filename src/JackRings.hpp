#pragma once
// JACK RINGS (Nov 26 2026, Nick): every jack gets ONE ring, same size on every module (r 3.1 mm, line 0.35 mm, the old
// STEREO PHASER CV ring), coloured by what it carries: audio IN gold #f2b632, audio OUT orange #ff7a00, everything else
// grey #8a8a8a. Drawn by the jack widget (BlackJack / SmallJack in plugin.hpp); panels no longer draw jack rings.
// The table lists only AUDIO ports (enum index = configInput / configOutput order); anything not listed is grey.
// Sidechain inputs count as audio, FM inputs do not (Nick, Nov 26). Keyed by model slug (same in the paid plugin and singles).
#include <rack.hpp>
#include <string>
#include <vector>
#include <cstring>

namespace jackrings {
struct Entry { const char* slug; std::vector<int> in, out; };
inline const std::vector<Entry>& table() {
    static const std::vector<Entry> t = {
        {"MatrixForge", {0,1}, {0,1}},
        {"Duo", {3,4}, {0,1,2,3}},
        {"Drum", {3,4}, {0,1,10,11,12,13,14,15,16,17,28,29}},
        {"MtxQuad", {9,11}, {0,1,2,3,5,6,7,8,9}},
        {"Quad", {9,11}, {0,1,2,3,5,6,7,8,9}},
        {"MatrixFx", {0,1,2,3,4,5,6,7,11}, {0,1}},
        {"Echo", {0,1}, {0,1}},
        {"Loop", {0,1,2,3,4,5,6,7}, {0,1,2,3,4,5,6,7,8,9}},
        {"GlitchEcho", {0,1}, {0,1}},
        {"Grit", {0,1}, {0,1}},
        {"Stereo", {0}, {0,1}},
        {"Matrix8", {}, {17,18}},
        {"Kick", {}, {0,1}},
        {"SnareHat", {}, {0,1,2}},
        {"Resonator", {4,5}, {0,1,3}},
        {"Poly", {}, {0,1}},
        {"Pulse", {}, {0}},
        {"DualFilter", {0,1}, {0,1,2,3}},
        {"NoizeeFlagshipFilter", {16,17}, {0,1}},
        {"FX", {9,10}, {0,1,2}},
        {"GrainForge", {0,1}, {0,1}},
        {"BlokMaster", {0,1,2}, {0,1}},
        {"Mix24", {6,7,8,9,10,11,12,13,14,15,16,17,18,19}, {0,1,2,3}},
        {"Mix8", {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23}, {0,1,2,3}},
        {"Mix12", {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}, {0,1,2,3}},
        {"ToyBox", {}, {3,4}},
    };
    return t;
}
enum Kind { GREY = 0, AUDIO_IN = 1, AUDIO_OUT = 2 };
inline Kind kindOf(const std::string& slug, bool out, int id) {
    for (const Entry& e : table()) {
        if (slug != e.slug) continue;
        for (int v : (out ? e.out : e.in)) if (v == id) return out ? AUDIO_OUT : AUDIO_IN;
        return GREY;
    }
    return GREY;
}
inline NVGcolor colour(Kind k) {
    if (k == AUDIO_IN)  return nvgRGB(0xf2, 0xb6, 0x32);
    if (k == AUDIO_OUT) return nvgRGB(0xff, 0x7a, 0x00);
    return nvgRGB(0x8a, 0x8a, 0x8a);
}
constexpr float RING_R_MM = 3.1f, RING_W_MM = 0.35f;
}  // namespace jackrings
