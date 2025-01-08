
---
# pH 2 Click

> [pH 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5596) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5596&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for pH 2 Click driver. 
The library initializes and defines the I2C bus drivers or 
ADC drivers to read data from pH probe.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.pH2

### Example Key Functions

- `ph2_cfg_setup` Config Object Initialization function.
```c
void ph2_cfg_setup ( ph2_cfg_t *cfg );
```

- `ph2_init` Initialization function.
```c
err_t ph2_init ( ph2_t *ctx, ph2_cfg_t *cfg );
```

- `ph2_calibrate` Ph 2 calibrate function.
```c
err_t ph2_calibrate ( ph2_t *ctx, float pH_value );
```

- `ph2_calculate_ph` Ph 2 calculate pH value function.
```c
err_t ph2_calculate_ph ( ph2_t *ctx, float *pH_value );
```

- `ph2_calibrate_offset` Ph 2 calibrate offset function.
```c
void ph2_calibrate_offset ( ph2_t *ctx );
```

### Application Init

> Initializes the driver and performs offset calibration, 
as well as calibration in pH-neutral substance.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph2_cfg_t ph2_cfg;  /**< Click config object. */

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
    ph2_cfg_setup( &ph2_cfg );
    PH2_MAP_MIKROBUS( ph2_cfg, MIKROBUS_1 );
    err_t init_flag = ph2_init( &ph2, &ph2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, "     Performing calibration       \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " Disconect BNC connector, \r\n" );
    log_printf( &logger, "    short-circuit it, \r\n" );
    log_printf( &logger, " adjust offset potentiometer \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " STAT1 - turn clockwise \r\n" );
    log_printf( &logger, " STAT2 - turn counter-clockwise \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    ph2_calibrate_offset( &ph2 );
    
    log_printf( &logger, " Calibration completed \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    log_printf( &logger, " Connect probe back \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, " ================================ \r\n" );  
    
    ph2_calibrate( &ph2, 7 );
    
    log_printf( &logger, " Calibration done!  \r\n" );
    log_printf( &logger, " ================================ \r\n" ); 
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ================================ \r\n" ); 
}
```

### Application Task

> This example demonstrates the use of the pH 2 Click board by 
reading pH value of the substance where probe is placed.

```c
void application_task ( void ) 
{
    float pH_val = 0;
    ph2_calculate_ph( &ph2, &pH_val );
    log_printf( &logger, " pH value: %.3f \r\n", pH_val );
    log_printf( &logger, " ================================ \r\n" ); 
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
