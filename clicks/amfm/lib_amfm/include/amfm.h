/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for AMFM Click driver.
 *
 * \addtogroup amfm AMFM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMFM_H
#define AMFM_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AMFM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.gp1  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sen  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gp2  = MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.shd  = MIKROBUS( mikrobus, MIKROBUS_PWM);
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMFM_OK                                         0
#define AMFM_ERROR                                     -1
/** \} */

/**
 * \defgroup device_address Device Address
 * \{
 */
#define AMFM_DEVICE_ADDRESS                             0x11
/** \} */

/**
 * \defgroup commands_amfm Commands AMFM
 * \{
 */
#define AMFM_CMD_PWRUP                                  0x01
#define AMFM_CMD_GETREV                                 0x10
#define AMFM_CMD_PWRDOWN                                0x11
#define AMFM_CMD_SETPROP                                0x12
#define AMFM_CMD_GETPROP                                0x13
#define AMFM_CMD_GETINTSTATUS                           0x14
#define AMFM_CMD_PATCHARGS                              0x15
#define AMFM_CMD_PATCHDATA                              0x16
#define AMFM_CMD_GPIOCTL                                0x80
#define AMFM_CMD_GPIOSET                                0x81
/** \} */

/**
 * \defgroup commands_am Commands AM
 * \{
 */
#define AMFM_CMD_AMTUNEFREQ                             0x40
#define AMFM_CMD_AMSEEKSTART                            0x41
#define AMFM_CMD_AMTUNESTATUS                           0x42
#define AMFM_CMD_AMRSQSTATUS                            0x43
#define AMFM_CMD_AMAGCSTATUS                            0x47
#define AMFM_CMD_AMAGCOVERRIDE                          0x48
/** \} */

/**
 * \defgroup commands_fm Commands FM
 * \{
 */
#define AMFM_CMD_FMTUNEFREQ                             0x20
#define AMFM_CMD_FMSEEKSTART                            0x21
#define AMFM_CMD_FMTUNESTATUS                           0x22
#define AMFM_CMD_FMRSQSTATUS                            0x23
#define AMFM_CMD_FMRDSSTATUS                            0x24
#define AMFM_CMD_FMAGCSTATUS                            0x27
#define AMFM_CMD_FMAGCOVERRIDE                          0x28
/** \} */

/**
 * \defgroup arguments Arguments
 * \{
 */
#define AMFM_PWRUP_ARG1_CTSIEN                          0x80
#define AMFM_PWRUP_ARG1_GPO2OEN                         0x40
#define AMFM_PWRUP_ARG1_PATCH                           0x20
#define AMFM_PWRUP_ARG1_XOSCEN                          0x10
#define AMFM_PWRUP_ARG1_FUNC_FMRECEIVE                  0x00
#define AMFM_PWRUP_ARG1_FUNC_QUERYLIBID                 0x0F
#define AMFM_PWRUP_ARG2_OPMODE_ANALOGOUT                0x05
#define AMFM_PWRUP_ARG2_OPMODE_DIGITALOUT               0x0B
#define AMFM_PWRUP_ARG2_OPMODE_DIGITALOUTS              0xB0
#define AMFM_PWRUP_ARG2_OPMODE_ANALOGDIGITALOUTS        0xB5
#define AMFM_FMTUNEFREQ_ARG1_FREEZE                     0x02
#define AMFM_FMTUNEFREQ_ARG1_FAST                       0x01
#define AMFM_FMSEEKSTART_ARG1_SEEKUP                    0x08
#define AMFM_FMSEEKSTART_ARG1_WRAP                      0x04
#define AMFM_FMTUNESTATUS_ARG1_CANCEL                   0x02
#define AMFM_FMTUNESTATUS_ARG1_INTACK                   0x01
#define AMFM_FMRSQSTATUS_ARG1_INTACK                    0x01
#define AMFM_FMRDSSTATUS_ARG1_STATUSONLY                0x04
#define AMFM_FMRDSSTATUS_ARG1_MTFIFO                    0x02
#define AMFM_FMRDSSTATUS_ARG1_INTACK                    0x01
#define AMFM_FMAGCOVERRIDE_ARG1_RFAGCDIS                0x01
#define AMFM_GPIOCTL_ARG1_GPO3OEN                       0x08
#define AMFM_GPIOCTL_ARG1_GPO2OEN                       0x04
#define AMFM_GPIOCTL_ARG1_GPO1OEN                       0x02
#define AMFM_GPIOSET_ARG1_GPO3LEVEL                     0x08
#define AMFM_GPIOSET_ARG1_GPO2LEVEL                     0x04
#define AMFM_GPIOSET_ARG1_GPO1LEVEL                     0x02
/** \} */

