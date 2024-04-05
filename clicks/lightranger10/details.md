
---
# LightRanger 10 click

> LightRanger 10 Click is a compact add-on board suitable for range-finding and distance sensing applications. This board features the VL53L4CX, a ToF (time of flight) optical distance sensor with an extended target detection range from STMicroelectronics. Specifically designed for long-range and multi-target measurements, the VL53L4CX provides very accurate distance measurements up to 6m with excellent results over short distances and 18° FoV (Field of View), which improves performances under ambient light. Data processing is performed inside the VL53L4CX, providing distance information and confidence values through its I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger 10 Click driver.

#### Standard key functions :

- `lightranger10_cfg_setup` Config Object Initialization function.
```c
void lightranger10_cfg_setup ( lightranger10_cfg_t *cfg );
```

- `lightranger10_init` Initialization function.
```c
err_t lightranger10_init ( lightranger10_t *ctx, lightranger10_cfg_t *cfg );
```

- `lightranger10_default_cfg` Click Default Configuration function.
```c
err_t lightranger10_default_cfg ( lightranger10_t *ctx );
```

#### Example key functions :

- `lightranger10_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t lightranger10_get_int_pin ( lightranger10_t *ctx );
```

- `lightranger10_clear_interrupts` This function clears the interrupts.
```c
err_t lightranger10_clear_interrupts ( lightranger10_t *ctx );
```

- `lightranger10_get_distance` This function reads the target object distance in millimeters.
```c
err_t lightranger10_get_distance ( lightranger10_t *ctx, uint16_t *distance_mm );
```

## Example Description

> This example demonstrates the use of LightRanger 10 click board by reading and displaying the target object distance in millimeters.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration, and then calibrates the sensor to the object positioned at 200mm distance from the sensor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger10_cfg_t lightranger10_cfg;  /**< Click config object. */

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
    lightranger10_cfg_setup( &lightranger10_cfg );
    LIGHTRANGER10_MAP_MIKROBUS( lightranger10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger10_init( &lightranger10, &lightranger10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER10_ERROR == lightranger10_default_cfg ( &lightranger10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " --- Sensor calibration --- \r\n" );
    log_printf( &logger, " Place an object at 200mm distance from sensor in the next 5 seconds.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Sensor calibration is in progress...\r\n" );
    if ( LIGHTRANGER10_ERROR == lightranger10_calibrate_distance ( &lightranger10, 200 ) )
    {
        log_error( &logger, " Sensor calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then clears the interrupt and reads the target distance in millimeters and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    while ( lightranger10_get_int_pin ( &lightranger10 ) );
    
    uint16_t distance_mm;
    if ( ( LIGHTRANGER10_OK == lightranger10_clear_interrupts ( &lightranger10 ) ) && 
         ( LIGHTRANGER10_OK == lightranger10_get_distance ( &lightranger10, &distance_mm ) ) )
    {
        log_printf ( &logger, " Distance: %u mm \r\n\n", distance_mm );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
