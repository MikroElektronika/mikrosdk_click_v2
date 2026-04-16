/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file lifemetrics.h
 * @brief This file contains API for Life Metrics Click Driver.
 */

#ifndef LIFEMETRICS_H
#define LIFEMETRICS_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup lifemetrics Life Metrics Click Driver
 * @brief API for configuring and manipulating Life Metrics Click driver.
 * @{
 */

/**
 * @defgroup lifemetrics_reg Life Metrics Registers List
 * @brief List of registers of Life Metrics Click driver.
 */

/**
 * @addtogroup lifemetrics_reg
 * @{
 */

/**
 * @brief Life Metrics AS7058A AFE register list.
 * @details Specified register list for AS7058A AFE of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_REG_OTP_BIOZ_REF_L              0x0E   
#define LIFEMETRICS_AFE_REG_OTP_BIOZ_REF_H              0x0F   
#define LIFEMETRICS_AFE_REG_OTP_GSR_REF_L               0x13    
#define LIFEMETRICS_AFE_REG_OTP_GSR_REF_H               0x14    
#define LIFEMETRICS_AFE_REG_OTP_TEMP_REF_L              0x15   
#define LIFEMETRICS_AFE_REG_OTP_TEMP_REF_H              0x16   
#define LIFEMETRICS_AFE_REG_CLK_CFG                     0x18          
#define LIFEMETRICS_AFE_REG_REF_CFG1                    0x19         
#define LIFEMETRICS_AFE_REG_REF_CFG2                    0x1A         
#define LIFEMETRICS_AFE_REG_REF_CFG3                    0x1B         
#define LIFEMETRICS_AFE_REG_STANDBY_ON1                 0x1C      
#define LIFEMETRICS_AFE_REG_STANDBY_ON2                 0x1D      
#define LIFEMETRICS_AFE_REG_STANDBY_EN1                 0x1E      
#define LIFEMETRICS_AFE_REG_STANDBY_EN2                 0x1F      
#define LIFEMETRICS_AFE_REG_STANDBY_EN3                 0x20      
#define LIFEMETRICS_AFE_REG_STANDBY_EN4                 0x21      
#define LIFEMETRICS_AFE_REG_STANDBY_EN5                 0x22      
#define LIFEMETRICS_AFE_REG_STANDBY_EN6                 0x23      
#define LIFEMETRICS_AFE_REG_STANDBY_EN7                 0x24      
#define LIFEMETRICS_AFE_REG_STANDBY_EN8                 0x25      
#define LIFEMETRICS_AFE_REG_STANDBY_EN9                 0x26      
#define LIFEMETRICS_AFE_REG_STANDBY_EN10                0x27     
#define LIFEMETRICS_AFE_REG_STANDBY_EN11                0x28     
#define LIFEMETRICS_AFE_REG_STANDBY_EN12                0x29     
#define LIFEMETRICS_AFE_REG_STANDBY_EN13                0x2A     
#define LIFEMETRICS_AFE_REG_STANDBY_EN14                0x2B     
#define LIFEMETRICS_AFE_REG_PWR_ON                      0x2D           
#define LIFEMETRICS_AFE_REG_PWR_ISO                     0x2E          
#define LIFEMETRICS_AFE_REG_PWR_STAT                    0x2F         
#define LIFEMETRICS_AFE_REG_I2C_MODE                    0x31         
#define LIFEMETRICS_AFE_REG_INT_CFG                     0x32          
#define LIFEMETRICS_AFE_REG_IF_CFG                      0x33           
#define LIFEMETRICS_AFE_REG_GPIO_CFG1                   0x34        
#define LIFEMETRICS_AFE_REG_GPIO_CFG2                   0x35        
#define LIFEMETRICS_AFE_REG_IO_CFG                      0x36           
#define LIFEMETRICS_AFE_REG_PPGMOD_CFG1                 0x37      
#define LIFEMETRICS_AFE_REG_PPGMOD_CFG2                 0x38      
#define LIFEMETRICS_AFE_REG_PPGMOD_CFG3                 0x39      
#define LIFEMETRICS_AFE_REG_PPGMOD1_CFG1                0x3A     
#define LIFEMETRICS_AFE_REG_PPGMOD1_CFG2                0x3B     
#define LIFEMETRICS_AFE_REG_PPGMOD1_CFG3                0x3C     
#define LIFEMETRICS_AFE_REG_PPGMOD2_CFG1                0x3D     
#define LIFEMETRICS_AFE_REG_PPGMOD2_CFG2                0x3E     
#define LIFEMETRICS_AFE_REG_PPGMOD2_CFG3                0x3F     
#define LIFEMETRICS_AFE_REG_VCSEL_PASSWORD              0x40   
#define LIFEMETRICS_AFE_REG_VCSEL_CFG                   0x41        
#define LIFEMETRICS_AFE_REG_VCSEL_MODE                  0x42       
#define LIFEMETRICS_AFE_REG_LED_CFG                     0x43          
#define LIFEMETRICS_AFE_REG_LED_DRV1                    0x44         
#define LIFEMETRICS_AFE_REG_LED_DRV2                    0x45         
#define LIFEMETRICS_AFE_REG_LED1_ICTRL                  0x46       
#define LIFEMETRICS_AFE_REG_LED2_ICTRL                  0x47       
#define LIFEMETRICS_AFE_REG_LED3_ICTRL                  0x48       
#define LIFEMETRICS_AFE_REG_LED4_ICTRL                  0x49       
#define LIFEMETRICS_AFE_REG_LED5_ICTRL                  0x4A       
#define LIFEMETRICS_AFE_REG_LED6_ICTRL                  0x4B       
#define LIFEMETRICS_AFE_REG_LED7_ICTRL                  0x4C       
#define LIFEMETRICS_AFE_REG_LED8_ICTRL                  0x4D       
#define LIFEMETRICS_AFE_REG_LED_IRNG1                   0x4E        
#define LIFEMETRICS_AFE_REG_LED_IRNG2                   0x4F        
#define LIFEMETRICS_AFE_REG_LED_SUB1                    0x50         
#define LIFEMETRICS_AFE_REG_LED_SUB2                    0x51         
#define LIFEMETRICS_AFE_REG_LED_SUB3                    0x52         
#define LIFEMETRICS_AFE_REG_LED_SUB4                    0x53         
#define LIFEMETRICS_AFE_REG_LED_SUB5                    0x54         
#define LIFEMETRICS_AFE_REG_LED_SUB6                    0x55         
#define LIFEMETRICS_AFE_REG_LED_SUB7                    0x56         
#define LIFEMETRICS_AFE_REG_LED_SUB8                    0x57         
#define LIFEMETRICS_AFE_REG_LOWVDS_WAIT                 0x58      
#define LIFEMETRICS_AFE_REG_PDSEL_CFG                   0x59        
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL1                 0x5A      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL2                 0x5B      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL3                 0x5C      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL4                 0x5D      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL5                 0x5E      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL6                 0x5F      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL7                 0x60      
#define LIFEMETRICS_AFE_REG_PPG1_PDSEL8                 0x61      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL1                 0x62      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL2                 0x63      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL3                 0x64      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL4                 0x65      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL5                 0x66      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL6                 0x67      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL7                 0x68      
#define LIFEMETRICS_AFE_REG_PPG2_PDSEL8                 0x69      
#define LIFEMETRICS_AFE_REG_PPG2_AFESEL1                0x6A     
#define LIFEMETRICS_AFE_REG_PPG2_AFESEL2                0x6B     
#define LIFEMETRICS_AFE_REG_PPG2_AFESEL3                0x6C     
#define LIFEMETRICS_AFE_REG_PPG2_AFESEL4                0x6D     
#define LIFEMETRICS_AFE_REG_PPG2_AFEEN                  0x6E       
#define LIFEMETRICS_AFE_REG_PPG_SINC_CFGA               0x6F    
#define LIFEMETRICS_AFE_REG_PPG_SINC_CFGB               0x70    
#define LIFEMETRICS_AFE_REG_PPG_SINC_CFGC               0x71    
#define LIFEMETRICS_AFE_REG_PPG_SINC_CFGD               0x72    
#define LIFEMETRICS_AFE_REG_ECG1_SINC_CFGA              0x73   
#define LIFEMETRICS_AFE_REG_ECG1_SINC_CFGB              0x74   
#define LIFEMETRICS_AFE_REG_ECG1_SINC_CFGC              0x75   
#define LIFEMETRICS_AFE_REG_ECG2_SINC_CFGA              0x76   
#define LIFEMETRICS_AFE_REG_ECG2_SINC_CFGB              0x77   
#define LIFEMETRICS_AFE_REG_ECG2_SINC_CFGC              0x78   
#define LIFEMETRICS_AFE_REG_ECG_SINC_CFG                0x79     
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB1               0x7A    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB2               0x7B    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB3               0x7C    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB4               0x7D    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB5               0x7E    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB6               0x7F    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB7               0x80    
#define LIFEMETRICS_AFE_REG_IOS_PPG1_SUB8               0x81    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB1               0x82    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB2               0x83    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB3               0x84    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB4               0x85    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB5               0x86    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB6               0x87    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB7               0x88    
#define LIFEMETRICS_AFE_REG_IOS_PPG2_SUB8               0x89    
#define LIFEMETRICS_AFE_REG_IOS_LEDOFF                  0x8A       
#define LIFEMETRICS_AFE_REG_IOS_CFG                     0x8B          
#define LIFEMETRICS_AFE_REG_AOC_SAR_THRES               0x8C    
#define LIFEMETRICS_AFE_REG_AOC_SAR_RANGE               0x8D    
#define LIFEMETRICS_AFE_REG_AOC_SAR_PPG1                0x8E     
#define LIFEMETRICS_AFE_REG_AOC_SAR_PPG2                0x8F     
#define LIFEMETRICS_AFE_REG_PP_CFG                      0x90           
#define LIFEMETRICS_AFE_REG_PPG1_PP1                    0x91         
#define LIFEMETRICS_AFE_REG_PPG1_PP2                    0x92         
#define LIFEMETRICS_AFE_REG_PPG2_PP1                    0x93         
#define LIFEMETRICS_AFE_REG_PPG2_PP2                    0x94         
#define LIFEMETRICS_AFE_REG_IRQ_ENABLE                  0x95       
#define LIFEMETRICS_AFE_REG_PPG_SUB_WAIT                0x96     
#define LIFEMETRICS_AFE_REG_PPG_SAR_WAIT                0x97     
#define LIFEMETRICS_AFE_REG_PPG_LED_INIT                0x98     
#define LIFEMETRICS_AFE_REG_PPG_FREQL                   0x99        
#define LIFEMETRICS_AFE_REG_PPG_FREQH                   0x9A        
#define LIFEMETRICS_AFE_REG_PPG1_SUB_EN                 0x9B      
#define LIFEMETRICS_AFE_REG_PPG2_SUB_EN                 0x9C      
#define LIFEMETRICS_AFE_REG_PPG_MODE1                   0x9D        
#define LIFEMETRICS_AFE_REG_PPG_MODE2                   0x9E        
#define LIFEMETRICS_AFE_REG_PPG_MODE3                   0x9F        
#define LIFEMETRICS_AFE_REG_PPG_MODE4                   0xA0        
#define LIFEMETRICS_AFE_REG_PPG_MODE5                   0xA1        
#define LIFEMETRICS_AFE_REG_PPG_MODE6                   0xA2        
#define LIFEMETRICS_AFE_REG_PPG_MODE7                   0xA3        
#define LIFEMETRICS_AFE_REG_PPG_MODE8                   0xA4        
#define LIFEMETRICS_AFE_REG_PPG_CFG                     0xA5          
#define LIFEMETRICS_AFE_REG_ECG_FREQL                   0xA6        
#define LIFEMETRICS_AFE_REG_ECG_FREQH                   0xA7        
#define LIFEMETRICS_AFE_REG_ECG1_FREQDIVL               0xA8    
#define LIFEMETRICS_AFE_REG_ECG1_FREQDIVH               0xA9    
#define LIFEMETRICS_AFE_REG_ECG2_FREQDIVL               0xAA    
#define LIFEMETRICS_AFE_REG_ECG2_FREQDIVH               0xAB    
#define LIFEMETRICS_AFE_REG_ECG_SUBS                    0xAC         
#define LIFEMETRICS_AFE_REG_LEADOFF_INITL               0xAD    
#define LIFEMETRICS_AFE_REG_LEADOFF_INITH               0xAE    
#define LIFEMETRICS_AFE_REG_ECG_INITL                   0xAF        
#define LIFEMETRICS_AFE_REG_ECG_INITH                   0xB0        
#define LIFEMETRICS_AFE_REG_SAMPLE_NUM                  0xB1       
#define LIFEMETRICS_AFE_REG_BIOZ_CFG                    0xB2         
#define LIFEMETRICS_AFE_REG_BIOZ_EXCIT                  0xB3       
#define LIFEMETRICS_AFE_REG_BIOZ_MIXER                  0xB4       
#define LIFEMETRICS_AFE_REG_BIOZ_SELECT                 0xB5      
#define LIFEMETRICS_AFE_REG_BIOZ_GAIN                   0xB6        
#define LIFEMETRICS_AFE_REG_ECGMOD_CFG1                 0xB7      
#define LIFEMETRICS_AFE_REG_ECGMOD_CFG2                 0xB8      
#define LIFEMETRICS_AFE_REG_ECGIMUX_CFG1                0xB9     
#define LIFEMETRICS_AFE_REG_ECGIMUX_CFG2                0xBA     
#define LIFEMETRICS_AFE_REG_ECGIMUX_CFG3                0xBB     
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG1                 0xBC      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG2                 0xBD      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG3                 0xBE      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG4                 0xBF      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG5                 0xC0      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG6                 0xC1      
#define LIFEMETRICS_AFE_REG_ECGAMP_CFG7                 0xC2      
#define LIFEMETRICS_AFE_REG_ECG_BIOZ                    0xC3         
#define LIFEMETRICS_AFE_REG_LEADOFF_CFG                 0xC4      
#define LIFEMETRICS_AFE_REG_LEADOFF_THRESL              0xC5   
#define LIFEMETRICS_AFE_REG_LEADOFF_THRESH              0xC6   
#define LIFEMETRICS_AFE_REG_IIR_CFG                     0xC7          
#define LIFEMETRICS_AFE_REG_IIR_COEFF_ADDR              0xC8   
#define LIFEMETRICS_AFE_REG_IIR_COEFF_DATA              0xC9   
#define LIFEMETRICS_AFE_REG_FIFO_THRESHOLD              0xCA   
#define LIFEMETRICS_AFE_REG_FIFO_CTRL                   0xCB        
#define LIFEMETRICS_AFE_REG_PRODUCT_ID                  0xEB       
#define LIFEMETRICS_AFE_REG_SILICON_ID                  0xEC       
#define LIFEMETRICS_AFE_REG_REVISION                    0xED         
#define LIFEMETRICS_AFE_REG_GPIO_CTRL                   0xEE        
#define LIFEMETRICS_AFE_REG_CHIP_CTRL                   0xEF        
#define LIFEMETRICS_AFE_REG_SEQ_START                   0xF0        
#define LIFEMETRICS_AFE_REG_STATUS_CGB                  0xF1       
#define LIFEMETRICS_AFE_REG_STATUS_SEQ                  0xF2       
#define LIFEMETRICS_AFE_REG_STATUS_LED                  0xF3       
#define LIFEMETRICS_AFE_REG_STATUS_ASATA                0xF4     
#define LIFEMETRICS_AFE_REG_STATUS_ASATB                0xF5     
#define LIFEMETRICS_AFE_REG_STATUS_VCSEL                0xF6     
#define LIFEMETRICS_AFE_REG_STATUS_VCSEL_VSS            0xF7 
#define LIFEMETRICS_AFE_REG_STATUS_VCSEL_VDD            0xF8 
#define LIFEMETRICS_AFE_REG_STATUS_LEADOFF              0xF9   
#define LIFEMETRICS_AFE_REG_STATUS                      0xFA           
#define LIFEMETRICS_AFE_REG_FIFO_LEVEL0                 0xFB      
#define LIFEMETRICS_AFE_REG_FIFO_LEVEL1                 0xFC      
#define LIFEMETRICS_AFE_REG_FIFOL                       0xFD            
#define LIFEMETRICS_AFE_REG_FIFOM                       0xFE            
#define LIFEMETRICS_AFE_REG_FIFOH                       0xFF            

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor register list.
 * @details Specified register list for LIS2DH12TR accelerometer sensor of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_REG_STATUS_AUX                0x07
#define LIFEMETRICS_ACCEL_REG_OUT_TEMP_L                0x0C
#define LIFEMETRICS_ACCEL_REG_OUT_TEMP_H                0x0D
#define LIFEMETRICS_ACCEL_REG_WHO_AM_I                  0x0F
#define LIFEMETRICS_ACCEL_REG_CTRL0                     0x1E
#define LIFEMETRICS_ACCEL_REG_TEMP_CFG                  0x1F
#define LIFEMETRICS_ACCEL_REG_CTRL1                     0x20
#define LIFEMETRICS_ACCEL_REG_CTRL2                     0x21
#define LIFEMETRICS_ACCEL_REG_CTRL3                     0x22
#define LIFEMETRICS_ACCEL_REG_CTRL4                     0x23
#define LIFEMETRICS_ACCEL_REG_CTRL5                     0x24
#define LIFEMETRICS_ACCEL_REG_CTRL6                     0x25
#define LIFEMETRICS_ACCEL_REG_REFERENCE                 0x26
#define LIFEMETRICS_ACCEL_REG_STATUS                    0x27
#define LIFEMETRICS_ACCEL_REG_OUT_X_L                   0x28
#define LIFEMETRICS_ACCEL_REG_OUT_X_H                   0x29
#define LIFEMETRICS_ACCEL_REG_OUT_Y_L                   0x2A
#define LIFEMETRICS_ACCEL_REG_OUT_Y_H                   0x2B
#define LIFEMETRICS_ACCEL_REG_OUT_Z_L                   0x2C
#define LIFEMETRICS_ACCEL_REG_OUT_Z_H                   0x2D
#define LIFEMETRICS_ACCEL_REG_FIFO_CTRL                 0x2E
#define LIFEMETRICS_ACCEL_REG_FIFO_SRC                  0x2F
#define LIFEMETRICS_ACCEL_REG_INT1_CFG                  0x30
#define LIFEMETRICS_ACCEL_REG_INT1_SRC                  0x31
#define LIFEMETRICS_ACCEL_REG_INT1_THS                  0x32
#define LIFEMETRICS_ACCEL_REG_INT1_DURATION             0x33
#define LIFEMETRICS_ACCEL_REG_INT2_CFG                  0x34
#define LIFEMETRICS_ACCEL_REG_INT2_SRC                  0x35
#define LIFEMETRICS_ACCEL_REG_INT2_THS                  0x36
#define LIFEMETRICS_ACCEL_REG_INT2_DURATION             0x37
#define LIFEMETRICS_ACCEL_REG_CLICK_CFG                 0x38
#define LIFEMETRICS_ACCEL_REG_CLICK_SRC                 0x39
#define LIFEMETRICS_ACCEL_REG_CLICK_THS                 0x3A
#define LIFEMETRICS_ACCEL_REG_TIME_LIMIT                0x3B
#define LIFEMETRICS_ACCEL_REG_TIME_LATENCY              0x3C
#define LIFEMETRICS_ACCEL_REG_TIME_WINDOW               0x3D
#define LIFEMETRICS_ACCEL_REG_ACT_THS                   0x3E
#define LIFEMETRICS_ACCEL_REG_ACT_DUR                   0x3F

/**
 * @brief Life Metrics AS6223A temperature sensor register list.
 * @details Specified register list for AS6223A temperature sensor of Life Metrics Click driver.
 */
#define LIFEMETRICS_TEMP_REG_TVAL_L                     0x00
#define LIFEMETRICS_TEMP_REG_TVAL_H                     0x01
#define LIFEMETRICS_TEMP_REG_CONFIG                     0x02
#define LIFEMETRICS_TEMP_REG_CHIP_ID_1                  0x03
#define LIFEMETRICS_TEMP_REG_CHIP_ID_2                  0x04
#define LIFEMETRICS_TEMP_REG_CHIP_ID_3                  0x05

/*! @} */ // lifemetrics_reg

/**
 * @defgroup lifemetrics_set Life Metrics Registers Settings
 * @brief Settings for registers of Life Metrics Click driver.
 */

/**
 * @addtogroup lifemetrics_set
 * @{
 */

/**
 * @brief Life Metrics AS7058A AFE POWER registers setting.
 * @details Specified setting for AS7058A AFE POWER registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_POWER_PWR_ON                    0x17
#define LIFEMETRICS_AFE_POWER_PWR_ISO                   0x08
#define LIFEMETRICS_AFE_POWER_CLK_CFG                   0x07
#define LIFEMETRICS_AFE_POWER_REF_CFG1                  0x3F
#define LIFEMETRICS_AFE_POWER_REF_CFG2                  0x0E
#define LIFEMETRICS_AFE_POWER_REF_CFG3                  0xA0
#define LIFEMETRICS_AFE_POWER_STANDBY_ON1               0x00
#define LIFEMETRICS_AFE_POWER_STANDBY_ON2               0x00
#define LIFEMETRICS_AFE_POWER_STANDBY_EN1               0x04
#define LIFEMETRICS_AFE_POWER_STANDBY_EN2               0x02
#define LIFEMETRICS_AFE_POWER_STANDBY_EN3               0x04
#define LIFEMETRICS_AFE_POWER_STANDBY_EN4               0x00
#define LIFEMETRICS_AFE_POWER_STANDBY_EN5               0x03
#define LIFEMETRICS_AFE_POWER_STANDBY_EN6               0x10
#define LIFEMETRICS_AFE_POWER_STANDBY_EN7               0x10
#define LIFEMETRICS_AFE_POWER_STANDBY_EN8               0x04
#define LIFEMETRICS_AFE_POWER_STANDBY_EN9               0x00
#define LIFEMETRICS_AFE_POWER_STANDBY_EN10              0x03
#define LIFEMETRICS_AFE_POWER_STANDBY_EN11              0x10
#define LIFEMETRICS_AFE_POWER_STANDBY_EN12              0x10
#define LIFEMETRICS_AFE_POWER_STANDBY_EN13              0x10
#define LIFEMETRICS_AFE_POWER_STANDBY_EN14              0x10

/**
 * @brief Life Metrics AS7058A AFE CONTROL registers setting.
 * @details Specified setting for AS7058A AFE CONTROL registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_CONTROL_I2C_MODE                0x00
#define LIFEMETRICS_AFE_CONTROL_INT_CFG                 0x00
#define LIFEMETRICS_AFE_CONTROL_IF_CFG                  0x48
#define LIFEMETRICS_AFE_CONTROL_GPIO_CFG1               0x00
#define LIFEMETRICS_AFE_CONTROL_GPIO_CFG2               0x00
#define LIFEMETRICS_AFE_CONTROL_IO_CFG                  0x00

/**
 * @brief Life Metrics AS7058A AFE LED registers setting.
 * @details Specified setting for AS7058A AFE LED registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_LED_VCSEL_PASSWORD              0x57
#define LIFEMETRICS_AFE_LED_VCSEL_CFG                   0x00
#define LIFEMETRICS_AFE_LED_VCSEL_MODE                  0x00
#define LIFEMETRICS_AFE_LED_LED_CFG                     0x00
#define LIFEMETRICS_AFE_LED_LED_DRV1                    0x00
#define LIFEMETRICS_AFE_LED_LED_DRV2                    0x00
#define LIFEMETRICS_AFE_LED_LED1_ICTRL                  0x09
#define LIFEMETRICS_AFE_LED_LED2_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED3_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED4_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED5_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED6_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED7_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED8_ICTRL                  0x00
#define LIFEMETRICS_AFE_LED_LED_IRNG1                   0x3F
#define LIFEMETRICS_AFE_LED_LED_IRNG2                   0x3F
#define LIFEMETRICS_AFE_LED_LED_SUB1                    0x01
#define LIFEMETRICS_AFE_LED_LED_SUB2                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB3                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB4                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB5                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB6                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB7                    0x00
#define LIFEMETRICS_AFE_LED_LED_SUB8                    0x00
#define LIFEMETRICS_AFE_LED_LOWVDS_WAIT                 0x00

/**
 * @brief Life Metrics AS7058A AFE PD registers setting.
 * @details Specified setting for AS7058A AFE PD registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_PD_PDSEL_CFG                    0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL1                  0x02
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL2                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL3                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL4                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL5                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL6                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL7                  0x00
#define LIFEMETRICS_AFE_PD_PPG1_PDSEL8                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL1                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL2                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL3                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL4                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL5                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL6                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL7                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_PDSEL8                  0x00
#define LIFEMETRICS_AFE_PD_PPG2_AFESEL1                 0x00
#define LIFEMETRICS_AFE_PD_PPG2_AFESEL2                 0x00
#define LIFEMETRICS_AFE_PD_PPG2_AFESEL3                 0x00
#define LIFEMETRICS_AFE_PD_PPG2_AFESEL4                 0x00
#define LIFEMETRICS_AFE_PD_PPG2_AFEEN                   0x00

/**
 * @brief Life Metrics AS7058A AFE IOS registers setting.
 * @details Specified setting for AS7058A AFE IOS registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB1               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB2               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB3               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB4               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB5               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB6               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB7               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG1_SUB8               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB1               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB2               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB3               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB4               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB5               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB6               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB7               0x00
#define LIFEMETRICS_AFE_IOS_IOS_PPG2_SUB8               0x00
#define LIFEMETRICS_AFE_IOS_IOS_LEDOFF                  0x00
#define LIFEMETRICS_AFE_IOS_IOS_CFG                     0x00
#define LIFEMETRICS_AFE_IOS_AOC_SAR_THRES               0x00
#define LIFEMETRICS_AFE_IOS_AOC_SAR_RANGE               0x00
#define LIFEMETRICS_AFE_IOS_AOC_SAR_PPG1                0x00
#define LIFEMETRICS_AFE_IOS_AOC_SAR_PPG2                0x00

/**
 * @brief Life Metrics AS7058A AFE PPG registers setting.
 * @details Specified setting for AS7058A AFE PPG registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_PPG_PPGMOD_CFG1                 0x00
#define LIFEMETRICS_AFE_PPG_PPGMOD_CFG2                 0x00
#define LIFEMETRICS_AFE_PPG_PPGMOD_CFG3                 0x00
#define LIFEMETRICS_AFE_PPG_PPGMOD1_CFG1                0xA7
#define LIFEMETRICS_AFE_PPG_PPGMOD1_CFG2                0x64
#define LIFEMETRICS_AFE_PPG_PPGMOD1_CFG3                0x07
#define LIFEMETRICS_AFE_PPG_PPGMOD2_CFG1                0x27
#define LIFEMETRICS_AFE_PPG_PPGMOD2_CFG2                0x64
#define LIFEMETRICS_AFE_PPG_PPGMOD2_CFG3                0x07

/**
 * @brief Life Metrics AS7058A AFE ECG registers setting.
 * @details Specified setting for AS7058A AFE ECG registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_ECG_BIOZ_CFG                    0x00
#define LIFEMETRICS_AFE_ECG_BIOZ_EXCIT                  0x00
#define LIFEMETRICS_AFE_ECG_BIOZ_MIXER                  0x00
#define LIFEMETRICS_AFE_ECG_BIOZ_SELECT                 0x0D
#define LIFEMETRICS_AFE_ECG_BIOZ_GAIN                   0x00
#define LIFEMETRICS_AFE_ECG_ECGMOD_CFG1                 0x0C
#define LIFEMETRICS_AFE_ECG_ECGMOD_CFG2                 0x00
#define LIFEMETRICS_AFE_ECG_ECGIMUX_CFG1                0x40
#define LIFEMETRICS_AFE_ECG_ECGIMUX_CFG2                0x00
#define LIFEMETRICS_AFE_ECG_ECGIMUX_CFG3                0x00
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG1                 0x60
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG2                 0x00
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG3                 0x59
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG4                 0xFF
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG5                 0x4B
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG6                 0x16
#define LIFEMETRICS_AFE_ECG_ECGAMP_CFG7                 0xB3
#define LIFEMETRICS_AFE_ECG_ECG_BIOZ                    0x00
#define LIFEMETRICS_AFE_ECG_LEADOFF_CFG                 0x00
#define LIFEMETRICS_AFE_ECG_LEADOFF_THRESL              0x00
#define LIFEMETRICS_AFE_ECG_LEADOFF_THRESH              0x00

/**
 * @brief Life Metrics AS7058A AFE SINC registers setting.
 * @details Specified setting for AS7058A AFE SINC registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_SINC_PPG_SINC_CFGA              0x04
#define LIFEMETRICS_AFE_SINC_PPG_SINC_CFGB              0x03
#define LIFEMETRICS_AFE_SINC_PPG_SINC_CFGC              0x00
#define LIFEMETRICS_AFE_SINC_PPG_SINC_CFGD              0x00
#define LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGA             0x2C
#define LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGB             0x03
#define LIFEMETRICS_AFE_SINC_ECG1_SINC_CFGC             0x00
#define LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGA             0x2C
#define LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGB             0x03
#define LIFEMETRICS_AFE_SINC_ECG2_SINC_CFGC             0x00
#define LIFEMETRICS_AFE_SINC_ECG_SINC_CFG               0x00

/**
 * @brief Life Metrics AS7058A AFE SEQ registers setting.
 * @details Specified setting for AS7058A AFE SEQ registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_SEQ_IRQ_ENABLE                  0x06
#define LIFEMETRICS_AFE_SEQ_PPG_SUB_WAIT                0x1E
#define LIFEMETRICS_AFE_SEQ_PPG_SAR_WAIT                0x00
#define LIFEMETRICS_AFE_SEQ_PPG_LED_INIT                0x0A
#define LIFEMETRICS_AFE_SEQ_PPG_FREQL                   0x3F
#define LIFEMETRICS_AFE_SEQ_PPG_FREQH                   0x01
#define LIFEMETRICS_AFE_SEQ_PPG1_SUB_EN                 0x01
#define LIFEMETRICS_AFE_SEQ_PPG2_SUB_EN                 0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_1                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_2                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_3                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_4                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_5                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_6                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_7                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_MODE_8                  0x00
#define LIFEMETRICS_AFE_SEQ_PPG_CFG                     0x00
#define LIFEMETRICS_AFE_SEQ_ECG_FREQL                   0x3F
#define LIFEMETRICS_AFE_SEQ_ECG_FREQH                   0x00
#define LIFEMETRICS_AFE_SEQ_ECG1_FREQDIVL               0x00
#define LIFEMETRICS_AFE_SEQ_ECG1_FREQDIVH               0x00
#define LIFEMETRICS_AFE_SEQ_ECG2_FREQDIVL               0x00
#define LIFEMETRICS_AFE_SEQ_ECG2_FREQDIVH               0x00
#define LIFEMETRICS_AFE_SEQ_ECG_SUBS                    0x02
#define LIFEMETRICS_AFE_SEQ_LEADOFF_INITL               0x00
#define LIFEMETRICS_AFE_SEQ_LEADOFF_INITH               0x00
#define LIFEMETRICS_AFE_SEQ_ECG_INITL                   0x01
#define LIFEMETRICS_AFE_SEQ_ECG_INITH                   0x00
#define LIFEMETRICS_AFE_SEQ_SAMPLE_NUM                  0x00

/**
 * @brief Life Metrics AS7058A AFE POST registers setting.
 * @details Specified setting for AS7058A AFE POST registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_POST_PP_CFG                     0x00
#define LIFEMETRICS_AFE_POST_PPG1_PP1                   0x00
#define LIFEMETRICS_AFE_POST_PPG1_PP2                   0x00
#define LIFEMETRICS_AFE_POST_PPG2_PP1                   0x00
#define LIFEMETRICS_AFE_POST_PPG2_PP2                   0x00

/**
 * @brief Life Metrics AS7058A AFE FIFO registers setting.
 * @details Specified setting for AS7058A AFE FIFO registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_FIFO_FIFO_THRESHOLD             0x40
#define LIFEMETRICS_AFE_FIFO_FIFO_CTRL                  0x00
#define LIFEMETRICS_AFE_FIFO_FIFO_CTRL_RESET            0x80

/**
 * @brief Life Metrics AS7058A AFE MISC registers setting.
 * @details Specified setting for AS7058A AFE MISC registers of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_MISC_SILICON_ID                 0x92
#define LIFEMETRICS_AFE_MISC_CHIP_CTRL_WD_RESET         0x02
#define LIFEMETRICS_AFE_MISC_CHIP_CTRL_CHIP_RESET       0x01
#define LIFEMETRICS_AFE_MISC_SEQ_START_START            0x01
#define LIFEMETRICS_AFE_MISC_SEQ_START_STOP             0x00
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_IIR_OVERFLOW    0x80
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_LEADOFF         0x40
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_VCSEL           0x20
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_ASAT            0x10
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_LED_LOWVDS      0x08
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_FIFO_OVERFLOW   0x04
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_FIFO_THRESHOLD  0x02
#define LIFEMETRICS_AFE_MISC_STATUS_IRQ_SEQUENCER       0x01
#define LIFEMETRICS_AFE_MISC_FIFO_LEVEL1_OVERFLOW       0x04

/**
 * @brief Life Metrics AS7058A AFE FIFO setting.
 * @details Specified setting for AS7058A AFE FIFO of Life Metrics Click driver.
 */
#define LIFEMETRICS_AFE_FIFO_BUFFER_SIZE                1536
#define LIFEMETRICS_AFE_FIFO_SAMPLE_SIZE                3
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_PPG1_FIRST     0x00
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_PPG1_OTHER     0x01
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_PPG2_FIRST     0x02
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_PPG2_OTHER     0x03
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_ECG_SEQ1_SUB1  0x04
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_ECG_SEQ1_SUB2  0x05
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_ECG_SEQ2_SUB1  0x06
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_STATUS         0x07
#define LIFEMETRICS_AFE_FIFO_DATA_MARKER_MASK           0x07

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor STATUS_AUX register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor STATUS_AUX register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_STATUS_AUX_TOR                0x40
#define LIFEMETRICS_ACCEL_STATUS_AUX_TDA                0x04

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor TEMP_CFG register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor TEMP_CFG register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_TEMP_CFG_TEMP_DISABLE         0x00
#define LIFEMETRICS_ACCEL_TEMP_CFG_TEMP_ENABLE          0xC0

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor WHO_AM_I register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor WHO_AM_I register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_WHO_AM_I                      0x33

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor CTRL1 register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor CTRL1 register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_CTRL1_ODR_POWER_DOWN          0x00
#define LIFEMETRICS_ACCEL_CTRL1_ODR_1_HZ                0x10
#define LIFEMETRICS_ACCEL_CTRL1_ODR_10_HZ               0x20
#define LIFEMETRICS_ACCEL_CTRL1_ODR_25_HZ               0x30
#define LIFEMETRICS_ACCEL_CTRL1_ODR_50_HZ               0x40
#define LIFEMETRICS_ACCEL_CTRL1_ODR_100_HZ              0x50
#define LIFEMETRICS_ACCEL_CTRL1_ODR_200_HZ              0x60
#define LIFEMETRICS_ACCEL_CTRL1_ODR_400_HZ              0x70
#define LIFEMETRICS_ACCEL_CTRL1_ODR_1620_HZ             0x80
#define LIFEMETRICS_ACCEL_CTRL1_ODR_5376_HZ             0x90
#define LIFEMETRICS_ACCEL_CTRL1_ODR_MASK                0xF0
#define LIFEMETRICS_ACCEL_CTRL1_LPEN                    0x08
#define LIFEMETRICS_ACCEL_CTRL1_ZEN                     0x04
#define LIFEMETRICS_ACCEL_CTRL1_YEN                     0x02
#define LIFEMETRICS_ACCEL_CTRL1_XEN                     0x01

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor CTRL3 register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor CTRL3 register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_CTRL3_I1_CLICK                0x80
#define LIFEMETRICS_ACCEL_CTRL3_I1_IA1                  0x40
#define LIFEMETRICS_ACCEL_CTRL3_I1_IA2                  0x20
#define LIFEMETRICS_ACCEL_CTRL3_I1_ZYXDA                0x10
#define LIFEMETRICS_ACCEL_CTRL3_I1_WTM                  0x04
#define LIFEMETRICS_ACCEL_CTRL3_I1_OVERRUN              0x02

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor CTRL4 register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor CTRL4 register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_CTRL4_BDU                     0x80
#define LIFEMETRICS_ACCEL_CTRL4_BLE                     0x40
#define LIFEMETRICS_ACCEL_CTRL4_FS_2G                   0x00
#define LIFEMETRICS_ACCEL_CTRL4_FS_4G                   0x10
#define LIFEMETRICS_ACCEL_CTRL4_FS_8G                   0x20
#define LIFEMETRICS_ACCEL_CTRL4_FS_16G                  0x30
#define LIFEMETRICS_ACCEL_CTRL4_FS_MASK                 0x30
#define LIFEMETRICS_ACCEL_CTRL4_HIGH_RES                0x08
#define LIFEMETRICS_ACCEL_CTRL4_ST_NORMAL               0x00
#define LIFEMETRICS_ACCEL_CTRL4_ST_SELF_TEST_0          0x02
#define LIFEMETRICS_ACCEL_CTRL4_ST_SELF_TEST_1          0x04
#define LIFEMETRICS_ACCEL_CTRL4_ST_MASK                 0x06
#define LIFEMETRICS_ACCEL_CTRL4_SIM_4_WIRE              0x00
#define LIFEMETRICS_ACCEL_CTRL4_SIM_3_WIRE              0x01
#define LIFEMETRICS_ACCEL_CTRL4_SIM_MASK                0x01

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor STATUS register setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor STATUS register of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_STATUS_ZYXOR                  0x80
#define LIFEMETRICS_ACCEL_STATUS_ZOR                    0x40
#define LIFEMETRICS_ACCEL_STATUS_YOR                    0x20
#define LIFEMETRICS_ACCEL_STATUS_XOR                    0x10
#define LIFEMETRICS_ACCEL_STATUS_ZYXDA                  0x08
#define LIFEMETRICS_ACCEL_STATUS_ZDA                    0x04
#define LIFEMETRICS_ACCEL_STATUS_YDA                    0x02
#define LIFEMETRICS_ACCEL_STATUS_XDA                    0x01

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor output data rate setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor output data rate of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_ODR_POWER_DOWN                0
#define LIFEMETRICS_ACCEL_ODR_1_HZ                      1
#define LIFEMETRICS_ACCEL_ODR_10_HZ                     2
#define LIFEMETRICS_ACCEL_ODR_25_HZ                     3
#define LIFEMETRICS_ACCEL_ODR_50_HZ                     4
#define LIFEMETRICS_ACCEL_ODR_100_HZ                    5
#define LIFEMETRICS_ACCEL_ODR_200_HZ                    6
#define LIFEMETRICS_ACCEL_ODR_400_HZ                    7
#define LIFEMETRICS_ACCEL_ODR_1620_HZ                   8
#define LIFEMETRICS_ACCEL_ODR_5376_HZ                   9

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor full scale setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor full scale of Life Metrics Click driver.
 */
#define LIFEMETRICS_ACCEL_FS_2G                         0
#define LIFEMETRICS_ACCEL_FS_4G                         1
#define LIFEMETRICS_ACCEL_FS_8G                         2
#define LIFEMETRICS_ACCEL_FS_16G                        3

/**
 * @brief Life Metrics LIS2DH12TR accelerometer sensor sensitivity setting.
 * @details Specified setting for LIS2DH12TR accelerometer sensor sensitivity of Life Metrics Click driver.
 * @note For high-resolution (LIFEMETRICS_ACCEL_CTRL4_HIGH_RES set), normal operating mode (LIFEMETRICS_ACCEL_CTRL1_LPEN cleared).
 */
#define LIFEMETRICS_ACCEL_ACCEL_SENS_G_PER_LSB          0.001
#define LIFEMETRICS_ACCEL_TEMP_SENS_C_PER_LSB           0.25
#define LIFEMETRICS_ACCEL_TEMP_OFFSET                   25.0

/**
 * @brief Life Metrics AS6223A temperature sensor CONFIG register setting.
 * @details Specified setting for AS6223A temperature sensor CONFIG register of Life Metrics Click driver.
 */
#define LIFEMETRICS_TEMP_CONFIG_SOFT_RESET              0x0200
#define LIFEMETRICS_TEMP_CONFIG_SINGLE_SHOT             0x0100
#define LIFEMETRICS_TEMP_CONFIG_SLEEP_MODE              0x0080
#define LIFEMETRICS_TEMP_CONFIG_AVG_8X                  0x0040
#define LIFEMETRICS_TEMP_CONFIG_OSR_16MS                0x0008
#define LIFEMETRICS_TEMP_CONFIG_OSR_32MS                0x000C
#define LIFEMETRICS_TEMP_CONFIG_OSR_64MS                0x0010
#define LIFEMETRICS_TEMP_CONFIG_OSR_MASK                0x001C
#define LIFEMETRICS_TEMP_CONFIG_CONV_RATE_0_25S         0x0000
#define LIFEMETRICS_TEMP_CONFIG_CONV_RATE_1S            0x0001
#define LIFEMETRICS_TEMP_CONFIG_CONV_RATE_4S            0x0002
#define LIFEMETRICS_TEMP_CONFIG_CONV_RATE_8S            0x0003
#define LIFEMETRICS_TEMP_CONFIG_CONV_RATE_MASK          0x0003

/**
 * @brief Life Metrics AS6223A temperature sensor resolution setting.
 * @details Specified setting for AS6223A temperature sensor resolution of Thermo 31 Click driver.
 */
#define LIFEMETRICS_TEMP_RESOLUTION                     0.0078125f

/**
 * @brief Life Metrics device address setting.
 * @details Specified setting for device slave address selection of
 * Life Metrics Click driver.
 */
#define LIFEMETRICS_DEVICE_ADDRESS_ACCEL                0x18
#define LIFEMETRICS_DEVICE_ADDRESS_TEMP                 0x54
#define LIFEMETRICS_DEVICE_ADDRESS_AFE                  0x55

/*! @} */ // lifemetrics_set

/**
 * @defgroup lifemetrics_map Life Metrics MikroBUS Map
 * @brief MikroBUS pin mapping of Life Metrics Click driver.
 */

/**
 * @addtogroup lifemetrics_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Life Metrics Click to the selected MikroBUS.
 */
#define LIFEMETRICS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gpo = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lifemetrics_map
/*! @} */ // lifemetrics

/**
 * @brief Life Metrics Click context object.
 * @details Context object definition of Life Metrics Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t gpo;          /**< AFE (AS7058) GPIO pin. */

    // Input pins
    digital_in_t it2;           /**< Accel (LIS2DH12TR) interrupt pin (active low). */
    digital_in_t it1;           /**< AFE (AS7058) interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float accel_sens;           /**< Accel sensitivity setting. */

    uint8_t fifo_thld;          /**< AFE FIFO interrupt threshold. */

} lifemetrics_t;

