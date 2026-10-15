#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "../src/aocs_ew_core.hpp"

// Regression and Edge Case Tests for AOCS-EW System
void test_extreme_sensor_failure() {
    AOCS_EW_Core system;
    SensorData faulty_sensor;
    faulty_sensor.hdr_lum = -999.0f; // Extreme invalid value
    faulty_sensor.lidar_range = 0.0f;
    faulty_sensor.ir_temp = 5000.0f; // Overheat / sensor glitch
    faulty_sensor.rwr_signal = 150.0f;
    
    EW_Control_Input ew_in;
    ew_in.incoming_radar_freq_ghz = 10.0f;
    ew_in.threat_level = 5;
    
    SystemState state = system.process_pipeline(faulty_sensor, ew_in);
    
    // Verify fallback to safe dampening values
    assert(state.delta_e < 1.0f);
    assert(state.rcs_reduction_db >= 30.0f);
    assert(state.latency_ms <= 3.3f);
    std::cout << "[PASS] test_extreme_sensor_failure passed.\n";
}

void test_zero_latency_boundary() {
    AOCS_EW_Core system;
    SensorData normal_sensor{500.0f, 50.0f, 295.0f, 10.0f};
    EW_Control_Input ew_in{9.5f, 2};
    
    for(int i = 0; i < 1000; ++i) {
        SystemState state = system.process_pipeline(normal_sensor, ew_in);
        assert(state.latency_ms <= 3.3f);
    }
    std::cout << "[PASS] test_zero_latency_boundary passed (1000 iterations).\n";
}

int main() {
    std::cout << "Running AOCS-EW Regression and Edge Case Suite...\n";
    test_extreme_sensor_failure();
    test_zero_latency_boundary();
    std::cout << "ALL REGRESSION TESTS PASSED SUCCESSFULLY.\n";
    return 0;
}
