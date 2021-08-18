
---
# Hall Switch 2 click

Hall Switch 2 Click is a compact add-on board that represents a magnetic field-activated dual-relay Click board™. This board features the MHA100KN, a high-performance, low-power Hall-Effect sensor from MEMSIC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hall_switch_2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-switch-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the HallSwitch2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallSwitch2 Click driver.

#### Standard key functions :

- `hallswitch2_cfg_setup` Config Object Initialization function.
```c
void hallswitch2_cfg_setup ( hallswitch2_cfg_t *cfg );
```

- `hallswitch2_init` Initialization function.
```c
err_t hallswitch2_init ( hallswitch2_t *ctx, hallswitch2_cfg_t *cfg );
```

#### Example key functions :

- `hallswitch2_check_state` This function checks the S and N pin states, which indicates a magnetic field poles.
```c
uint8_t hallswitch2_check_state ( hallswitch2_t *ctx );
```

## Example Description

> This example demonstrates the use of Hall Switch 2 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    hallswitch2_cfg_t hallswitch2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallswitch2_cfg_setup( &hallswitch2_cfg );
    HALLSWITCH2_MAP_MIKROBUS( hallswitch2_cfg, MIKROBUS_1 );
    if ( hallswitch2_init( &hallswitch2, &hallswitch2_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Displays the corresponding message on the USB UART based on the switches state, i.e. based on the magnetic field presence.

```c

void application_task ( void )
{
    switch ( hallswitch2_check_state( &hallswitch2 ) )
    {
        case HALLSWITCH2_NO_MAGNET_DETECTED:
        {
            if ( HALLSWITCH2_NO_MAGNET_DETECTED != print_state )
            {
                log_printf( &logger, " No magnet detected\r\n" );
                log_printf( &logger, " Switches - disabled\r\n\r\n" );
                print_state = HALLSWITCH2_NO_MAGNET_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_S_POLE_DETECTED:
        {
            if ( HALLSWITCH2_S_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " South pole detected\r\n" );
                log_printf( &logger, " Switch 1 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_S_POLE_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_N_POLE_DETECTED:
        {
            if ( HALLSWITCH2_N_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " North pole detected\r\n" );
                log_printf( &logger, " Switch 2 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_N_POLE_DETECTED;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
