#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "../src/aocs_ew_core.hpp"

// Test-Suite für Regression & Randfälle im AOCS-EW System
void test_extreme_sensor_failure() {
    std::cout << "[TEST] Starte Test: Extrem-Sensor-Ausfall & Fallback..." << std::endl;
    AOCSEWSystem system;
    system.initialize();

    // Simuliere Totalausfall von Kamera 1 und Radar Warning Receiver
    SensorData input;
    input.camera_active = false;
    input.rwr_active = false;
    input.lidar_active = true;
    input.ambient_temp_c = 25.0f;
    input.incoming_radar_ghz = 9.5f;

    SystemState state = system.process_frame(input);
    
    // Prüfe, ob das System auf LiDAR/IR-Fallback umschaltet und Latenz unter 3.3ms bleibt
    assert(state.latency_ms <= 3.3f);
    assert(state.fallback_mode_active == true);
    std::cout << "[PASS] Extrem-Sensor-Ausfall erfolgreich abgefangen. Latenz: " << state.latency_ms << "ms" << std::endl;
}

void test_supersonic_thermal_spike() {
    std::cout << "[TEST] Starte Test: Überschall-Thermoschock & Display-Kompensation..." << std::endl;
    AOCSEWSystem system;
    system.initialize();

    SensorData input;
    input.camera_active = true;
    input.rwr_active = true;
    input.lidar_active = true;
    input.ambient_temp_c = -40.0f;
    input.skin_temp_c = 120.0f; // extremer Überschall-Reibungshitze-Spike
    input.incoming_radar_ghz = 14.0f;

    SystemState state = system.process_frame(input);
    
    // Prüfe Thermokompensation und RCS-Reduktion
    assert(state.thermal_delta_ok == true);
    assert(state.rcs_reduction_db >= 30.0f);
    std::cout << "[PASS] Überschall-Thermoschock kompensiert. RCS-Reduktion: " << state.rcs_reduction_db << " dB" << std::endl;
}

int main() {
    std::cout << "=== AOCS-EW REGRESSION & RANDFALL TEST-SUITE ===" << std::endl;
    try {
        test_extreme_sensor_failure();
        test_supersonic_thermal_spike();
        std::cout << "=== ALLE REGRESSIONSTESTS ERFOLGREICH BESTANDEN ===" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Test fehlgeschlagen: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
