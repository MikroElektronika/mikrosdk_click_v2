
---
# Barometer 3 Click

> [Barometer 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4190) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4190&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Barometer 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer3

### Example Key Functions

- `barometer3_cfg_setup` Config Object Initialization function. 
```c
void barometer3_cfg_setup ( barometer3_cfg_t *cfg );
``` 
 
- `barometer3_init` Initialization function. 
```c
err_t barometer3_init ( barometer3_t *ctx, barometer3_cfg_t *cfg );
```

- `barometer3_def_cfg` Click Default Configuration function. 
```c
void barometer3_def_cfg ( barometer3_t *ctx );
```

- `barometer3_cfg_temp` Temperature Measurement Configuration function. 
```c
void barometer3_cfg_temp ( barometer3_t *ctx, uint8_t temp_mr, uint8_t temp_osr );
```
 
- `barometer3_meas_temp_once` Get Temperature Measurement Once function. 
```c
uint8_t barometer3_meas_temp_once ( barometer3_t *ctx, float *result, uint8_t temp_osr );
```

- `barometer3_meas_prs_once` Get Pressure Measurement Once function. 
```c
uint8_t barometer3_meas_prs_once ( barometer3_t *ctx, float *result, uint8_t prs_osr );
```

### Application Init

> Initializes the driver, sets the Click board default configuration and check the communication by reading the device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer3_cfg_t cfg;
    uint8_t status_val;

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

    barometer3_cfg_setup( &cfg );
    BAROMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer3_init( &barometer3, &cfg );

    barometer3_def_cfg( &barometer3 );
    Delay_ms ( 100 );
    
    barometer3_generic_read( &barometer3, BAROMETER3_PROD_ID, &status_val, 1 );
    
    if ( status_val != BAROMETER3_PRODUCT_ID )
    {
        
        log_printf( &logger, " ERROR - wrong ID\r\n" );
        log_printf( &logger, " Please restart your system.\r\n" );
        for ( ; ; );
    }
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

> Reads the temperature [ Celsius ] and pressure [ mBar ] and displays the results on the USB UART.

```c
void application_task ( void )
{
    barometer3_cfg_temp( &barometer3, BAROMETER3_TMP_RATE_1, BAROMETER3_TMP_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_temp_once( &barometer3, &temperature, BAROMETER3_TMP_PRC_128 ) );
    log_printf( &logger, " Temperature: %.2f Celsius \r\n", temperature );
    
    barometer3_cfg_pres( &barometer3, BAROMETER3_PM_RATE_1, BAROMETER3_PM_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 ) );
    log_printf( &logger, " Pressure: %.2f mBar \r\n", pressure );
    log_printf( &logger, "----------------------- \r\n" );
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