/**
 * \defgroup properties_amfm Properties AMFM
 * \{
 */
#define AMFM_PROP_GPOIEN_H                              0x00
#define AMFM_PROP_GPOIEN_L                              0x01
#define AMFM_PROP_DIGITALOUTFORMAT_H                    0x01
#define AMFM_PROP_DIGITALOUTFORMAT_L                    0x02
#define AMFM_PROP_DIGITALOUTSAMPLERATE_H                0x01
#define AMFM_PROP_DIGITALOUTSAMPLERATE_L                0x04
#define AMFM_PROP_REFCLKFREQ_H                          0x02
#define AMFM_PROP_REFCLKFREQ_L                          0x01
#define AMFM_PROP_REFCLKPRESCALE_H                      0x02
#define AMFM_PROP_REFCLKPRESCALE_L                      0x02
#define AMFM_PROP_RXVOLUME_H                            0x40
#define AMFM_PROP_RXVOLUME_L                            0x00
#define AMFM_PROP_RXHMUTE_H                             0x40
#define AMFM_PROP_RXHMUTE_L                             0x01
/** \} */

/**
 * \defgroup properties_am Properties AM
 * \{
 */
#define AMFM_PROP_FMDEEMPHASIS_H                        0x11
#define AMFM_PROP_FMDEEMPHASIS_L                        0x00
#define AMFM_PROP_AMDEEMPHASIS_H                        0x31
#define AMFM_PROP_AMDEEMPHASIS_L                        0x00
#define AMFM_PROP_FMCHANFILTER_H                        0x11
#define AMFM_PROP_FMCHANFILTER_L                        0x02
#define AMFM_PROP_AMCHANFILTER_H                        0x31
#define AMFM_PROP_AMCHANFILTER_L                        0x02
#define AMFM_PROP_AMAUTOVOLCTRLMAXGAIN_H                0x31
#define AMFM_PROP_AMAUTOVOLCTRLMAXGAIN_L                0x03
#define AMFM_PROP_AMMODEAFCSWPULLINRANGE_H              0x31
#define AMFM_PROP_AMMODEAFCSWPULLINRANGE_L              0x04
#define AMFM_PROP_AMMODEAFCSWLOCKINRANGE_H              0x31
#define AMFM_PROP_AMMODEAFCSWLOCKINRANGE_L              0x05
#define AMFM_PROP_AMRSQINTS_H                           0x32
#define AMFM_PROP_AMRSQINTS_L                           0x00
#define AMFM_PROP_AMRSQSNRHITHS_H                       0x32
#define AMFM_PROP_AMRSQSNRHITHS_L                       0x01
#define AMFM_PROP_AMRSQSNRLOTHS_H                       0x32
#define AMFM_PROP_AMRSQSNRLOTHS_L                       0x02
#define AMFM_PROP_AMRSQRSSIHITHS_H                      0x32
#define AMFM_PROP_AMRSQRSSIHITHS_L                      0x03
#define AMFM_PROP_AMRSQRSSILOTHS_H                      0x32
#define AMFM_PROP_AMRSQRSSILOTHS_L                      0x04
#define AMFM_PROP_AMSMUTERATE_H                         0x33
#define AMFM_PROP_AMSMUTERATE_L                         0x00
#define AMFM_PROP_AMSMUTESLOPE_H                        0x33
#define AMFM_PROP_AMSMUTESLOPE_L                        0x01
#define AMFM_PROP_AMSMUTEMAXATTENUATION_H               0x33
#define AMFM_PROP_AMSMUTEMAXATTENUATION_L               0x02
#define AMFM_PROP_AMSMUTESNRTHS_H                       0x33
#define AMFM_PROP_AMSMUTESNRTHS_L                       0x03
#define AMFM_PROP_AMSMUTERELEASERATE_H                  0x33
#define AMFM_PROP_AMSMUTERELEASERATE_L                  0x04
#define AMFM_PROP_AMSMUTEATTACKRATE_H                   0x33
#define AMFM_PROP_AMSMUTEATTACKRATE_L                   0x05
#define AMFM_PROP_AMSEEKBANDBOT_H                       0x34
#define AMFM_PROP_AMSEEKBANDBOT_L                       0x00
#define AMFM_PROP_AMSEEKBANDTOP_H                       0x34
#define AMFM_PROP_AMSEEKBANDTOP_L                       0x01
#define AMFM_PROP_AMSEEKFREQSPACING_H                   0x34
#define AMFM_PROP_AMSEEKFREQSPACING_L                   0x02
#define AMFM_PROP_AMSEEKTUNESNRTHS_H                    0x34
#define AMFM_PROP_AMSEEKTUNESNRTHS_L                    0x03
#define AMFM_PROP_AMSEEKTUNERSSITHS_H                   0x34
#define AMFM_PROP_AMSEEKTUNERSSITHS_L                   0x04
#define AMFM_PROP_AMAGCATTACKRATE_H                     0x37
#define AMFM_PROP_AMAGCATTACKRATE_L                     0x02
#define AMFM_PROP_AMAGCRELEASERATE_H                    0x37
#define AMFM_PROP_AMAGCRELEASERATE_L                    0x03
#define AMFM_PROP_AMFRONTENDAGCCTRL_H                   0x37
#define AMFM_PROP_AMFRONTENDAGCCTRL_L                   0x05
#define AMFM_PROP_AMNBDETECTTHS_H                       0x39
#define AMFM_PROP_AMNBDETECTTHS_L                       0x00
#define AMFM_PROP_AMNBINTERVAL_H                        0x39
#define AMFM_PROP_AMNBINTERVAL_L                        0x01
#define AMFM_PROP_AMNBRATE_H                            0x39
#define AMFM_PROP_AMNBRATE_L                            0x02
#define AMFM_PROP_AMNBIIRFILTER_H                       0x39
#define AMFM_PROP_AMNBIIRFILTER_L                       0x03
#define AMFM_PROP_AMNBDELAY_H                           0x39
#define AMFM_PROP_AMNBDELAY_L                           0x04
/** \} */

