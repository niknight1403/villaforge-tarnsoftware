#include "optimized_pipeline.hpp"
#include <cassert>
#include <iostream>

void run_performance_tests() {
    std::cout << "[TEST] Starting AOCS-EW Performance & Cost Optimization Tests..." << std::endl;

    aocs_ew::OptimizedPipeline pipeline(4);
    aocs_ew::SensorData sample_data;
    sample_data.timestamp_ns = 123456789;
    sample_data.rgb_data.resize(1920 * 1080 * 3, 0.5f);

    aocs_ew::OptimizationMetrics metrics;

    // Test 1: Standard High-Performance Mode
    pipeline.set_eco_mode(false);
    bool success_standard = pipeline.process_frame(sample_data, metrics);
    std::cout << "[TEST] Standard Mode Latency: " << metrics.end_to_end_latency_ms << " ms (CPU: " << metrics.cpu_utilization_pct << "%)" << std::endl;
    assert(success_standard && "Standard mode latency exceeded 3.3 ms budget!");

    // Test 2: ECO / Power-Saving Mode
    pipeline.set_eco_mode(true);
    bool success_eco = pipeline.process_frame(sample_data, metrics);
    std::cout << "[TEST] ECO Mode Latency: " << metrics.end_to_end_latency_ms << " ms (Power: " << metrics.power_consumption_w << " W)" << std::endl;
    assert(success_eco && "ECO mode latency exceeded 3.3 ms budget!");
    assert(metrics.power_consumption_w < 100.0 && "ECO mode power consumption target missed!");

    std::cout << "[PASS] All performance and cost optimization tests passed successfully!" << std::endl;
}

int main() {
    run_performance_tests();
    return 0;
}
