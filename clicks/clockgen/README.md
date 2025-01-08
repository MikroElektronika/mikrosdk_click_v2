
---
# Clock Gen Click

> [Clock Gen Click](https://www.mikroe.com/?pid_product=MIKROE-4113) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4113&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Clock Gen Click represent a replacement for crystals, crystal oscillators, VCXOs, phase-locked 
> loops (PLLs), and fanout buffers. This Click features an I2C configurable clock generator 
> based on a PLL + high resolution MultiSynth fractional divider architecture which can generate
> any frequency up to 200 MHz with 0 ppm error. The chip on Click is capable of generating 
> synchronous or free-running non-integer related clock frequencies at each of its outputs 
> (CLK0, CLK1, and CLK2), enabling one device to synthesize clocks for multiple clock domains in a design.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen

### Example Key Functions

- `clockgen_cfg_setup` Config Object Initialization function. 
```c
void clockgen_cfg_setup ( clockgen_cfg_t *cfg );
``` 
 
- `clockgen_init` Initialization function. 
```c
err_t clockgen_init ( clockgen_t *ctx, clockgen_cfg_t *cfg );
```

- `clockgen_default_cfg` Click Default Configuration function. 
```c
void clockgen_default_cfg ( clockgen_t *ctx );
```

- `clockgen_set_frequency` This function sets clock divider. 
```c
void clockgen_set_frequency( clockgen_t *ctx, uint8_t clk_num, uint8_t pll_num, uint32_t freq );
```
 
- `clockgen_setup_pll` This function sets pll. 
```c
void clockgen_setup_pll ( clockgen_t *ctx, uint8_t pll, uint8_t mult, uint32_t num );
```

- `clockgen_setup_multisyinth` This function sets clock frequency on specific clock. 
```c
void clockgen_setup_multisyinth ( clockgen_t *ctx, uint8_t clk_num, uint32_t divider, uint32_t num );
```

### Application Init

> Configures device to default function that enables clock 0 and disables all others.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );


    //  Click initialization.

    clockgen_cfg_setup( &cfg );
    CLOCKGEN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen_init( &clockgen, &cfg );

    clockgen_default_cfg( &clockgen );
    
    Delay_ms ( 500 );
}
```

### Application Task

> Changes 4 different frequency in span of 5 seconds.

```c
void application_task ( void )
{
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
