\mainpage Main Page

---
# PROFET 15A click

PROFET Click is a compact add-on board that contains a smart high-side power switch. This board features the BTS70041EPPXUMA1, a single-channel, high-side power switch with embedded protection and diagnosis feature from Infineon Technologies. This switch has a driving capability suitable for 15A loads featuring a ReverSave™, which causes the power transistor to switch on in case of reverse polarity. Besides its protection features, it also has pin-configurable diagnosis features such as proportional load current sense, open Load in ON and OFF state, and short circuit to ground and battery.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/profet15a_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/profet-click-15a)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the PROFET 15A Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PROFET 15A Click driver.

#### Standard key functions :

- `profet15a_cfg_setup` Config Object Initialization function.
```c
void profet15a_cfg_setup ( profet15a_cfg_t *cfg );
```

- `profet15a_init` Initialization function.
```c
err_t profet15a_init ( profet15a_t *ctx, profet15a_cfg_t *cfg );
```

#### Example key functions :

- `profet15a_read_an_pin_voltage` PROFET 15A read AN pin voltage level function.
```c
err_t profet15a_read_an_pin_voltage ( profet15a_t *ctx, float *data_out );
```

- `profet15a_set_mode` PROFET 15A set mode.
```c
err_t profet15a_set_mode ( profet15a_t *ctx, uint8_t mode );
```

## Example Description

> This example showcases the ability of the PROFET 15A Click board.
It configures Host MCU for communication and then enables 
and disables output channel. Besides that, it reads the voltage 
of IS pin and calculates current on output.

**The demo application is composed of two sections :**

### Application Init

> Initialization of the communication modules(ADC and UART) 
and additional pins for controlling the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    profet15a_cfg_t profet15a_cfg;  /**< Click config object. */

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
    profet15a_cfg_setup( &profet15a_cfg );
    PROFET15A_MAP_MIKROBUS( profet15a_cfg, MIKROBUS_1 );
    if ( profet15a_init( &profet15a, &profet15a_cfg ) == ADC_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    profet15a_set_mode( &profet15a, PROFET15A_DIAGNOSTIC_ON );
    Delay_ms ( 1000 );
}

```

### Application Task

> On every iteration of the task device switches between 
DIAGNOSTIC and OFF mode while it reads the voltage of IS pin 
and with that calculates current on output.

```c

void application_task ( void )
{
    static uint8_t mode = PROFET15A_DIAGNOSTIC_ON;
    float profet15a_an_voltage = 0;
    
    profet15a_set_mode( &profet15a, mode );
    
    if ( PROFET15A_DIAGNOSTIC_ON == profet15a.mode )
    {
        mode = PROFET15A_MODE_OFF;
        log_printf( &logger, " > Output ON diagnostic mode\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        mode = PROFET15A_DIAGNOSTIC_ON;
        log_printf( &logger, " > Output OFF\r\n" );
    }

    if ( profet15a_read_an_pin_voltage ( &profet15a, &profet15a_an_voltage ) != ADC_ERROR )
    {
        log_printf( &logger, " > IS Voltage \t~ %.3f[V]\r\n", profet15a_an_voltage );
        
        float current = profet15a_an_voltage * profet15a.kilis / profet15a.rsens;
        log_printf( &logger, " > OUT Current \t~ %.3f[A]\r\n", current );
    }  
    
    log_printf( &logger, "*******************************************\r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Formula for calculating current on load: 
I_load = voltage(IS) x kILIS / 1.2 kΩ

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PROFET15A

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
