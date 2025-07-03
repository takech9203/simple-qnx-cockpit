#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <string>

int main() {
    int speed = 0;
    bool increasing = true;
    int elapsed_time = 0;
    const int MAX_TIME = 20;
    
    // Initialize fuel level (100% full)
    int fuel_level = 100;
    
    std::cout << "Starting QNX Vehicle Cockpit..." << std::endl;
    sleep(1);
    
    while (elapsed_time < MAX_TIME) {
        // Clear screen
        std::cout << "\033[2J\033[H";
        
        std::cout << "=== QNX Vehicle Cockpit ===" << std::endl;
        std::cout << std::endl;
        
        // Speed display
        std::cout << "Speed: " << std::setw(3) << speed << " km/h" << std::endl;
        
        // Simple ASCII speed meter
        std::cout << "┌────────────────────────────┐" << std::endl;
        std::cout << "│";
        
        int bars = (speed * 28) / 200;
        for (int i = 0; i < 28; i++) {
            std::cout << (i < bars ? "█" : " ");
        }
        std::cout << "│" << std::endl;
        std::cout << "└────────────────────────────┘" << std::endl;
        std::cout << "0                        200" << std::endl;
        
        // Fuel gauge display
        std::cout << std::endl;
        
        // Determine fuel status text and color
        std::string fuel_status = "";
        if (fuel_level <= 10) {
            // Red text for low fuel
            fuel_status = " \033[1;31m[LOW]\033[0m";
        }
        
        std::cout << "Fuel: " << std::setw(3) << fuel_level << "%" << fuel_status << std::endl;
        
        // Simple ASCII fuel gauge
        std::cout << "┌────────────────────────────┐" << std::endl;
        std::cout << "│";
        
        int fuel_bars = (fuel_level * 28) / 100;
        for (int i = 0; i < 28; i++) {
            // Use different colors based on fuel level
            if (i < fuel_bars) {
                if (fuel_level <= 10) {
                    // Red for low fuel
                    std::cout << "\033[1;31m█\033[0m";
                } else if (fuel_level <= 25) {
                    // Yellow for medium-low fuel
                    std::cout << "\033[1;33m█\033[0m";
                } else {
                    // Green for normal fuel level
                    std::cout << "\033[1;32m█\033[0m";
                }
            } else {
                std::cout << " ";
            }
        }
        std::cout << "│" << std::endl;
        std::cout << "└────────────────────────────┘" << std::endl;
        std::cout << "E                          F" << std::endl;
        
        // Status
        std::cout << std::endl << "Status: ";
        if (speed == 0) std::cout << "PARKED";
        else if (speed < 50) std::cout << "CITY";
        else if (speed < 100) std::cout << "HIGHWAY";
        else std::cout << "HIGH SPEED";
        
        // Add fuel empty warning if applicable
        if (fuel_level == 0) {
            std::cout << " - \033[1;31mFUEL EMPTY\033[0m";
        }
        
        std::cout << std::endl << std::endl;
        std::cout << "Auto-exit in " << (MAX_TIME - elapsed_time) << " seconds" << std::endl;
        
        // Update speed
        if (increasing) {
            speed += 5;
            if (speed >= 120) increasing = false;
        } else {
            speed -= 3;
            if (speed <= 0) increasing = true;
        }
        
        // Update fuel level - decreases faster at higher speeds
        if (speed > 0) {
            // Adjust fuel consumption rate to be more reasonable for the 20-second simulation
            double fuel_decrease = 0.5;  // Base consumption rate
            if (speed > 80) fuel_decrease = 1.0;  // Higher consumption at high speeds
            
            // Ensure fuel doesn't go below 0
            fuel_level = std::max(0, static_cast<int>(fuel_level - fuel_decrease));
            
            // If fuel is empty, reduce speed
            if (fuel_level == 0) {
                speed = std::max(0, speed - 10);  // Slow down when out of fuel
            }
        }
        
        sleep(1);
        elapsed_time++;
    }
    
    std::cout << "\nCockpit shutting down..." << std::endl;
    
    return 0;
}