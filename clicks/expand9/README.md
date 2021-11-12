\mainpage Main Page

---
# Expand 9 click

> Expand 9 Click is a compact add-on board that contains a multi-port I/O expander. This board features the SX1509QB, the world’s lowest voltage level shifting GPIO expander from Semtech Corporation. The SX1509QB comes in a 16-channel configuration and allows easy serial expansion of I/O through a standard I2C serial interface. It also has a built-in level shifting feature making it highly flexible in power supply systems where communication between incompatible I/O voltages is required, an integrated LED driver for enhanced lighting, and a keypad scanning engine to implement keypad applications up to 8x8 matrix.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand_9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand9 Click driver.

#### Standard key functions :

- `expand9_cfg_setup` Config Object Initialization function.
```c
void expand9_cfg_setup ( expand9_cfg_t *cfg );
```

- `expand9_init` Initialization function.
```c
err_t expand9_init ( expand9_t *ctx, expand9_cfg_t *cfg );
```

- `expand9_default_cfg` Click Default Configuration function.
```c
err_t expand9_default_cfg ( expand9_t *ctx );
```

#### Example key functions :

- `expand9_set_ch_output_state` Expand 9 set channel output state function.
```c
err_t expand9_set_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state );
```

- `expand9_led_driver_config` Expand 9 LED driver configuration function.
```c
err_t expand9_led_driver_config ( expand9_t *ctx, uint8_t ch_pos, uint8_t freq_div, uint8_t lin_log );
```

- `expand9_soft_reset` Expand 9 software reset function.
```c
err_t expand9_soft_reset ( expand9_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the Expand 9 Click board™.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand9_cfg_t expand9_cfg;  /**< Click config object. */

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
    expand9_cfg_setup( &expand9_cfg );
    EXPAND9_MAP_MIKROBUS( expand9_cfg, MIKROBUS_1 );
    err_t init_flag = expand9_init( &expand9, &expand9_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    expand9_default_cfg ( &expand9 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

> his is an example that demonstrates the use of the Expand 9 Click board™.
> This example shows the capabilities of the Expand 9 click by toggling each of 16 available channels.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{   
    expand9_soft_reset( &expand9 );
    Delay_ms( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms( 100 );
    }
    
    expand9_soft_reset( &expand9 );
    Delay_ms( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms( 100 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
