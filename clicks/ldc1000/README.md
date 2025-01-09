
---
# LDC 1000 Click

> [LDC 1000 Click](https://www.mikroe.com/?pid_product=MIKROE-1583) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1583&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize and configure the logger and Click modules and
  read and display proximity and impendance data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ldc1000

### Example Key Functions

- `ldc1000_cfg_setup` Config Object Initialization function. 
```c
void ldc1000_cfg_setup ( ldc1000_cfg_t *cfg );
``` 
 
- `ldc1000_init` Initialization function. 
```c
err_t ldc1000_init ( ldc1000_t *ctx, ldc1000_cfg_t *cfg );
```

- `ldc1000_default_cfg` Click Default Configuration function. 
```c
void ldc1000_default_cfg ( ldc1000_t *ctx );
```

- `ldc1000_get_proximity_data` This function reads the proximity data. 
```c
uint16_t ldc1000_get_proximity_data ( ldc1000_t *ctx );
```
 
- `ldc1000_get_inductance_data` This function reads the inductance data. 
```c
float ldc1000_get_inductance_data ( ldc1000_t *ctx );
```

- `ldc1000_get_int_input` This function reads the input voltage from the INT pin. 
```c
uint8_t ldc1000_get_int_input ( ldc1000_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. Configuration data 
  is written to the: rp maximum/minimum, sensor frequency, LDC/Clock/Power registers. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    ldc1000_cfg_t cfg;

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

    ldc1000_cfg_setup( &cfg );
    LDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1000_init( &ldc1000, &cfg );
    Delay_100ms( );
    ldc1000_default_cfg( &ldc1000 );
    Delay_100ms( );
}
```

### Application Task

> This function reads and displays proximity and impendance data every 10th of a second. 

```c
void application_task ( )
{
    uint16_t proximity;
    uint16_t inductance;

    proximity = ldc1000_get_proximity_data( &ldc1000 );
    inductance = ldc1000_get_inductance_data( &ldc1000 );

    if ( ( ( proximity - old_proximity ) > LDC1000_SENSITIVITY ) &&
         ( ( old_proximity - proximity ) > LDC1000_SENSITIVITY ) )
    {
        log_printf( &logger, " * Proximity: %d \r\n", proximity );

        log_printf( &logger, " * Impendance: %f uH\r\n", inductance );

        old_proximity = proximity;

        log_printf( &logger, "--------------------\r\n" );
        Delay_100ms();
    }
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