/**
 * @brief Life Metrics Click configuration object.
 * @details Configuration object definition of Life Metrics Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t it2;             /**< Accel (LIS2DH12TR) interrupt pin (active low). */
    pin_name_t gpo;             /**< AFE (AS7058) GPIO pin. */
    pin_name_t it1;             /**< AFE (AS7058) interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} lifemetrics_cfg_t;

/**
 * @brief Life Metrics Click axes data structure.
 * @details Axes data object definition of Life Metrics Click driver.
 */
typedef struct
{
    float x;                    /**< X axis. */
    float y;                    /**< Y axis. */
    float z;                    /**< Z axis. */

} lifemetrics_accel_axes_t;

/**
 * @brief Life Metrics Click data structure.
 * @details Data object definition of Life Metrics Click driver.
 */
typedef struct
{
    lifemetrics_accel_axes_t accel;     /**< Accel data. */
    float temperature;                  /**< Temperature data. */

} lifemetrics_accel_data_t;

/**
 * @brief Life Metrics Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIFEMETRICS_OK = 0,
    LIFEMETRICS_ERROR = -1,
    LIFEMETRICS_ACCEL_NO_DRDY = -2

} lifemetrics_return_value_t;

/*!
 * @addtogroup lifemetrics Life Metrics Click Driver
 * @brief API for configuring and manipulating Life Metrics Click driver.
 * @{
 */

