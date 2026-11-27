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
// JACK RINGS (Nov 26 2026, Nick): every jack draws its own ring, one size on every module, coloured by what it carries
// (src/JackRings.hpp: audio in gold, audio out orange, the rest grey). Panels no longer draw jack rings.
#include "JackRings.hpp"
struct RingPort : app::SvgPort {
    int ringKind = -1;   // resolved lazily in draw(): Rack -t screenshots and browser previews draw before any step()
    void resolveRing() {  // (Gemini review, Nov 26): module may be null there, the ModuleWidget's model is set by then
        app::ModuleWidget* mw = getAncestorOfType<app::ModuleWidget>();
        if (mw && mw->model) ringKind = jackrings::kindOf(mw->model->slug, type == engine::Port::OUTPUT, portId);
    }
    void draw(const DrawArgs& args) override {
        app::SvgPort::draw(args);   // jack + its shadow first, so the ring stays crisp (it clears the 2.5 mm jack body)
        if (ringKind < 0) resolveRing();
        nvgBeginPath(args.vg);
        nvgCircle(args.vg, box.size.x * 0.5f, box.size.y * 0.5f, mm2px(jackrings::RING_R_MM));
        nvgStrokeWidth(args.vg, mm2px(jackrings::RING_W_MM));
        nvgStrokeColor(args.vg, jackrings::colour(ringKind < 0 ? jackrings::GREY : (jackrings::Kind)ringKind));
        nvgStroke(args.vg);
    }
};

struct BlackJack : RingPort {
    // (Nov 14 2026, Nick: "make all the jacks match small jacks": every module's jacks are the 5.2 mm small jack now; the
    // 8 mm black / silver art stays in res/ in case it comes back. Jacks are placed by their centre, so they stay put.)
    BlackJack() { setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/JackSmall.svg"))); }
};

// Small version of BlackJack (5.2 mm), for the JAM and MIX-24 modules.
struct SmallJack : RingPort {
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

