\# Vector CAN DBC-to-AUTOSAR C Code Generator



A deterministic automotive tooling pipeline in Python and C99 that parses Vector CAN network matrix database (`.dbc`) files and auto-synthesizes MISRA-compliant signal serialization (`Pack`) and deserialization (`Unpack`) C routines.



\## Key Features

\- \*\*Zero-Manual Bit Manipulation:\*\* Eliminates manual bit-shift and mask off-by-one errors by automatically computing bitfield masks `(1 << length) - 1`.

\- \*\*Quantization Protection:\*\* Applies round-to-nearest-integer arithmetic (`+0.5f`) during floating-point to raw integer quantization.

\- \*\*Physical Boundary Clamping:\*\* Clamps out-of-range sensor readings to DBC-defined physical minimum and maximum limits before bus serialization.

\- \*\*Automated Round-Trip Test Harness:\*\* C test suite validating round-trip accuracy against signal resolution tolerances using IEEE 754 float approximations.



\## Signal Layout Specification (CAN ID: 0x120 / Powertrain\_Data)

\- `EngineSpeed`: Start bit 0, 16 bits, Factor 0.25, Offset 0 (0 to 8000 RPM)

\- `VehicleSpeed`: Start bit 16, 12 bits, Factor 0.1, Offset 0 (0 to 250 km/h)

\- `EngineTemp`: Start bit 28, 8 bits, Factor 1.0, Offset -40 (-40 to 215 degC)

\- `ThrottlePosition`: Start bit 36, 8 bits, Factor 0.5, Offset 0 (0 to 100 %)

\- `EngineStatus`: Start bit 44, 2 bits, Factor 1.0, Offset 0 (0 to 3)



\## Quick Start

```bash

\# Generate C files, compile test harness, and execute validation

make

