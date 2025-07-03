# Simple QNX Cockpit

A cross-platform vehicle cockpit application demonstrating real-time embedded system development for automotive applications. Built with C++ and designed to run identically on both Linux development environments and QNX real-time operating systems.

## Overview

This project showcases a minimal yet functional vehicle dashboard with basic speed simulation for demonstration purposes. The application features a text-based user interface with animated speed gauges, making it ideal for embedded systems where graphical displays may not be available or necessary.

**Key Use Cases:**
- Embedded automotive development prototyping
- QNX real-time system demonstrations
- Cross-platform C++ development examples
- Educational tool for understanding automotive software

## Features
- Real-time speed display with ASCII progress bar
- Animated speed simulation (0-120 km/h)
- Color-coded fuel gauge display with dynamic consumption based on speed
- Low fuel warnings and vehicle slowdown when fuel is empty
- Status indicators (PARKED, CITY, HIGHWAY, HIGH SPEED)
- Auto-exit after 20 seconds
- Cross-platform support (Linux/QNX)

## Quick Start

### Linux
```bash
make linux
```

### QNX Target
```bash
make qnx
```

## Build Options

### Platforms
- `linux` - Native Linux build
- `aarch64le` - QNX ARM 64-bit

### Examples
```bash
# Linux build and run
make linux

# QNX build, deploy and run
make qnx

# Deploy only to QNX target
make qnx-deploy

# Clean all builds
make clean
```

## Architecture

### Cross-Platform Design
- **Single codebase** - Same C++ source runs on both platforms
- **Conditional compilation** - Automatic compiler selection (gcc/g++ for Linux, qcc/q++ for QNX)
- **Platform-specific builds** - Separate build directories for each target
- **Remote deployment** - Automated SCP/SSH deployment to QNX targets

### Technical Details
- **Language**: C++
- **Build system**: GNU Make
- **QNX compiler**: QNX Software Development Platform
- **Linux compiler**: GCC
- **Dependencies**: Standard C++ library only

## Configuration

### QNX Target Settings
```bash
export TARGET_IP=10.1.10.107    # QNX target IP address
export TARGET_USER=root         # SSH username for target
export TARGET_PATH=/tmp         # Deployment directory on target
```

### Development Requirements
- **Linux**: GCC/G++ compiler
- **QNX**: QNX Software Development Platform with ARM64 support
- **Network**: SSH access to QNX target system

## Build Artifacts
- **Linux executable**: `build/linux/cockpit`
- **QNX executable**: `build/aarch64le/cockpit`
- **Object files**: `build/{platform}/*.o`
- **Dependency files**: `build/{platform}/*.d`

## Application Behavior
The cockpit simulation runs for exactly 20 seconds, displaying:
1. **Speed progression**: 0 → 120 km/h → 0 km/h in simple increments
2. **Visual speed meter**: ASCII progress bar showing current speed
3. **Fuel gauge**: Color-coded ASCII progress bar showing remaining fuel level (decreases faster at higher speeds)
   - Green: Normal fuel level (>25%)
   - Yellow: Medium-low fuel level (11-25%)
   - Red: Low fuel level (≤10%)
4. **Fuel warnings**: "LOW" warning when fuel is below 10%, "FUEL EMPTY" when depleted
5. **Vehicle behavior**: Speed automatically decreases when fuel is empty
6. **Status indicators**: PARKED → CITY → HIGHWAY → HIGH SPEED based on current speed
7. **Countdown timer**: Shows remaining runtime
8. **Automatic exit**: Clean shutdown after 20 seconds

## Troubleshooting
- **QNX connection issues**: Verify TARGET_IP and SSH access
- **Build failures**: Ensure QNX SDP is properly installed and configured
- **Permission errors**: Check SSH key authentication or use password authentication


## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This library is licensed under the MIT-0 License. See the [LICENSE](LICENSE) file.
