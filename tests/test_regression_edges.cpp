#include "optimized_pipeline.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void run_edge_case_tests() {
    std::cout << "[TEST] Starting AOCS-EW Edge Case & Regression Tests..." << std::endl;

    aocs_ew::OptimizedPipeline pipeline(4);
    aocs_ew::SensorData sample_data;
    aocs_ew::OptimizationMetrics metrics;

    // Edge Case 1: Empty / Zero-size sensor frame
    sample_data.timestamp_ns = 1000000;
    sample_data.rgb_data.clear();
    pipeline.set_eco_mode(false);
    bool empty_success = pipeline.process_frame(sample_data, metrics);
    std::cout << "[TEST] Empty Frame Latency: " << metrics.end_to_end_latency_ms << " ms" << std::endl;
    assert(empty_success && "Handling empty frame failed!");

    // Edge Case 2: Extreme high-load frame data
    sample_data.rgb_data.resize(3840 * 2160 * 3, 0.99f); // 4K resolution payload
    bool highload_success = pipeline.process_frame(sample_data, metrics);
    std::cout << "[TEST] 4K High-Load Latency: " << metrics.end_to_end_latency_ms << " ms" << std::endl;
    assert(metrics.end_to_end_latency_ms <= 3.3 && "High-load latency violated 3.3 ms budget!");

    // Edge Case 3: Rapid ECO-Mode Toggle Regression Test
    for (int i = 0; i < 10; ++i) {
        pipeline.set_eco_mode(i % 2 == 0);
        bool toggle_success = pipeline.process_frame(sample_data, metrics);
        assert(toggle_success && "Rapid ECO-mode toggle failed!");
    }
    std::cout << "[TEST] Rapid ECO Toggle passed!" << std::endl;

    std::cout << "[PASS] All regression and edge case tests passed successfully!" << std::endl;
}

int main() {
    run_edge_case_tests();
    return 0;
}
