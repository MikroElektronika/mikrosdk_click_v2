\mainpage Main Page

---
# LED Driver 14 click

> LED Driver 14 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the BD18337EFV-M, a reliable four-channel constant current LED driver from Rohm Semiconductor. It is powered by an external power supply in the range of 5.5V to 20V, providing a maximum output current of 150mA per channel. The BD18337EFV-M also comes with the possibility for up to 3 LEDs in series on its output OUTx pin and built-in energy sharing control, selectable operational mode, and multiple built-in protection functions that protect the circuit during abnormalities. This Click board™ is ideal for LED rear lamps (turn/stop), fog lamps, and turn signals for automotive applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Driver 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 14 Click driver.

#### Standard key functions :

- `leddriver14_cfg_setup` Config Object Initialization function.
```c
void leddriver14_cfg_setup ( leddriver14_cfg_t *cfg );
```

- `leddriver14_init` Initialization function.
```c
err_t leddriver14_init ( leddriver14_t *ctx, leddriver14_cfg_t *cfg );
```

- `leddriver14_default_cfg` Click Default Configuration function.
```c
err_t leddriver14_default_cfg ( leddriver14_t *ctx );
```

#### Example key functions :

- `leddriver14_set_rset` This function sets the resistance of the selected rset channel.
```c
err_t leddriver14_set_rset ( leddriver14_t *ctx, uint8_t rset, uint16_t res_ohm );
```

- `leddriver14_get_int_pin` This function returns the int pin logic state.
```c
uint8_t leddriver14_get_int_pin ( leddriver14_t *ctx );
```

- `leddriver14_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver14_set_duty_cycle ( leddriver14_t *ctx, float duty_cycle );
```

## Example Description

> This example demonstrates the use of LED Driver 14 click board by controlling the brightness of LEDs by changing the PWM Duty Cycle.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver14_cfg_t leddriver14_cfg;  /**< Click config object. */

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
    leddriver14_cfg_setup( &leddriver14_cfg );
    LEDDRIVER14_MAP_MIKROBUS( leddriver14_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver14_init( &leddriver14, &leddriver14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( PWM_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER14_ERROR == leddriver14_default_cfg ( &leddriver14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Adjusts the LEDs' brightness by changing the PWM duty cycle every 500ms. A duty cycle value is being displayed on the USB UART.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver14_set_duty_cycle ( &leddriver14, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
    
    if ( !leddriver14_get_int_pin ( &leddriver14 ) )
    {
        log_info ( &logger, " Abnormality such as LED Open or the OUTx pin short circuit occured " );
    }
    
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
