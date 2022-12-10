#pragma once

#include <string>

namespace SRR {
    class Engine {
    public:
        void startEngine(const std::string& root_path);
        void shutdownEngine();

        void init();
        void clear();

        void run();
        void tickOneFrame(float delta_time);

    protected:
        void logicalTick(float delta_time);
        void renderTick(float delta_time);

        void  calculateFPS(float delta_time);
        float calculateDeltaTime();
    };
} // namespace SRR
