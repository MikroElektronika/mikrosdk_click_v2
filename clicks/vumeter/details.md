
---
# VU Meter click

> VU Meter Click is a compact add-on board representing a volume unit meter that displays the intensity of an audio signal. This board features the LM3914, a monolithic integrated circuit that senses analog voltage levels and drives a 10-segment bar graph display from Texas Instruments. This Click board™ is manufactured with a sound detecting device (microphone), Op-Amp, and the LM3914, which gleams the bar graph display according to the sound’s quality. The LM3914 is an analog-controlled driver meaning it can control (turn ON or OFF) a display by an analog input voltage and eliminates the need for additional programming.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vumeter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vu-meter-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the VUMeter Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VUMeter Click driver.

#### Standard key functions :

- `vumeter_cfg_setup` Config Object Initialization function.
```c
void vumeter_cfg_setup ( vumeter_cfg_t *cfg );
```

- `vumeter_init` Initialization function.
```c
err_t vumeter_init ( vumeter_t *ctx, vumeter_cfg_t *cfg );
```

#### Example key functions :

- `vumeter_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t vumeter_read_an_pin_voltage ( vumeter_t *ctx, float *data_out );
```

- `vumeter_set_gain_level` This function sets the input signal gain level (the microphone sensitivity).
```c
err_t vumeter_set_gain_level ( vumeter_t *ctx, uint8_t gain_lvl );
```

- `vumeter_calculate_vu_level` This function calculates VU level from the analog voltage input.
```c
float vumeter_calculate_vu_level ( vumeter_t *ctx, uint16_t sample_rate_ms );
```

## Example Description

> This example demonstrates the use of VU Meter click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the gain level (the microphone sensitivity) to maximum.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    vumeter_cfg_t vumeter_cfg;  /**< Click config object. */

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

    vumeter_cfg_setup( &vumeter_cfg );
    VUMETER_MAP_MIKROBUS( vumeter_cfg, MIKROBUS_1 );
    err_t init_flag  = vumeter_init( &vumeter, &vumeter_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vumeter_set_gain_level ( &vumeter, VUMETER_GAIN_LEVEL_MAX );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Calculates VU level from the analog voltage read from AN pin, and displays the results on the USB UART approximately every 100ms.

```c

void application_task ( void )
{
    log_printf( &logger, " VU level: %.3f VU\r\n", vumeter_calculate_vu_level ( &vumeter, 100 ) );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VUMeter

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