/**
 * \defgroup properties_fm Properties FM
 * \{
 */
#define AMFM_PROP_FMBLENDSTEREOTHS_H                    0x11
#define AMFM_PROP_FMBLENDSTEREOTHS_L                    0x05
#define AMFM_PROP_FMBLENDMONOTHS_H                      0x11
#define AMFM_PROP_FMBLENDMONOTHS_L                      0x06
#define AMFM_PROP_FMANTENNAIN_H                         0x11
#define AMFM_PROP_FMANTENNAIN_L                         0x07
#define AMFM_PROP_FMMAXTUNEERR_H                        0x11
#define AMFM_PROP_FMMAXTUNEERR_L                        0x08
#define AMFM_PROP_FMRSQINTSRC_H                         0x12
#define AMFM_PROP_FMRSQINTSRC_L                         0x00
#define AMFM_PROP_FMRSQSNRHITHS_H                       0x12
#define AMFM_PROP_FMRSQSNRHITHS_L                       0x01
#define AMFM_PROP_FMRSQSNRLOTHS_H                       0x12
#define AMFM_PROP_FMRSQSNRLOTHS_L                       0x02
#define AMFM_PROP_FMRSQRSSIHITHS_H                      0x12
#define AMFM_PROP_FMRSQRSSIHITHS_L                      0x03
#define AMFM_PROP_FMRSQRSSILOTHS_H                      0x12
#define AMFM_PROP_FMRSQRSSILOTHS_L                      0x04
#define AMFM_PROP_FMRSQMULTIPATHHITHS_H                 0x12
#define AMFM_PROP_FMRSQMULTIPATHHITHS_L                 0x05
#define AMFM_PROP_FMRSQMULTIPATHLOTHS_H                 0x12
#define AMFM_PROP_FMRSQMULTIPATHLOTHS_L                 0x06
#define AMFM_PROP_FMRSQBLENDTHS_H                       0x12
#define AMFM_PROP_FMRSQBLENDTHS_L                       0x07
#define AMFM_PROP_FMSMUTERATE_H                         0x13
#define AMFM_PROP_FMSMUTERATE_L                         0x00
#define AMFM_PROP_FMSMUTESLOPE_H                        0x13
#define AMFM_PROP_FMSMUTESLOPE_L                        0x01
#define AMFM_PROP_FMSMUTEMAXATTENUATION_H               0x13
#define AMFM_PROP_FMSMUTEMAXATTENUATION_L               0x02
#define AMFM_PROP_FMSMUTESNRTHS_H                       0x13
#define AMFM_PROP_FMSMUTESNRTHS_L                       0x03
#define AMFM_PROP_FMSMUTERELEASERATE_H                  0x13
#define AMFM_PROP_FMSMUTERELEASERATE_L                  0x04
#define AMFM_PROP_FMSMUTEATTACKRATE_H                   0x13
#define AMFM_PROP_FMSMUTEATTACKRATE_L                   0x05
#define AMFM_PROP_FMSEEKBANDBOT_H                       0x14
#define AMFM_PROP_FMSEEKBANDBOT_L                       0x00
#define AMFM_PROP_FMSEEKBANDTOP_H                       0x14
#define AMFM_PROP_FMSEEKBANDTOP_L                       0x01
#define AMFM_PROP_FMSEEKFREQSPACING_H                   0x14
#define AMFM_PROP_FMSEEKFREQSPACING_L                   0x02
#define AMFM_PROP_FMSEEKTUNESNRTHS_H                    0x14
#define AMFM_PROP_FMSEEKTUNESNRTHS_L                    0x03
#define AMFM_PROP_FMSEEKTUNERSSITHS_H                   0x14
#define AMFM_PROP_FMSEEKTUNERSSITHS_L                   0x04
#define AMFM_PROP_FMRDSINTSRC_H                         0x15
#define AMFM_PROP_FMRDSINTSRC_L                         0x00
#define AMFM_PROP_FMRDSINTFIFOCOUNT_H                   0x15
#define AMFM_PROP_FMRDSINTFIFOCOUNT_L                   0x01
#define AMFM_PROP_FMRDSCFG_H                            0x15
#define AMFM_PROP_FMRDSCFG_L                            0x02
#define AMFM_PROP_FMRDSCONFIDENCE_H                     0x15
#define AMFM_PROP_FMRDSCONFIDENCE_L                     0x03
#define AMFM_PROP_FMAGCATTACKRATE_H                     0x17
#define AMFM_PROP_FMAGCATTACKRATE_L                     0x00
#define AMFM_PROP_FMAGCRELEASERATE_H                    0x17
#define AMFM_PROP_FMAGCRELEASERATE_L                    0x01
#define AMFM_PROP_FMBLENDRSSISTEREOTHS_H                0x18
#define AMFM_PROP_FMBLENDRSSISTEREOTHS_L                0x00
#define AMFM_PROP_FMBLENDRSSIMONOTHS_H                  0x18
#define AMFM_PROP_FMBLENDRSSIMONOTHS_L                  0x01
#define AMFM_PROP_FMBLENDRSSIATTACKRATE_H               0x18
#define AMFM_PROP_FMBLENDRSSIATTACKRATE_L               0x02
#define AMFM_PROP_FMBLENDRSSIRELEASERATE_H              0x18
#define AMFM_PROP_FMBLENDRSSIRELEASERATE_L              0x03
#define AMFM_PROP_FMBLENDSNRSTEREOTHS_H                 0x18
#define AMFM_PROP_FMBLENDSNRSTEREOTHS_L                 0x04
#define AMFM_PROP_FMBLENDSNRMONOTHS_H                   0x18
#define AMFM_PROP_FMBLENDSNRMONOTHS_L                   0x05
#define AMFM_PROP_FMBLENDSNRATTACKRATE_H                0x18
#define AMFM_PROP_FMBLENDSNRATTACKRATE_L                0x06
#define AMFM_PROP_FMBLENDSNRRELEASERATE_H               0x18
#define AMFM_PROP_FMBLENDSNRRELEASERATE_L               0x07
#define AMFM_PROP_FMBLENDMULTIPATHSTEREOTHS_H           0x18
#define AMFM_PROP_FMBLENDMULTIPATHSTEREOTHS_L           0x08
#define AMFM_PROP_FMBLENDMULTIPATHMONOTHS_H             0x18
#define AMFM_PROP_FMBLENDMULTIPATHMONOTHS_L             0x09
#define AMFM_PROP_FMBLENDMULTIPATHATTACKRATE_H          0x18
#define AMFM_PROP_FMBLENDMULTIPATHATTACKRATE_L          0x0A
#define AMFM_PROP_FMBLENDMULTIPATHRELEASERATE_H         0x18
#define AMFM_PROP_FMBLENDMULTIPATHRELEASERATE_L         0x0B
#define AMFM_PROP_FMBLENDMAXSTEREOSEPARATION_H          0x18
#define AMFM_PROP_FMBLENDMAXSTEREOSEPARATION_L          0x0C
#define AMFM_PROP_FMNBDETECTTHS_H                       0x19
#define AMFM_PROP_FMNBDETECTTHS_L                       0x00
#define AMFM_PROP_FMNBINTERVAL_H                        0x19
#define AMFM_PROP_FMNBINTERVAL_L                        0x01
#define AMFM_PROP_FMNBRATE_H                            0x19
#define AMFM_PROP_FMNBRATE_L                            0x02
#define AMFM_PROP_FMNBIIRFILTER_H                       0x19
#define AMFM_PROP_FMNBIIRFILTER_L                       0x03
#define AMFM_PROP_FMNBDELAY_H                           0x19
#define AMFM_PROP_FMNBDELAY_L                           0x04
#define AMFM_PROP_FMHICUTSNRHITHS_H                     0x1A
#define AMFM_PROP_FMHICUTSNRHITHS_L                     0x00
#define AMFM_PROP_FMHICUTSNRLOTHS_H                     0x1A
#define AMFM_PROP_FMHICUTSNRLOTHS_L                     0x01
#define AMFM_PROP_FMHICUTATTACKRATE_H                   0x1A
#define AMFM_PROP_FMHICUTATTACKRATE_L                   0x02
#define AMFM_PROP_FMHICUTRELEASERATE_H                  0x1A
#define AMFM_PROP_FMHICUTRELEASERATE_L                  0x03
#define AMFM_PROP_FMHICUTMULTIPATHTRIGGERTHRESHOLD_H    0x1A
#define AMFM_PROP_FMHICUTMULTIPATHTRIGGERTHRESHOLD_L    0x04
#define AMFM_PROP_FMHICUTMULTIPATHENDTHS_H              0x1A
#define AMFM_PROP_FMHICUTMULTIPATHENDTHS_L              0x05
#define AMFM_PROP_FMHICUTCUTOFFFREQ_H                   0x1A
#define AMFM_PROP_FMHICUTCUTOFFFREQ_L                   0x06
/** \} */

