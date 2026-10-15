#ifndef AOCS_EW_OPTIMIZED_PIPELINE_H
#define AOCS_EW_OPTIMIZED_PIPELINE_H

#include <vector>
#include <chrono>
#include <cstdint>
#include <iostream>

namespace aocs_ew {

struct SensorData {
    uint64_t timestamp_ns;
    std::vector<float> rgb_data;
    std::vector<float> ir_data;
    std::vector<float> radar_warning_data;
};

struct OptimizationMetrics {
    double end_to_end_latency_ms;
    double cpu_utilization_pct;
    double memory_bandwidth_gbps;
    double power_consumption_w;
};

class OptimizedPipeline {
public:
    OptimizedPipeline(size_t buffer_pool_size = 4);
    ~OptimizedPipeline() = default;

    // Zero-copy processing step for multi-spectral sensor fusion
    bool process_frame(const SensorData& input, OptimizationMetrics& out_metrics);
    
    // Dynamic frequency scaling for low power consumption
    void set_eco_mode(bool enabled);

private:
    size_t pool_size;
    bool eco_mode;
    std::vector<std::vector<float>> memory_pool;
    size_t current_pool_index;
};

} // namespace aocs_ew

#endif // AOCS_EW_OPTIMIZED_PIPELINE_H
