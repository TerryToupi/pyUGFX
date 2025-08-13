## Prerequisites

- CMake (3.30 or higher)
- Python
- One of the following toolchains:
  - Visual Studio
  - Xcode
  - Ninja

## Installation

### General Setup

1. Clone the repository:
```bash
git clone https://github.com/TerryToupi/pyUGFX.git
cd pyUGFX
```

2. Create a build directory:
```bash
mkdir out
cd out
```

### Build Instructions

Choose one of the following methods based on your preferred toolchain:

#### Using Visual Studio

```bash
cmake -G "Visual Studio 17 2022" ..
cmake --build .
```

#### Using Xcode

```bash
cmake -G "Xcode" ..
cmake --build .
```

#### Using Ninja

```bash
cmake -G "Ninja" ..
cmake --build .
```

## Dependencies

- Python (required)
