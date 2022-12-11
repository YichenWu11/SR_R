#include <engine/engine.h>

#include <core/base/macro.h>

// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define SRR_XSTR(s) SRR_STR(s)
#define SRR_STR(s) #s

int main() {
    SRR::Engine srr_engine;
    srr_engine.init();

    srr_engine.startEngine(SRR_XSTR(ROOT_DIR));

    srr_engine.run();

    srr_engine.shutdownEngine();

    return 0;
}