/**
 * \defgroup property_values Property Values
 * \{
 */
#define AMFM_PROPVALH_RSQREP                            0x08
#define AMFM_PROPVALH_RDSREP                            0x04
#define AMFM_PROPVALH_STCREP                            0x01
#define AMFM_PROPVALL_CTSIEN                            0x80
#define AMFM_PROPVALL_ERRIEN                            0x40
#define AMFM_PROPVALL_RSQIEN                            0x08
#define AMFM_PROPVALL_RDSIEN                            0x04
#define AMFM_PROPVALL_STCIEN                            0x01
#define AMFM_PROPVALL_OFALL                             0x80
#define AMFM_PROPVALL_OMODE_I2S                         0x00
#define AMFM_PROPVALL_OMODE_LEFTJUST                    0x30
#define AMFM_PROPVALL_OMODE_MSBATSECONDDCLK             0x40
#define AMFM_PROPVALL_OMODE_MSBATFIRSTDCLK              0x60
#define AMFM_PROPVALL_OMONO                             0x04
#define AMFM_PROPVALL_OSIZE_16b                         0x00
#define AMFM_PROPVALL_OSIZE_20b                         0x01
#define AMFM_PROPVALL_OSIZE_24b                         0x02
#define AMFM_PROPVALL_OSIZE_08b                         0x03
#define AMFM_PROPVALL_DEEMPH_75uS                       0x02
#define AMFM_PROPVALL_DEEMPH_50uS                       0x01
#define AMFM_PROPVALL_AUTO                              0x00
#define AMFM_PROPVALL_WIDE                              0x01
#define AMFM_PROPVALL_NARROW                            0x02
#define AMFM_PROPVALL_NARROWER                          0x03
#define AMFM_PROPVALL_NARROWEST                         0x04
#define AMFM_PROPVALL_FMTXO                             0x01
#define AMFM_PROPVALL_BLENDIEN                          0x80
#define AMFM_PROPVALL_MULTHIEN                          0x20
#define AMFM_PROPVALL_MULTLIEN                          0x10
#define AMFM_PROPVALL_SNRHIEN                           0x08
#define AMFM_PROPVALL_SNRLIEN                           0x04
#define AMFM_PROPVALL_RSSIHIEN                          0x02
#define AMFM_PROPVALL_RSSILIEN                          0x01
#define AMFM_PROPVALL_RDSNEWBLOCKB                      0x20
#define AMFM_PROPVALL_RDSNEWBLOCKA                      0x10
#define AMFM_PROPVALL_RDSSYNCFOUND                      0x04
#define AMFM_PROPVALL_RDSSYNCLOST                       0x02
#define AMFM_PROPVALL_RDSRECV                           0x01
#define AMFM_PROPVALH_BLETHA_NOERRORS                   0x00
#define AMFM_PROPVALH_BLETHA_1TO2ERRORS                 0x40
#define AMFM_PROPVALH_BLETHA_3TO5ERRORS                 0x80
#define AMFM_PROPVALH_BLETHA_UNCORRECTABLE              0xC0
#define AMFM_PROPVALH_BLETHB_NOERRORS                   0x00
#define AMFM_PROPVALH_BLETHB_1TO2ERRORS                 0x10
#define AMFM_PROPVALH_BLETHB_3TO5ERRORS                 0x20
#define AMFM_PROPVALH_BLETHB_UNCORRECTABLE              0x30
#define AMFM_PROPVALH_BLETHC_NOERRORS                   0x00
#define AMFM_PROPVALH_BLETHC_1TO2ERRORS                 0x04
#define AMFM_PROPVALH_BLETHC_3TO5ERRORS                 0x08
#define AMFM_PROPVALH_BLETHC_UNCORRECTABLE              0x0C
#define AMFM_PROPVALH_BLETHD_NOERRORS                   0x00
#define AMFM_PROPVALH_BLETHD_1TO2ERRORS                 0x01
#define AMFM_PROPVALH_BLETHD_3TO5ERRORS                 0x02
#define AMFM_PROPVALH_BLETHD_UNCORRECTABLE              0x03
#define AMFM_PROPVALL_RDSEN                             0x01
#define AMFM_PROPVALL_MAXAUDIOFREQ_MAX                  0x00
#define AMFM_PROPVALL_MAXAUDIOFREQ_2                    0x10
#define AMFM_PROPVALL_MAXAUDIOFREQ_3                    0x20
#define AMFM_PROPVALL_MAXAUDIOFREQ_4                    0x30
#define AMFM_PROPVALL_MAXAUDIOFREQ_5                    0x40
#define AMFM_PROPVALL_MAXAUDIOFREQ_6                    0x50
#define AMFM_PROPVALL_MAXAUDIOFREQ_8                    0x60
#define AMFM_PROPVALL_MAXAUDIOFREQ_11                   0x70
#define AMFM_PROPVALL_HICUTTRANSFREQ_DISABLED           0x00
#define AMFM_PROPVALL_HICUTTRANSFREQ_2                  0x01
#define AMFM_PROPVALL_HICUTTRANSFREQ_3                  0x02
#define AMFM_PROPVALL_HICUTTRANSFREQ_4                  0x03
#define AMFM_PROPVALL_HICUTTRANSFREQ_5                  0x04
#define AMFM_PROPVALL_HICUTTRANSFREQ_6                  0x05
#define AMFM_PROPVALL_HICUTTRANSFREQ_8                  0x06
#define AMFM_PROPVALL_HICUTTRANSFREQ_11                 0x07
#define AMFM_PROPVALL_LMUTE                             0x02
#define AMFM_PROPVALL_RMUTE                             0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t rst;
    digital_out_t sen;
    digital_out_t shd;

    // Input pins 
    digital_in_t gp1;
    digital_in_t gp2;
    
    pin_name_t gp1_pin;
    pin_name_t gp2_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;
    uint8_t command_and_arguments_buffer[ 6 ];
    uint16_t aux_variable;
    uint8_t response_buffer[ 8 ];
    uint8_t n_bytes;

} amfm_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t gp1;
    pin_name_t rst;
    pin_name_t sen;
    pin_name_t gp2;
    pin_name_t shd;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} amfm_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void amfm_cfg_setup ( amfm_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
err_t amfm_init ( amfm_t *ctx, amfm_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AmFm Click.
 */
void amfm_default_cfg ( amfm_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void amfm_generic_write ( amfm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void amfm_generic_read ( amfm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for checking AN pin state.
 *
 * @param ctx          Click object.
 *
 * @description This function returns AN pin state.
 */
uint8_t amfm_an_get ( amfm_t *ctx );

/**
 * @brief Function for checking INT pin state.
 *
 * @param ctx          Click object.
 *
 * @description This function returns INT pin state.
 */
uint8_t amfm_int_get ( amfm_t *ctx );

/**
 * @brief Function for setting RST pin state.
 *
 * @param ctx          Click object.
 * @param pin_state    Pin state ( 0 or 1 ).
 *
 * @description This function sets RST pin state.
 */
void amfm_rst_set ( amfm_t *ctx, uint8_t pin_state );

/**
 * @brief Function for setting CS pin state.
 *
 * @param ctx          Click object.
 * @param pin_state    Pin state ( 0 or 1 ).
 *
 * @description This function sets CS pin state.
 */
void amfm_cs_set ( amfm_t *ctx, uint8_t pin_state );

/**
 * @brief Function for sending command and command arguments to device.
 *
 * @param ctx                 Click object.
 * @param cmd_and_args_buf    Pointer to buffer that contains command and command arguments to send.
 *
 * @description This function sends command and command arguments to device.
 */
uint8_t amfm_send_command ( amfm_t *ctx, uint8_t *cmd_and_args_buf );

/**
 * @brief Function for checking CTS bit.
 *
 * @param ctx          Click object.
 *
 * @description This function checks CTS bit state.
 */
uint8_t amfm_get_cts ( amfm_t *ctx );

/**
 * @brief Function for checking STC bit.
 *
 * @param ctx          Click object.
 *
 * @description This function checks STC bit state.
 */
uint8_t amfm_get_stc ( amfm_t *ctx );

/**
 * @brief Function for checking RSQ bit.
 *
 * @param ctx          Click object.
 *
 * @description This function checks RSQ bit state.
 */
uint8_t amfm_get_rsq ( amfm_t *ctx );

/**
 * @brief Function for checking RDS bit.
 *
 * @param ctx          Click object.
 *
 * @description This function checks RDS bit state.
 */
uint8_t amfm_get_rds ( amfm_t *ctx );

/**
 * @brief Function for getting device response.
 *
 * @param ctx          Click object.
 * @param resp_buf     Buffer to wich the response bytes will be stored.
 * @param n_bytes      Number of response bytes.
 *
 * @description This function returns a device response into a resp_buf.
 */
uint8_t amfm_get_response ( amfm_t *ctx, uint8_t *resp_buf, uint8_t n_bytes );

/**
 * @brief Device initialization.
 *
 * @param ctx          Click object.
 *
 * @description This function returns 0 for succesful initialization of a device 
 * and returns 1 for unsucessful initialization of a device.
 */
uint8_t amfm_init_device ( amfm_t *ctx );

/**
 * @brief Function for seeking next station.
 *
 * @param ctx          Click object.
 *
 * @description This function returns 0 for succesful seek
 * and returns 1 for unsucessful seek.
 */
uint8_t amfm_seek ( amfm_t *ctx );

/**
 * @brief Function for setting volume level.
 *
 * @param ctx        Click object.
 * @param volume     volume level ( range: 0 - 63 ).
 *
 * @description This function sets volume level in range: 0 - 63.
 */
uint8_t amfm_set_volume ( amfm_t *ctx, uint8_t volume );

/**
 * @brief Function for muting device.
 *
 * @param ctx          Click object.
 *
 * @description This function returns 0 for succesful mute
 * and returns 1 for unsuccesful mute.
 */
uint8_t amfm_mute ( amfm_t *ctx );

/**
 * @brief Function for unmuting device.
 *
 * @param ctx          Click object.
 *
 * @description This function returns 0 for succesful unmute
 * and returns 1 for unsuccesful unmute.
 */
uint8_t amfm_unmute ( amfm_t *ctx );

/**
 * @brief Function for tune up current frequency.
 *
 * @param ctx          Click object.
 *
 * @description This function increments current frequency for 10 KHz.
 */
uint8_t amfm_tune_up ( amfm_t *ctx );

/**
 * @brief Function for tune down current frequency.
 *
 * @param ctx          Click object.
 *
 * @description This function decrements current frequency for 10 KHz.
 */
uint8_t amfm_tune_down ( amfm_t *ctx );

/**
 * @brief Function for tuning frequency.
 *
 * @param ctx          Click object.
 * @param frequency    Frequency value to be tuned ( frequency value in KHz ).
 *
 * @description This function tunes desired frequency value.
 */
uint8_t amfm_tune_frequency ( amfm_t *ctx, uint16_t frequency );

/**
 * @brief Function for getting current channel value.
 *
 * @param ctx          Click object.
 *
 * @description This function returns current channel value in KHz.
 */
uint16_t amfm_get_channel ( amfm_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMFM_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
