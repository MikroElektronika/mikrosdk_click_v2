
---
# CapSense 2 Click

> CapSense 2 Click is a compact add-on board that easily integrates projected capacitive touch into user's applications. This board features the CAP1114, a multi-channel capacitive touch sensor that takes human body capacitance as an input and directly provides the real-time sensor information via the I2C serial interface from Microchip. This board contains capacitive sensing elements, a 7-segment slider, two buttons, and four LED indicators that visually detect the activation on some of these parts. This Click board™ offers reliable and accurate sensing for any application that uses capacitive touch sensing functions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capsense2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/capsense-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the CapSense 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CapSense 2 Click driver.

#### Standard key functions :

- `capsense2_cfg_setup` Config Object Initialization function.
```c
void capsense2_cfg_setup ( capsense2_cfg_t *cfg );
```

- `capsense2_init` Initialization function.
```c
err_t capsense2_init ( capsense2_t *ctx, capsense2_cfg_t *cfg );
```

- `capsense2_default_cfg` Click Default Configuration function.
```c
err_t capsense2_default_cfg ( capsense2_t *ctx );
```

#### Example key functions :

- `capsense2_read_register` This function reads a data byte from the selected register by using I2C serial interface.
```c
err_t capsense2_read_register ( capsense2_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `capsense2_get_alert_pin` This function returns the alert pin logic state.
```c
uint8_t capsense2_get_alert_pin ( capsense2_t *ctx );
```

- `capsense2_clear_interrupt` This function clears the INT bit of the main status register if the interrupt pin is asserted.
```c
err_t capsense2_clear_interrupt ( capsense2_t *ctx );
```

## Example Description

> This example demonstrates the use of CapSense 2 Click board by reading and displaying the sensor's events.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration
which resets the Click board and links the desired LEDs to buttons and swipe sensors.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    capsense2_cfg_t capsense2_cfg;  /**< Click config object. */

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
    capsense2_cfg_setup( &capsense2_cfg );
    CAPSENSE2_MAP_MIKROBUS( capsense2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == capsense2_init( &capsense2, &capsense2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPSENSE2_ERROR == capsense2_default_cfg ( &capsense2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for an event interrupt and displays the event on the USB UART.

```c
void application_task ( void )
{
    if ( capsense2_get_alert_pin ( &capsense2 ) )
    {
        uint8_t button_status = 0;
        if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_BUTTON_STATUS_1, &button_status ) )
        {
            static uint8_t button_press_state = 0;
            static uint8_t swipe_state = 0;
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER )
            {
                if ( CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER != swipe_state )
                {
                    log_printf ( &logger, " Swipe UP \r\n\n" );
                    swipe_state = CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER )
            {
                if ( CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER != swipe_state )
                {
                    log_printf ( &logger, " Swipe DOWN \r\n\n" );
                    swipe_state = CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 )
            {
                if ( !( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) )
                {
                    log_printf ( &logger, " Button 1 pressed \r\n\n" );
                    button_press_state |= CAPSENSE2_BUTTON_STATUS_1_BUTTON_1;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 )
            {
                if ( !( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) )
                {
                    log_printf ( &logger, " Button 2 pressed \r\n\n" );
                    button_press_state |= CAPSENSE2_BUTTON_STATUS_1_BUTTON_2;
                }
            }
            capsense2_clear_interrupt ( &capsense2 );
            
            // check if buttons are released
            if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_BUTTON_STATUS_1, &button_status ) )
            {
                if ( ( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) && 
                    !( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) )
                {
                    log_printf ( &logger, " Button 1 released \r\n\n" );
                    button_press_state &= ~CAPSENSE2_BUTTON_STATUS_1_BUTTON_1;
                }
                if ( ( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) && 
                    !( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) )
                {
                    log_printf ( &logger, " Button 2 released \r\n\n" );
                    button_press_state &= ~CAPSENSE2_BUTTON_STATUS_1_BUTTON_2;
                }
            }
            
            // check if swipe event is finished and display the slider position
            uint8_t slider = 0;
            if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_SLIDER_POSITION_DATA, &slider ) )
            {
                if ( slider )
                {
                    log_printf ( &logger, " Slider position: %u \r\n\n", ( uint16_t ) slider );
                }
                else
                {
                    swipe_state = 0;
                }
            }
        }
        capsense2_clear_interrupt ( &capsense2 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSense2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
