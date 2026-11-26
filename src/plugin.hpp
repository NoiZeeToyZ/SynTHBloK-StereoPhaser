#pragma once
#include "rack.hpp"
#include <set>

using namespace rack;


// -------------------------------------------------------------

extern Plugin* pluginInstance;

// the panel screw on every SynTHBloK module: a black-oxide socket head cap screw (knurled rim, hex socket)
struct SocketScrew : app::SvgScrew {
    SocketScrew() { setSvg(Svg::load(asset::plugin(pluginInstance, "res/SocketScrewBlack.svg"))); }
};

extern Model* modelSynTHBloK;
extern Model* modelSynTHBloKBackdrop;
extern Model* modelSynTHBloKBlank;
extern Model* modelSynTHBloKPoly;
extern Model* modelSynTHBloKStereo;
extern Model* modelSynTHBloKFX;
extern Model* modelSynTHBloKMix24;
extern Model* modelNoizeeFlagshipFilter;
extern Model* modelSynTHBloKFilter;
extern Model* modelBloKMaster;
extern Model* modelSynTHBloKPlayer;
extern Model* modelSynTHBloKKick;
extern Model* modelSynTHBloKPlayerView;
extern Model* modelSynTHBloKSnareHat;
extern Model* modelSynTHBloKEuclid;
extern Model* modelSynTHBloKJamProbe;
extern Model* modelSynTHBloKJam;
extern Model* modelSynTHBloKMatrix8;
extern Model* modelSynTHBloKGrainForge;
extern Model* modelSynTHBloKMatrixForge;
extern Model* modelSynTHBloKDuo;
extern Model* modelSynTHBloKDrum;
extern Model* modelSynTHBloKMix12;
extern Model* modelSynTHBloKMix8;
extern Model* modelSynTHBloKEcho;
extern Model* modelSynTHBloKMatrixFx;
extern Model* modelSynTHBloKMatrixSong;
extern Model* modelSynTHBloKLoop;
extern Model* modelSynTHBloKMtxQuad;
extern Model* modelSynTHBloKDualFilter;
extern Model* modelSynTHBloKRandroyd;
extern Model* modelNoizeePatchGen;
// the module ids PATCH GEN placed (src/NoizeePatchGen.cpp): RANDROYD never patches into them
std::set<int64_t>& patchGenOwned();
// ONE RIG: set by a RANDROYD in the rack; PATCH GEN calls it so its patch packs into RANDROYD's rig
#include <functional>
std::function<void(history::ComplexAction*)>& randroydPackHook();

// VCV-size jack (23.7 px, the same as Rack's PJ301M): black body with a silver ring.
// Used on every module but the JAM and MIX-24.
struct BlackJack : app::SvgPort {
    // (Nov 14 2026, Nick: "make all the jacks match small jacks": every module's jacks are the 5.2 mm small jack now; the
    // 8 mm black / silver art stays in res/ in case it comes back. Jacks are placed by their centre, so they stay put.)
    BlackJack() { setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JackSmall.svg"))); }
};

// Small version of BlackJack (5.2 mm), for the JAM and MIX-24 modules.
struct SmallJack : app::SvgPort {
    SmallJack() { setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JackSmall.svg"))); }
};

struct MainToPoly {
    int   chainId;
    bool reset = false;
    float spread = 0.f;
    float cutoff = 0.f;  
    float env = 0.f;
    float vca = 0.f;
    float resonance;
    float drive;
    float filterMode; 
};

struct PolyToMain {
    float pitch[8];
    float env[8];
    float vca[8];
    float flt[8];
    int voices;
};

struct MainToStereo {
    float env;
    float accent;
    float postVCA;
};
// -------------------------------------------------------------
// INTERNAL 6‑STEM STEREO BUS (GLOBAL SHARED MIX BUS)
// -------------------------------------------------------------
struct SynTHBloKInternalBus {
    float L[6];
    float R[6];
};

