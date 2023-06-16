\mainpage Main Page
  
---
# PWR Meter 2 click

> PWR Meter 2 click is a compact and accurate power monitoring Click board™, capable of measuring and monitoring voltage up to 24V and current up to 5A.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwrmeter2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwr-meter-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the PwrMeter2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PwrMeter2 Click driver.

#### Standard key functions :

- `pwrmeter2_cfg_setup` Config Object Initialization function.
```c
void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg ); 
```

- `pwrmeter2_init` Initialization function.
```c
err_t pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg );
```

- `pwrmeter2_default_cfg` Click Default Configuration function.
```c
err_t pwrmeter2_default_cfg ( pwrmeter2_t *ctx );
```

#### Example key functions :

- `pwrmeter2_get_data` This function gets the calculated voltage( V ), current( A ) and power( W ) data.
```c
err_t pwrmeter2_get_data ( pwrmeter2_t *ctx, float *voltage, float *current, float *power );
```

- `pwrmeter2_write_reg` This function writes 24-bit data to the register.
```c
err_t pwrmeter2_write_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t data_in );
```

- `pwrmeter2_read_reg` This function reads the desired number of 24-bit data from the register/registers.
```c
err_t pwrmeter2_read_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t len );
```

## Examples Description

> This app measuring and monitoring voltage up to 24V and current up to 5A.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter2_cfg_t pwrmeter2_cfg;  /**< Click config object. */

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
    pwrmeter2_cfg_setup( &pwrmeter2_cfg );
    PWRMETER2_MAP_MIKROBUS( pwrmeter2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pwrmeter2_init( &pwrmeter2, &pwrmeter2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER2_ERROR == pwrmeter2_default_cfg ( &pwrmeter2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Gets calculated voltage, current and power data every 500 milliseconds and shows results on UART.

```c

void application_task ( void )
{
    float voltage = 0;
    float current = 0;
    float power = 0;
    if ( PWRMETER2_OK == pwrmeter2_get_data( &pwrmeter2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " U = %.3f V\r\n", voltage );
        log_printf( &logger, " I = %.3f A\r\n", current );
        log_printf( &logger, " P = %.3f W\r\n\n", power );
        Delay_ms( 500 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PwrMeter2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
