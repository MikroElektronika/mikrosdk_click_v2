# Air Quality 13 Click Driver

## Bosch SDK Requirement

> ⚠️ **The Bosch BMV080 SDK is not included in this repository due to licensing restrictions.**
> The user must download the SDK separately, accept the Bosch Sensortec SLA, and copy the required files manually before building.

### How to obtain the SDK

1. Download the Bosch BMV080 SDK from the [Bosch Sensortec website](https://www.bosch-sensortec.com/en/products/environmental-sensors/particulate-matter-sensor/bmv080#software)
2. Accept the Bosch Sensortec Software License Agreement (SLA)
3. Extract the downloaded ZIP archive

### Files to copy

Copy the following 4 files from the extracted SDK into the driver's `lib_airquality13/bosch/` directory:

| Source path in Bosch SDK | Destination in driver |
|---|---|
| `api/inc/bmv080.h` | `lib_airquality13/bosch/inc/bmv080.h` |
| `api/inc/bmv080_defs.h` | `lib_airquality13/bosch/inc/bmv080_defs.h` |
| `api/lib/<architecture>/arm_none_eabi_gcc/release/lib_bmv080.a` | `lib_airquality13/bosch/lib/<architecture>/lib_bmv080.a` |
| `api/lib/<architecture>/arm_none_eabi_gcc/release/lib_postProcessor.a` | `lib_airquality13/bosch/lib/<architecture>/lib_postProcessor.a` |

Replace `<architecture>` with the folder matching your target MCU architecture:

| Target MCU architecture | Architecture folder |
|---|---|
| Cortex-M4F | `arm_cortex_m4f` |
| Cortex-M4 | `arm_cortex_m4` |
| Cortex-M0+ | `arm_cortex_m0plus` |
| Cortex-M7F | `arm_cortex_m7f` |
| Cortex-M33 | `arm_cortex_m33` |
| Cortex-M33F | `arm_cortex_m33f` |

### Expected directory structure after copying

```
lib_airquality13/
└── bosch/
    ├── inc/
    │   ├── bmv080.h
    │   └── bmv080_defs.h
    └── lib/
        └── <architecture>/
            ├── lib_bmv080.a
            └── lib_postProcessor.a
```

If the SDK files are not copied into place, the build will fail with a missing file error.

## Platform Support

The Bosch BMV080 SDK is distributed as pre-compiled GCC static libraries. Supported platforms are determined by available library binaries.

| Platform | MCU examples | Status |
|----------|-------------|--------|
| ARM Cortex-M4F | STM32F407ZG, TM4C129XNCZAD, MK64FN1M0VDC12 | ✅ Tested |
| ARM Cortex-M4 | STM32F302VC | ✅ Tested |
| ARM Cortex-M0+ | STM32G0C1VC | ✅ Tested |
| ARM Cortex-M33F | R7FA4M3AD2CBM | ✅ Tested |
| ARM Cortex-M7F | STM32F745ZG | ✅ Tested |

