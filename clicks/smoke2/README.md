
---
# Smoke 2 Click

> [Smoke 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4299) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4299&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example is made to see how Smoke 2 Clicks work. The purpose of this example is that, depending on the way we choose, 
it collects data from the external environment about smoke, processes it, and prints it via the UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Smoke2

### Example Key Functions

- `smoke2_cfg_setup` Config Object Initialization function.
```c
void smoke2_cfg_setup ( smoke2_cfg_t *cfg );
```

- `smoke2_init` Initialization function.
```c
err_t smoke2_init ( smoke2_t *ctx, smoke2_cfg_t *cfg );
```

- `smoke2_default_cfg` Click Default Configuration function.
```c
err_t smoke2_default_cfg ( smoke2_t *ctx );
```

- `smoke2_get_int_pin` This function eget state of int pin of Smoke 2 Click board.
```c
uint8_t smoke2_get_int_pin ( smoke2_t *ctx );
```

- `smoke2_write_data` This function is generic for writing data to register of Smoke 2 Click board.
```c
void smoke2_write_data( smoke2_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `smoke2_read_data` This function is generic for reading data from registar of Smoke 2 Click board.
```c
uint16_t smoke2_read_data( smoke2_t *ctx, uint8_t reg );
```

### Application Init

> Initialization of communication modules, additional pins, Mapping pins and configures device for measurement.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    smoke2_cfg_t smoke2_cfg;      /**< Click config object. */
    
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
    smoke2_cfg_setup( &smoke2_cfg );
    SMOKE2_MAP_MIKROBUS( smoke2_cfg, MIKROBUS_1 );
    err_t init_flag  = smoke2_init( &smoke2, &smoke2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    smoke2_soft_reset( &smoke2 );
    smoke2_set_mode( &smoke2, SMOKE2_MODE_IDLE );

    uint16_t devid = smoke2_read_data( &smoke2, SMOKE2_REG_DEVID );
    log_printf( &logger, ">> ID:  0x%.2X\r\n", ( uint16_t ) ( devid & 0xFF ) );  
    log_printf( &logger, ">> REV: 0x%.2X\r\n", ( uint16_t ) ( ( devid >> 8 ) & 0xFF ) );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">> Configuration <<\r\n" );
    smoke2_default_cfg( &smoke2 ); 
    Delay_ms ( 1000 ); 
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    log_printf( &logger, ">> SMOKE MODE <<\r\n" );
    log_printf( &logger, ">> Calibration <<\r\n" );
    uint16_t calib_data = smoke2_smoke_calibration( &smoke2, 500 );
    log_printf( &logger, ">> Calibration data: %u\r\n", calib_data );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    log_printf( &logger, ">> PROXIMITY MODE <<\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Example shows module working depending on example mode. We can choose between: EXAMPLE_MODE_PROXIMITY and EXAMPLE_MODE_SMOKE.

```c
void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    smoke_example( &smoke2 );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    proximity_example( );
#endif
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
