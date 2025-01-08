
---
# Fingerprint 3 Click

> [Fingerprint 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4265) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4265&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Fingerprint 3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint3

### Example Key Functions

- `fingerprint3_cfg_setup` Config Object Initialization function.
```c
void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg ); 
```

- `fingerprint3_init` Initialization function.
```c
err_t fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg );
```

- `fingerprint3_set_config` Set config function.
```c
uint8_t fingerprint3_set_config ( fingerprint3_t *ctx, uint32_t addr, uint32_t pass );
```

- `fingerprint3_take_image` Take image function.
```c
uint8_t fingerprint3_take_image ( fingerprint3_t *ctx );
```

- `fingerprint3_aura_control` Aura LED control function.
```c
uint8_t fingerprint3_aura_control ( fingerprint3_t *ctx, uint8_t control, uint8_t speed, uint8_t color, uint8_t times );
```

- `fingerprint3_finger_indicator` Finger indicator function.
```c
uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx );
```

### Application Init

> Initializes the driver, configures the sensor, and enrolls fingerprints.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint3_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.
    fingerprint3_cfg_setup( &cfg );
    FINGERPRINT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    err_t init_flag = fingerprint3_init( &fingerprint3, &cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    error_check = fingerprint3_set_config ( &fingerprint3, FINGERPRINT3_DEFAULT_ADDRESS, 
                                                           FINGERPRINT3_DEFAULT_PASSWORD );
    display_error( "Set Config" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_soft_reset ( &fingerprint3 );
    display_error( "Soft Reset" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_check_sensor ( &fingerprint3 );
    display_error( "Check Sensor" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_empty_library ( &fingerprint3 );
    display_error( "Empty the Library" );
    Delay_ms ( 500 );
    
    uint8_t cnt = 0; 
    do 
    {
        log_printf( &logger, " >>>  Register fingerprint %u of %u  <<<\r\n", ( uint16_t ) cnt + 1, 
                                                                             ( uint16_t ) NUMBER_OF_FINGERPRINTS );
        log_printf( &logger, "--------------------------------- \r\n" );
        error_check = enroll_finger ( &fingerprint3, LOCATION_IN_LIBRARY + cnt, NUMBER_OF_IMAGES );
        display_error( "Enroll finger" );
        if ( FINGERPRINT3_OK != error_check )
        {
            log_printf( &logger, " Please enroll your fingerprint again.\r\n" );
            log_printf( &logger, "--------------------------------- \r\n" );
        }
        else
        {
            cnt++;
        }
        Delay_ms ( 1000 );
    }
    while ( FINGERPRINT3_OK != error_check || cnt != NUMBER_OF_FINGERPRINTS );
}
```

### Application Task

> Takes an image of the finger, then checks if there's a fingerprint in the library that matches the
> one it has just read. All data is being logged on the USB UART.

```c
void application_task ( void )
{
    search_finger( &fingerprint3 );
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
