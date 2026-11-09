// SynTHBloK-StereoPhaser: registers this plugin's modules.
#include "plugin.hpp"

Plugin* pluginInstance;

extern Model* modelSynTHBloKStereo;

void init(Plugin* p) {
    pluginInstance = p;
    p->addModel(modelSynTHBloKStereo);
}
