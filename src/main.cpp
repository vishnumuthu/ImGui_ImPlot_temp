#include "App.h"
#include "imgui.h"
#include "implot.h"
#include <vector>
#include <chrono>

struct ImGraph : App {
    using App::App;

    std::vector<float> fps_values;
    std::vector<float> time_seconds;

    std::chrono::high_resolution_clock::time_point last_time;
    float elapsed_time = 0.0f;
    float fps_counter = 0.0f;
    float frame_count = 0;
    float seconds_elapsed = 0;

    void Start() override {
        elapsed_time = 0.0f;
        last_time = std::chrono::high_resolution_clock::now();
    }

    void Update() override {
        // Compute deltaTime
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - last_time).count();
        last_time = now;

        // Update time and FPS tracking
        elapsed_time += deltaTime;
        frame_count++;

        // If 1 second has passed, log the average FPS
        if (elapsed_time >= 1.0f) {
            fps_values.push_back(frame_count);
            time_seconds.push_back(seconds_elapsed);

            // Reset counters
            elapsed_time = 0.0f;
            fps_counter = 0.0f;
            frame_count = 0;
            seconds_elapsed++;
        }

        // Set ImGui Window Size & Position
        ImGui::SetNextWindowSize(GetWindowSize());
        ImGui::SetNextWindowPos({0, 0});

        if (ImGui::Begin("FPS Monitor")) {
            if (ImPlot::BeginPlot("FPS vs Time")) {
                ImPlot::SetupAxes("Time (s)", "FPS", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
                ImPlot::PlotLine("FPS", time_seconds.data(), fps_values.data(), fps_values.size());
                ImPlot::EndPlot();
            }
        }
        ImGui::End();
    }
};

int main(int argc, char const* argv[]) {
    ImGraph app("ImGui_temp", 640, 480, argc, argv);
    app.Run();
    return 0;
}
