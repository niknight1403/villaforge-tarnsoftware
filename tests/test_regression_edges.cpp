#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "../include/aocs_ew.hpp"

void test_extreme_edge_cases() {
    std::cout << "Running AOCS-EW Regression & Edge Case Tests..." << std::endl;

    // Test 1: Zero / Negative Latency spike recovery
    AOCSEWSystem system;
    bool init_ok = system.initialize(3840, 2160, 300.0);
    assert(init_ok);

    // Test 2: Extreme Environmental Stress (Mach 4.5, extreme temperature & multi-lock radar)
    SensorData sensors;
    sensors.hdr_illumination = 150000.0f; // Blinding flash
    sensors.lidar_range_m = 0.5f;       // Imminent collision / near surface
    sensors.ir_temp_c = 450.0f;         // High thermal stress
    sensors.rwr_threat_detected = true;
    sensors.radar_frequency_ghz = 14.5f; // Ku-band lock-on

    PerformanceMetrics metrics = system.process_frame(sensors);
    
    // Verify Green Light Protocol under extreme edge cases
    assert(metrics.end_to_end_latency_ms <= 3.3);
    assert(metrics.delta_e < 1.0);
    assert(metrics.rcs_reduction_db >= 30.0);
    assert(metrics.frame_drop_rate == 0.0);

    std::cout << "All Regression & Edge Case Tests Passed Successfully!" << std::endl;
}

int main() {
    try {
        test_extreme_edge_cases();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
