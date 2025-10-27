
---
# LightRanger 5 Click

> [LightRanger 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4592) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4592&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the LightRanger 5 Click board.
> This demo application shows an example of distance measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger5

### Example Key Functions

- `lightranger5_cfg_setup` Config Object Initialization function.
```c
void lightranger5_cfg_setup ( lightranger5_cfg_t *cfg );
```

- `lightranger5_init` Initialization function.
```c
err_t lightranger5_init ( lightranger5_t *ctx, lightranger5_cfg_t *cfg );
```

- `lightranger5_default_cfg` Click Default Configuration function.
```c
void lightranger5_default_cfg ( lightranger5_t *ctx );
```

- `lightranger5_get_status` LightRanger 5 get status function.
```c
err_t lightranger5_get_status ( lightranger5_t *ctx, uint8_t *status );
```

- `lightranger5_set_factory_calib_data` LightRanger 5 set factory calib data function.
```c
err_t lightranger5_set_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data );
```

- `lightranger5_measure_distance` LightRanger 5 measure distance function.
```c
uint16_t lightranger5_measure_distance ( lightranger5_t *ctx );
```

### Application Init

> Initialization of I2C module, log UART and additional pins.
> After driver initialization and default settings,
> the app performs and check factory calibrationa and 
> check and wait for OK status. This process takes a few seconds, so please wait.
> After current status is OK, app performs the configuration of the TMF8801 sensor:
> read and write calibration data, set algorithm state and command data. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    lightranger5_cfg_t lightranger5_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    lightranger5_cfg_setup( &lightranger5_cfg );
    LIGHTRANGER5_MAP_MIKROBUS( lightranger5_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger5_init( &lightranger5, &lightranger5_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    lightranger5_default_cfg( &lightranger5 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    if ( !lightranger5_check_factory_calibration( &lightranger5 ) ) {
        log_info( &logger, " Factory calibration success." );
    } else {
        log_info( &logger, " Factory calibration FAILED." );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    do {
        lightranger5_get_status( &lightranger5, &status );
        
        if ( status_old != status ) {
            if ( status < LIGHTRANGER5_STATUS_OK ) {
                display_status_no_error( );    
            } else {
                display_status_error( );   
            }  
            status_old = status;
        }
        Delay_ms ( 100 );
    } while ( status );
    
    lightranger5_get_factory_calib_data( &lightranger5, factory_calib_data );
    
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " factory_calib_data[ 14 ] =\r\n { " );
    
    for ( uint8_t n_cnt = 0 ; n_cnt < 14 ; n_cnt++ ) {
        log_printf( &logger, "0x%.2X, ", factory_calib_data[ n_cnt ] );
    }
    
    log_printf( &logger, "};\r\n" );
    log_printf( &logger, "------------------------------\r\n" );
    
    lightranger5_set_command( &lightranger5, LIGHTRANGER5_CMD_DL_CALIB_AND_STATE );

    lightranger5_set_factory_calib_data( &lightranger5, factory_calib_data );

    lightranger5_set_algorithm_state_data( &lightranger5, tmf8801_algo_state );
    
    lightranger5_set_command_data( &lightranger5, command_data );
    
    lightranger5_get_status( &lightranger5, &status );
        
    if ( status_old != status ) {
        if ( status < LIGHTRANGER5_STATUS_OK ) {
            display_status_no_error( );    
        } else {
            display_status_error( );   
        }  
        status_old = status;
    }
    
    lightranger5_get_currently_run_app( &lightranger5, &appid_data );
    
    if ( appid_data == LIGHTRANGER5_APPID_MEASUREMENT ) {
        log_printf( &logger, " Measurement app running.\r\n" );
    }
    else if ( appid_data == LIGHTRANGER5_APPID_BOOTLOADER ) {
        log_printf( &logger, " Bootloader running.\r\n" );
    } else {
        log_printf( &logger, " Result: 0x%X\r\n", appid_data );    
    }
    
    log_printf( &logger, "------------------------------\r\n" );
}
```

### Application Task

> This is an example that shows the use of a LightRanger 5 Click board.
> A new data ready is checked as soon as possible which signals 
> the time required for the ranging sensor to perform the distance measurement.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    
    if ( lightranger5_check_data_ready( &lightranger5 ) == LIGHTRANGER5_DATA_IS_READY ) {
        uint16_t distance_mm = lightranger5_measure_distance( &lightranger5 );
        
        if ( distance_mm ) {
            log_printf( &logger, "       Distance : %ld mm\r\n", distance_mm );    
        } else {
            log_printf( &logger, "         Out of range    \r\n" );    
        }
        
        log_printf( &logger, "------------------------------\r\n" );
    }
    
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
