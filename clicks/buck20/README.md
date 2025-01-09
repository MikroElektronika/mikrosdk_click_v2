
---
# Buck 20 Click

> [Buck 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5533) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5533&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Buck 20 Click by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck20

### Example Key Functions

- `buck20_cfg_setup` Config Object Initialization function.
```c
void buck20_cfg_setup ( buck20_cfg_t *cfg );
```

- `buck20_init` Initialization function.
```c
err_t buck20_init ( buck20_t *ctx, buck20_cfg_t *cfg );
```

- `buck20_set_wiper_1` This function sets wiper 1 to desired value.
```c
err_t buck20_set_wiper_1 ( buck20_t *ctx, uint16_t data_in );
```

- `buck20_enable_device` This function enables the buck device by setting the RST pin to high logic state.
```c
void buck20_enable_device ( buck20_t *ctx );
```

- `buck20_disable_device` This function disables the buck device by setting the RST pin to low logic state.
```c
void buck20_disable_device ( buck20_t *ctx );
```

### Application Init

> Initializes the driver and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck20_cfg_t buck20_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    buck20_cfg_setup( &buck20_cfg );
    BUCK20_MAP_MIKROBUS( buck20_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == buck20_init( &buck20, &buck20_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    buck20_set_wiper_1 ( &buck20, BUCK20_WIPER_ZERO_SCALE );
    buck20_enable_device ( &buck20 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the digipot wiper position, as well as an approximate buck R1 and voltage output.

```c
void application_task ( void )
{
    static uint16_t digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
    float buck_r1_kohm, buck_vout;
    if ( BUCK20_OK == buck20_set_wiper_1 ( &buck20, digipot_wiper ) )
    {
        buck_r1_kohm = BUCK20_RESISTOR_R6_KOHM + 
                       ( float ) ( BUCK20_DIGIPOT_MAX_KOHM * digipot_wiper ) / BUCK20_WIPER_FULL_SCALE;
        buck_vout = BUCK20_BUCK_VREF + ( buck_r1_kohm * BUCK20_BUCK_VREF ) / BUCK20_BUCK_R2_KOHM;
        log_printf( &logger, " Digipot wiper position: %u\r\n", digipot_wiper );
        log_printf( &logger, " Approximate R1 (Digipot+R6): %.2f kOhm\r\n", buck_r1_kohm );
        log_printf( &logger, " Approximate buck voltage output: %.2f V\r\n\n", buck_vout );
        digipot_wiper += 50;
        if ( digipot_wiper > BUCK20_WIPER_FULL_SCALE )
        {
            digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> An approximate buck R1 and VOUT values do not have to be 100% accurate for all wiper settings
but they are a good reference point. VOUT ranges from ~1.3V to ~5V, and it is the most accurate
around 3.3V since all passive components are set for that output.

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