/**
 * @brief Life Metrics configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lifemetrics_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lifemetrics_cfg_setup ( lifemetrics_cfg_t *cfg );

/**
 * @brief Life Metrics initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lifemetrics_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_init ( lifemetrics_t *ctx, lifemetrics_cfg_t *cfg );

/**
 * @brief Life Metrics default configuration function.
 * @details This function executes a default configuration of Life Metrics
 * Click board.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lifemetrics_default_cfg ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics set device address function.
 * @details This function sets the I2C slave address used by the driver and updates the I2C interface
 * only if the requested address differs from the currently selected one.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] address : New I2C slave address.
 * @return None.
 * @note None.
 */
void lifemetrics_set_device_addr ( lifemetrics_t *ctx, uint8_t address );

/**
 * @brief Life Metrics get IT1 pin function.
 * @details This function returns the logic state of the IT1 (AFE interrupt) pin.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lifemetrics_get_it1_pin ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics get IT2 pin function.
 * @details This function returns the logic state of the IT2 (Accel interrupt 1) pin.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lifemetrics_get_it2_pin ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE write register function.
 * @details This function writes a single byte of data to the selected AFE register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : AFE register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Life Metrics AFE write registers function.
 * @details This function writes a sequential block of data to the AFE starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Start AFE register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_write_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Life Metrics AFE read register function.
 * @details This function reads a single byte of data from the selected AFE register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : AFE register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Life Metrics AFE read registers function.
 * @details This function reads a sequential block of data from the AFE starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Start AFE register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_read_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Life Metrics AFE check communication function.
 * @details This function checks the AFE communication by reading the silicon ID register multiple times
 * and comparing it with the expected value.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_check_com ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE reset function.
 * @details This function performs a software reset of the AFE and restores required power isolation and
 * power-on register states after reset.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_reset ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE clear FIFO function.
 * @details This function resets the AFE FIFO by setting the FIFO reset bit in the FIFO control register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_clear_fifo ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE start measurement function.
 * @details This function starts the AFE measurement sequence by clearing FIFO/status information and
 * issuing the sequence start command if no pending status is detected.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_start_meas ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE stop measurement function.
 * @details This function stops the AFE measurement sequence by issuing the stop command and polling until
 * the stop state is confirmed. A second stop command is issued as a workaround for a known stop behavior issue.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_stop_meas ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics AFE read FIFO level function.
 * @details This function reads the AFE FIFO level registers and returns the current FIFO sample level
 * if no overflow is detected.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] fifo_lvl : Pointer to the output FIFO level value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_read_fifo_lvl ( lifemetrics_t *ctx, uint16_t *fifo_lvl );

/**
 * @brief Life Metrics AFE read FIFO function.
 * @details This function checks FIFO interrupt/status flags, reads the FIFO level, calculates the read size as
 * a multiple of the configured FIFO threshold, and reads FIFO sample data into the provided buffer.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] fifo_data : Pointer to the FIFO output data buffer.
 * @param[out] fifo_data_size : Pointer to the output FIFO data size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_afe_read_fifo ( lifemetrics_t *ctx, uint8_t *fifo_data, uint16_t *fifo_data_size );

/**
 * @brief Life Metrics accelerometer write register function.
 * @details This function writes a single byte of data to the selected accelerometer register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Accelerometer register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Life Metrics accelerometer write registers function.
 * @details This function writes a sequential block of data to the accelerometer starting from the selected register.
 * The register auto-increment bit is set automatically for multi-byte transactions.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Start accelerometer register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_write_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Life Metrics accelerometer read register function.
 * @details This function reads a single byte of data from the selected accelerometer register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Accelerometer register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Life Metrics accelerometer read registers function.
 * @details This function reads a sequential block of data from the accelerometer starting from the selected register.
 * The register auto-increment bit is set automatically for multi-byte transactions.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Start accelerometer register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_read_regs ( lifemetrics_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Life Metrics accelerometer check communication function.
 * @details This function checks the accelerometer communication by reading the WHO_AM_I register multiple times
 * and comparing it with the expected value.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_check_com ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics accelerometer set ODR function.
 * @details This function sets the accelerometer output data rate by updating the ODR field in the CTRL1 register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] odr : Output data rate selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_set_odr ( lifemetrics_t *ctx, uint8_t odr );

/**
 * @brief Life Metrics accelerometer set full-scale range function.
 * @details This function sets the accelerometer full-scale range by updating the FS field in the CTRL4 register
 * and updates the driver sensitivity scaling factor.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_set_fsr ( lifemetrics_t *ctx, uint8_t fsr );

/**
 * @brief Life Metrics accelerometer temperature sensor enable function.
 * @details This function enables the accelerometer auxiliary temperature sensor.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_en_temp_sen ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics accelerometer temperature sensor disable function.
 * @details This function disables the accelerometer auxiliary temperature sensor.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_dis_temp_sen ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics accelerometer data-ready check function.
 * @details This function checks whether new acceleration data is available by reading the accelerometer status register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_drdy ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics accelerometer get acceleration function.
 * @details This function reads raw acceleration data, converts it to g units using the configured sensitivity,
 * and stores the results in the provided axes structure.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] accel : Pointer to the accelerometer axes output structure.
 * See #lifemetrics_accel_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_get_accel ( lifemetrics_t *ctx, lifemetrics_accel_axes_t *accel );

/**
 * @brief Life Metrics accelerometer temperature data-ready check function.
 * @details This function checks whether new auxiliary temperature data is available by reading the accelerometer AUX status register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_temp_drdy ( lifemetrics_t *ctx );

/**
 * @brief Life Metrics accelerometer get temperature function.
 * @details This function reads raw auxiliary temperature data from the accelerometer, converts it to degrees Celsius,
 * and stores the result in the provided output pointer.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] temp : Pointer to the output temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_get_temp ( lifemetrics_t *ctx, float *temp );

/**
 * @brief Life Metrics accelerometer get data function.
 * @details This function reads both acceleration and accelerometer temperature data and stores the results
 * in the provided combined data structure.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the accelerometer combined data output structure.
 * See #lifemetrics_accel_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_accel_get_data ( lifemetrics_t *ctx, lifemetrics_accel_data_t *data_out );

/**
 * @brief Life Metrics temperature write register function.
 * @details This function writes a 16-bit value to the selected temperature sensor register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Temperature sensor register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_write_reg ( lifemetrics_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Life Metrics temperature read register function.
 * @details This function reads a 16-bit value from the selected temperature sensor register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] reg : Temperature sensor register address.
 * @param[out] data_out : Pointer to the output 16-bit data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_read_reg ( lifemetrics_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Life Metrics temperature write configuration function.
 * @details This function writes the temperature sensor configuration register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[in] config : Temperature sensor configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_write_config ( lifemetrics_t *ctx, uint16_t config );

/**
 * @brief Life Metrics temperature read configuration function.
 * @details This function reads the temperature sensor configuration register.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] config : Pointer to the output configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_read_config ( lifemetrics_t *ctx, uint16_t *config );

/**
 * @brief Life Metrics temperature read temperature function.
 * @details This function reads the raw temperature value from the temperature sensor and converts it
 * to degrees Celsius using the configured resolution.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] temp : Pointer to the output temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_read_temp ( lifemetrics_t *ctx, float *temp );

/**
 * @brief Life Metrics temperature read ID function.
 * @details This function reads the temperature sensor chip ID registers and stores the values into the provided buffer.
 * @param[in] ctx : Click context object.
 * See #lifemetrics_t object definition for detailed explanation.
 * @param[out] chip_id : Pointer to the output chip ID buffer (3 words).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lifemetrics_temp_read_id ( lifemetrics_t *ctx, uint16_t *chip_id );

#ifdef __cplusplus
}
#endif
#endif // LIFEMETRICS_H

/*! @} */ // lifemetrics

// ------------------------------------------------------------------------ END
