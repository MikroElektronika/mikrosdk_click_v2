/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file a5000plugntrust.h
 * @brief This file contains API for A5000 Plug n Trust Click Driver.
 */

#ifndef A5000PLUGNTRUST_H
#define A5000PLUGNTRUST_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup a5000plugntrust A5000 Plug n Trust Click Driver
 * @brief API for configuring and manipulating A5000 Plug n Trust Click driver.
 * @{
 */

/**
 * @defgroup pcb Protocol Control Byte
 * @brief List of pcb of A5000 Plug n Trust Click driver.
 */

/**
 * @addtogroup pcb
 * @{
 */

/**
 * @brief Node Address Byte.
 * @details The node address byte identifies the source and 
 *          the intended destination of the block.
 */
#define A5000PLUGNTRUST_NAD_WRITE                           0x5A
#define A5000PLUGNTRUST_NAD_READ                            0xA5

/**
 * @brief Information block.
 * @details Information block is used to convey information 
 *          for use by the application layer.
 */
#define A5000PLUGNTRUST_PCB_BLOCK_I                         0x00
#define A5000PLUGNTRUST_PCB_BLOCK_I_NS_ENCODE               0x40
#define A5000PLUGNTRUST_PCB_BLOCK_I_M_CHAIN                 0x20

/**
 * @brief Receive ready block.
 * @details Receive ready block is used to convey a positive 
 *          or negative acknowledgement.
 */
#define A5000PLUGNTRUST_PCB_BLOCK_R                         0x80
#define A5000PLUGNTRUST_PCB_BLOCK_R_NR_ENCODE               0x10
#define A5000PLUGNTRUST_PCB_BLOCK_R_ERROR_CRC               0x01
#define A5000PLUGNTRUST_PCB_BLOCK_R_ERROR_OTHER             0x02

/**
 * @brief Supervisory block.
 * @details Supervisory block is used to exchange control 
 *          information between the Host and the Click board.
 */
#define A5000PLUGNTRUST_PCB_BLOCK_S                         0xC0
#define A5000PLUGNTRUST_PCB_BLOCK_S_RESYNC_REQ              0x00
#define A5000PLUGNTRUST_PCB_BLOCK_S_RESYNC_RSP              0x20
#define A5000PLUGNTRUST_PCB_BLOCK_S_IFS_REQ                 0x01
#define A5000PLUGNTRUST_PCB_BLOCK_S_IFS_RSP                 0x21
#define A5000PLUGNTRUST_PCB_BLOCK_S_ABORT_REQ               0x02
#define A5000PLUGNTRUST_PCB_BLOCK_S_ABORT_RSP               0x22
#define A5000PLUGNTRUST_PCB_BLOCK_S_WTX_REQ                 0x03
#define A5000PLUGNTRUST_PCB_BLOCK_S_WTX_RSP                 0x23
#define A5000PLUGNTRUST_PCB_BLOCK_S_SOFT_RESET_REQ          0x0F
#define A5000PLUGNTRUST_PCB_BLOCK_S_SOFT_RESET_RSP          0x2F
#define A5000PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_REQ    0x05
#define A5000PLUGNTRUST_PCB_BLOCK_S_END_APDU_SESSION_RSP    0x25
#define A5000PLUGNTRUST_PCB_BLOCK_S_SE_RESET_REQ            0x06
#define A5000PLUGNTRUST_PCB_BLOCK_S_SE_RESET_RSP            0x26
#define A5000PLUGNTRUST_PCB_BLOCK_S_GET_ATR_REQ             0x07
#define A5000PLUGNTRUST_PCB_BLOCK_S_GET_ATR_RSP             0x27

/*! @} */ // pcb

/**
 * @defgroup apdu A5000 Plug n Trust Registers List
 * @brief List of registers of A5000 Plug n Trust Click driver.
 */

/**
 * @addtogroup apdu
 * @{
 */

/**
 * @brief Instruction class.
 * @details Instruction class - indicates the type of command.
 */
#define A5000PLUGNTRUST_CLA_SECURE                          0x84
#define A5000PLUGNTRUST_CLA_NOT_SECURE                      0x80

/**
 * @brief Instruction code.
 * @details Instruction code - indicates the specific command.
 */
#define A5000PLUGNTRUST_INS_MASK_INS_CHAR                   0xE0
#define A5000PLUGNTRUST_INS_MASK_INSTRUCTION                0x1F
#define A5000PLUGNTRUST_INS_TRANSIENT                       0x80
#define A5000PLUGNTRUST_INS_AUTH_OBJECT                     0x40 
#define A5000PLUGNTRUST_INS_ATTEST                          0x20
#define A5000PLUGNTRUST_INS_WRITE                           0x01
#define A5000PLUGNTRUST_INS_READ                            0x02
#define A5000PLUGNTRUST_INS_CRYPTO                          0x03
#define A5000PLUGNTRUST_INS_MGMT                            0x04
#define A5000PLUGNTRUST_INS_PROCESS                         0x05
#define A5000PLUGNTRUST_INS_IMPORT_EXTERNAL                 0x06

/**
 * @brief Instruction parameters.
 * @details Instruction parameters for the command.
 */
#define A5000PLUGNTRUST_P1_UNUSED                           0x80
#define A5000PLUGNTRUST_P1_MASK_KEY_TYPE                    0x60
#define A5000PLUGNTRUST_P1_MASK_CRED_TYPE                   0x1F
#define A5000PLUGNTRUST_P1_KEY_PAIR                         0x60
#define A5000PLUGNTRUST_P1_PRIVATE                          0x40
#define A5000PLUGNTRUST_P1_PUBLIC                           0x20
#define A5000PLUGNTRUST_P1_DEFAULT                          0x00
#define A5000PLUGNTRUST_P1_EC                               0x01
#define A5000PLUGNTRUST_P1_RSA                              0x02
#define A5000PLUGNTRUST_P1_AES                              0x03
#define A5000PLUGNTRUST_P1_DES                              0x04
#define A5000PLUGNTRUST_P1_HMAC                             0x05
#define A5000PLUGNTRUST_P1_BINARY                           0x06
#define A5000PLUGNTRUST_P1_USERID                           0x07
#define A5000PLUGNTRUST_P1_COUNTER                          0x08
#define A5000PLUGNTRUST_P1_PCR                              0x09
#define A5000PLUGNTRUST_P1_CURVE                            0x0B
#define A5000PLUGNTRUST_P1_SIGNATURE                        0x0C
#define A5000PLUGNTRUST_P1_MAC                              0x0D
#define A5000PLUGNTRUST_P1_CIPHER                           0x0E
#define A5000PLUGNTRUST_P1_TLS                              0x0F
#define A5000PLUGNTRUST_P1_CRYPTO_OBJ                       0x10
#define A5000PLUGNTRUST_P2_DEFAULT                          0x00
#define A5000PLUGNTRUST_P2_GENERATE                         0x03
#define A5000PLUGNTRUST_P2_CREATE                           0x04
#define A5000PLUGNTRUST_P2_SIZE                             0x07
#define A5000PLUGNTRUST_P2_SIGN                             0x09
#define A5000PLUGNTRUST_P2_VERIFY                           0x0A
#define A5000PLUGNTRUST_P2_INIT                             0x0B
#define A5000PLUGNTRUST_P2_UPDATE                           0x0C
#define A5000PLUGNTRUST_P2_FINAL                            0x0D
#define A5000PLUGNTRUST_P2_ONESHOT                          0x0E
#define A5000PLUGNTRUST_P2_DH                               0x0F
#define A5000PLUGNTRUST_P2_DIVERSIFY                        0x10
#define A5000PLUGNTRUST_P2_AUTH_FIRST_PART2                 0x12
#define A5000PLUGNTRUST_P2_AUTH_NONFIRST_PART2              0x13
#define A5000PLUGNTRUST_P2_DUMP_KEY                         0x14
#define A5000PLUGNTRUST_P2_CHANGE_KEY_PART1                 0x15
#define A5000PLUGNTRUST_P2_CHANGE_KEY_PART2                 0x16
#define A5000PLUGNTRUST_P2_KILL_AUTH                        0x17
#define A5000PLUGNTRUST_P2_IMPORT                           0x18
#define A5000PLUGNTRUST_P2_EXPORT                           0x19
#define A5000PLUGNTRUST_P2_SESSION_CREATE                   0x1B
#define A5000PLUGNTRUST_P2_SESSION_CLOSE                    0x1C
#define A5000PLUGNTRUST_P2_SESSION_REFRESH                  0x1E
#define A5000PLUGNTRUST_P2_SESSION_POLICY                   0x1F
#define A5000PLUGNTRUST_P2_VERSION                          0x20
#define A5000PLUGNTRUST_P2_MEMORY                           0x22
#define A5000PLUGNTRUST_P2_LIST                             0x25
#define A5000PLUGNTRUST_P2_TYPE                             0x26
#define A5000PLUGNTRUST_P2_EXIST                            0x27
#define A5000PLUGNTRUST_P2_DELETE_OBJECT                    0x28
#define A5000PLUGNTRUST_P2_DELETE_ALL                       0x2A
#define A5000PLUGNTRUST_P2_SESSION_USERID                   0x2C
#define A5000PLUGNTRUST_P2_HKDF                             0x2D
#define A5000PLUGNTRUST_P2_PBKDF                            0x2E
#define A5000PLUGNTRUST_P2_I2CM                             0x30
#define A5000PLUGNTRUST_P2_I2CM_ATTESTED                    0x31
#define A5000PLUGNTRUST_P2_MAC                              0x32
#define A5000PLUGNTRUST_P2_UNLOCK_CHALLENGE                 0x33
#define A5000PLUGNTRUST_P2_CURVE_LIST                       0x34
#define A5000PLUGNTRUST_P2_SIGN_ECDAA                       0x35
#define A5000PLUGNTRUST_P2_ID                               0x36
#define A5000PLUGNTRUST_P2_ENCRYPT_ONESHOT                  0x37
#define A5000PLUGNTRUST_P2_DECRYPT_ONESHOT                  0x38
#define A5000PLUGNTRUST_P2_ATTEST                           0x3A
#define A5000PLUGNTRUST_P2_ATTRIBUTES                       0x3B
#define A5000PLUGNTRUST_P2_CPLC                             0x3C    
#define A5000PLUGNTRUST_P2_TIME                             0x3D    
#define A5000PLUGNTRUST_P2_TRANSPORT                        0x3E
#define A5000PLUGNTRUST_P2_VARIANT                          0x3F
#define A5000PLUGNTRUST_P2_PARAM                            0x40
#define A5000PLUGNTRUST_P2_DELETE_CURVE                     0x41
#define A5000PLUGNTRUST_P2_ENCRYPT                          0x42
#define A5000PLUGNTRUST_P2_DECRYPT                          0x43
#define A5000PLUGNTRUST_P2_VALIDATE                         0x44
#define A5000PLUGNTRUST_P2_GENERATE_ONESHOT                 0x45
#define A5000PLUGNTRUST_P2_VALIDATE_ONESHOT                 0x46
#define A5000PLUGNTRUST_P2_CRYPTO_LIST                      0x47
#define A5000PLUGNTRUST_P2_RANDOM                           0x49
#define A5000PLUGNTRUST_P2_TLS_PMS                          0x4A
#define A5000PLUGNTRUST_P2_TLS_PRF_CLI_HELLO                0x4B
#define A5000PLUGNTRUST_P2_TLS_PRF_SRV_HELLO                0x4C
#define A5000PLUGNTRUST_P2_TLS_PRF_CLI_RND                  0x4D
#define A5000PLUGNTRUST_P2_TLS_PRF_SRV_RND                  0x4E
#define A5000PLUGNTRUST_P2_RAW                              0x4F
#define A5000PLUGNTRUST_P2_IMPORT_EXT                       0x51
#define A5000PLUGNTRUST_P2_SCP                              0x52
#define A5000PLUGNTRUST_P2_AUTH_FIRST_PART1                 0x53
#define A5000PLUGNTRUST_P2_AUTH_NONFIRST_PART1              0x54

/**
 * @brief Secure Object type.
 * @details Secure Object Type constants.
 */
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_EC_KEY_PAIR      0x01
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_EC_PRIV_KEY      0x02
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_EC_PUB_KEY       0x03
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_RSA_KEY_PAIR     0x04
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_RSA_KEY_PAIR_CRT 0x05
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_RSA_PRIV_KEY     0x06
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_RSA_PRIV_KEY_CRT 0x07
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_RSA_PUB_KEY      0x08
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_AES_KEY          0x09
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_DES_KEY          0x0A
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_BINARY_FILE      0x0B
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_USERID           0x0C
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_COUNTER          0x0D
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_PCR              0x0F
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_CURVE            0x10
#define A5000PLUGNTRUST_SECURE_OBJECT_TYPE_HMAC_KEY         0x11

/**
 * @brief Memory type.
 * @details Memory Type constants.
 */
#define A5000PLUGNTRUST_MEM_PERSISTENT                      0x01
#define A5000PLUGNTRUST_MEM_TRANSIENT_RESET                 0x02
#define A5000PLUGNTRUST_MEM_TRANSIENT_DESELECT              0x03

/**
 * @brief Origin type.
 * @details Origin Type constants.
 */
#define A5000PLUGNTRUST_ORIGIN_EXTERNAL                     0x01
#define A5000PLUGNTRUST_ORIGIN_INTERNAL                     0x02
#define A5000PLUGNTRUST_ORIGIN_PROVISIONED                  0x03

/**
 * @brief TLV(Tag, Length, Value) tags.
 * @details TLV tag constants.
 */
#define A5000PLUGNTRUST_TLV_TAG_SESSION_ID                  0x10
#define A5000PLUGNTRUST_TLV_TAG_POLICY                      0x11
#define A5000PLUGNTRUST_TLV_TAG_MAX_ATTEMPTS                0x12
#define A5000PLUGNTRUST_TLV_TAG_IMPORT_AUTH_DATA            0x13
#define A5000PLUGNTRUST_TLV_TAG_IMPORT_AUTH_KEY_ID          0x14
#define A5000PLUGNTRUST_TLV_TAG_1                           0x41
#define A5000PLUGNTRUST_TLV_TAG_2                           0x42
#define A5000PLUGNTRUST_TLV_TAG_3                           0x43
#define A5000PLUGNTRUST_TLV_TAG_4                           0x44
#define A5000PLUGNTRUST_TLV_TAG_5                           0x45
#define A5000PLUGNTRUST_TLV_TAG_6                           0x46
#define A5000PLUGNTRUST_TLV_TAG_7                           0x47
#define A5000PLUGNTRUST_TLV_TAG_8                           0x48
#define A5000PLUGNTRUST_TLV_TAG_9                           0x49
#define A5000PLUGNTRUST_TLV_TAG_10                          0x4A

/**
 * @brief ECSignature Algo.
 * @details ECSignature Algorithm constants.
 */
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_PLAIN                 0x09
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_SHA                   0x11
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_SHA_224               0x25
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_SHA_256               0x21
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_SHA_384               0x22
#define A5000PLUGNTRUST_ECS_SIG_ECDSA_SHA_512               0x26
#define A5000PLUGNTRUST_ECS_SIG_ED25519PH_SHA_512           0xA3
#define A5000PLUGNTRUST_ECS_SIG_ECDAA                       0xF4 

/**
 * @brief RSASignature Algo.
 * @details RSASignature Algorithm constants.
 */
#define A5000PLUGNTRUST_RSA_SHA1_PKCS1_PSS                  0x15
#define A5000PLUGNTRUST_RSA_SHA224_PKCS1_PSS                0x2B
#define A5000PLUGNTRUST_RSA_SHA256_PKCS1_PSS                0x2C
#define A5000PLUGNTRUST_RSA_SHA384_PKCS1_PSS                0x2D
#define A5000PLUGNTRUST_RSA_SHA512_PKCS1_PSS                0x2E
#define A5000PLUGNTRUST_RSA_SHA1_PKCS1                      0x0A
#define A5000PLUGNTRUST_RSA_SHA_224_PKCS1                   0x27
#define A5000PLUGNTRUST_RSA_SHA_256_PKCS1                   0x28
#define A5000PLUGNTRUST_RSA_SHA_384_PKCS1                   0x29
#define A5000PLUGNTRUST_RSA_SHA_512_PKCS1                   0x2A
#define A5000PLUGNTRUST_RSA_NO_PAD                          0x0C
#define A5000PLUGNTRUST_RSA_PKCS1                           0x0A
#define A5000PLUGNTRUST_RSA_PKCS1_OAEP                      0x0F
#define A5000PLUGNTRUST_RSA_512                             512
#define A5000PLUGNTRUST_RSA_1024                            1024
#define A5000PLUGNTRUST_RSA_1152                            1152
#define A5000PLUGNTRUST_RSA_2048                            2048
#define A5000PLUGNTRUST_RSA_3072                            3072
#define A5000PLUGNTRUST_RSA_4096                            4096
#define A5000PLUGNTRUST_RSA_COMP_MOD                        0x00
#define A5000PLUGNTRUST_RSA_COMP_PUB_EXP                    0x01
#define A5000PLUGNTRUST_RSA_COMP_PRIV_EXP                   0x02
#define A5000PLUGNTRUST_RSA_COMP_P                          0x03
#define A5000PLUGNTRUST_RSA_COMP_Q                          0x04
#define A5000PLUGNTRUST_RSA_COMP_DP                         0x05
#define A5000PLUGNTRUST_RSA_COMP_DQ                         0x06
#define A5000PLUGNTRUST_RSA_COMP_INVQ                       0x07

/**
 * @brief Digest Mode.
 * @details Digest Mode constants.
 */
#define A5000PLUGNTRUST_DIGEST_NO_HASH                      0x00
#define A5000PLUGNTRUST_DIGEST_SHA                          0x01
#define A5000PLUGNTRUST_DIGEST_SHA224                       0x07
#define A5000PLUGNTRUST_DIGEST_SHA256                       0x04
#define A5000PLUGNTRUST_DIGEST_SHA384                       0x05
#define A5000PLUGNTRUST_DIGEST_SHA512                       0x06

/**
 * @brief MAC Algo.
 * @details MAC Algorithm constants.
 */
#define A5000PLUGNTRUST_HMAC_SHA1                           0x18
#define A5000PLUGNTRUST_HMAC_SHA256                         0x19
#define A5000PLUGNTRUST_HMAC_SHA384                         0x1A
#define A5000PLUGNTRUST_HMAC_SHA512                         0x1B
#define A5000PLUGNTRUST_CMAC_128                            0x31

/**
 * @brief ECCurve.
 * @details ECCurve constants.
 */
#define A5000PLUGNTRUST_ECC_UNUSED                          0x00
#define A5000PLUGNTRUST_ECC_NIST_P192                       0x01
#define A5000PLUGNTRUST_ECC_NIST_P224                       0x02
#define A5000PLUGNTRUST_ECC_NIST_P256                       0x03
#define A5000PLUGNTRUST_ECC_NIST_P384                       0x04
#define A5000PLUGNTRUST_ECC_NIST_P521                       0x05
#define A5000PLUGNTRUST_ECC_Brainpool160                    0x06
#define A5000PLUGNTRUST_ECC_Brainpool192                    0x07
#define A5000PLUGNTRUST_ECC_Brainpool224                    0x08
#define A5000PLUGNTRUST_ECC_Brainpool256                    0x09
#define A5000PLUGNTRUST_ECC_Brainpool320                    0x0A
#define A5000PLUGNTRUST_ECC_Brainpool384                    0x0B
#define A5000PLUGNTRUST_ECC_Brainpool512                    0x0C
#define A5000PLUGNTRUST_ECC_Secp160k1                       0x0D
#define A5000PLUGNTRUST_ECC_Secp192k1                       0x0E
#define A5000PLUGNTRUST_ECC_Secp224k1                       0x0F
#define A5000PLUGNTRUST_ECC_Secp256k1                       0x10
#define A5000PLUGNTRUST_ECC_TPM_ECC_BN_P256                 0x11
#define A5000PLUGNTRUST_ECC_ID_ECC_ED_25519                 0x40
#define A5000PLUGNTRUST_ECC_ID_ECC_MONT_DH_25519            0x41
#define A5000PLUGNTRUST_ECC_CURVE_PARAM_A                   0x01
#define A5000PLUGNTRUST_ECC_CURVE_PARAM_B                   0x02
#define A5000PLUGNTRUST_ECC_CURVE_PARAM_G                   0x04
#define A5000PLUGNTRUST_ECC_CURVE_PARAM_N                   0x08
#define A5000PLUGNTRUST_ECC_CURVE_PARAM_PRIME               0x10

/**
 * @brief Cipher Mode.
 * @details Cipher Mode constants.
 */
#define A5000PLUGNTRUST_CIPHER_DES_CBC_NOPAD                0x01
#define A5000PLUGNTRUST_CIPHER_DES_CBC_ISO9797_M1           0x02
#define A5000PLUGNTRUST_CIPHER_DES_CBC_ISO9797_M2           0x03
#define A5000PLUGNTRUST_CIPHER_DES_CBC_PKCS5                0x04
#define A5000PLUGNTRUST_CIPHER_DES_ECB_NOPAD                0x05
#define A5000PLUGNTRUST_CIPHER_DES_ECB_ISO9797_M1           0x06
#define A5000PLUGNTRUST_CIPHER_DES_ECB_ISO9797_M2           0x07
#define A5000PLUGNTRUST_CIPHER_DES_ECB_PKCS5                0x08
#define A5000PLUGNTRUST_CIPHER_AES_ECB_NOPAD                0x0E
#define A5000PLUGNTRUST_CIPHER_AES_CBC_NOPAD                0x0D
#define A5000PLUGNTRUST_CIPHER_AES_CBC_ISO9797_M1           0x16
#define A5000PLUGNTRUST_CIPHER_AES_CBC_ISO9797_M2           0x17
#define A5000PLUGNTRUST_CIPHER_AES_CBC_PKCS5                0x18
#define A5000PLUGNTRUST_CIPHER_AES_CTR                      0xF0

/**
 * @brief AppletConfig.
 * @details AppletConfig configurations.
 */
#define A5000PLUGNTRUST_CONFIG_ECDAA                        0x0001
#define A5000PLUGNTRUST_CONFIG_ECDSA_ECDH_ECDHE             0x0002
#define A5000PLUGNTRUST_CONFIG_EDDSA                        0x0004
#define A5000PLUGNTRUST_CONFIG_DH_MONT                      0x0008
#define A5000PLUGNTRUST_CONFIG_HMAC                         0x0010
#define A5000PLUGNTRUST_CONFIG_RSA_PLAIN                    0x0020
#define A5000PLUGNTRUST_CONFIG_RSA_CRT                      0x0040
#define A5000PLUGNTRUST_CONFIG_AES                          0x0080
#define A5000PLUGNTRUST_CONFIG_DES                          0x0100
#define A5000PLUGNTRUST_CONFIG_PBKDF                        0x0200
#define A5000PLUGNTRUST_CONFIG_TLS                          0x0400
#define A5000PLUGNTRUST_CONFIG_MIFARE                       0x0800
#define A5000PLUGNTRUST_CONFIG_FIPS_MODE_DISABLED           0x1000
#define A5000PLUGNTRUST_CONFIG_I2CM                         0x2000
#define A5000PLUGNTRUST_CONFIG_ECC_ALL                      0x000F
#define A5000PLUGNTRUST_CONFIG_RSA_ALL                      0x0060
#define A5000PLUGNTRUST_CONFIG_ALL                          0x3FFF

/**
 * @brief Lock Indicator.
 * @details Lock Indicator constants.
 */
#define A5000PLUGNTRUST_TRANSIENT_LOCK                      0x01
#define A5000PLUGNTRUST_PERSISTENT_LOCK                     0x02

/**
 * @brief Lock State.
 * @details Lock State constants.
 */
#define A5000PLUGNTRUST_LOCKED                              0x01

/**
 * @brief Crypto Context.
 * @details Crypto Context constants.
 */
#define A5000PLUGNTRUST_CC_DIGEST                           0x01
#define A5000PLUGNTRUST_CC_CIPHER                           0x02
#define A5000PLUGNTRUST_CC_SIGNATURE                        0x03

/**
 * @brief Result.
 * @details Result constants.
 */
#define A5000PLUGNTRUST_RESULT_SUCCESS                      0x01
#define A5000PLUGNTRUST_RESULT_FAILURE                      0x02

/**
 * @brief Transient Indicator.
 * @details Transient Indicator constants.
 */
#define A5000PLUGNTRUST_PERSISTENT                          0x01
#define A5000PLUGNTRUST_TRANSIENT                           0x02

/**
 * @brief Set Indicator.
 * @details Set Indicator constants.
 */
#define A5000PLUGNTRUST_NOT_SET                             0x01
#define A5000PLUGNTRUST_SET                                 0x02

/**
 * @brief More Indicator.
 * @details  More Indicator constants.
 */
#define A5000PLUGNTRUST_NO_MORE                             0x01
#define A5000PLUGNTRUST_MORE                                0x02

/**
 * @brief Platform SCP Request.
 * @details Platform SCP Request constants.
 */
#define A5000PLUGNTRUST_SCP_REQUIRED                        0x01
#define A5000PLUGNTRUST_SCP_NOT_REQUIRED                    0x02

/**
 * @brief Reserved file identifiers.
 * @details Reserved file identifiers constants.
 */
#define A5000PLUGNTRUST_APPLET_RES_ID_TRANSPORT             0x7FFF0200ul
#define A5000PLUGNTRUST_APPLET_RES_ID_KP_FASTSCP_USER       0x7FFF0201ul
#define A5000PLUGNTRUST_APPLET_RES_ID_KP_FASTSCP_IMPORT     0x7FFF0202ul
#define A5000PLUGNTRUST_APPLET_RES_ID_PUB_FASTSCP_IMPORT    0x7FFF0203ul
#define A5000PLUGNTRUST_APPLET_RES_ID_FEATURE               0x7FFF0204ul
#define A5000PLUGNTRUST_APPLET_RES_ID_FACTORY_RESET         0x7FFF0205ul
#define A5000PLUGNTRUST_APPLET_RES_ID_UNIQUE_ID             0x7FFF0206ul
#define A5000PLUGNTRUST_APPLET_RES_ID_PLATFORM_SCP          0x7FFF0207ul

/**
 * @brief Error codes.
 * @details Error codes constants.
 */
#define A5000PLUGNTRUST_SW_NOERROR                          0x9000
#define A5000PLUGNTRUST_SW_CONDITIONS_NOT_SATISFIED         0x6985
#define A5000PLUGNTRUST_SW_SECURITY_STATUS                  0x6982
#define A5000PLUGNTRUST_SW_WRONG_DATA                       0x6A80
#define A5000PLUGNTRUST_SW_DATA_INVALID                     0x6984
#define A5000PLUGNTRUST_SW_COMMAND_NOT_ALLOWED              0x6986

/**
 * @brief Check object exist.
 * @details Check object exist constants.
 */
#define A5000PLUGNTRUST_OBJECT_DOES_EXISTS                  1
#define A5000PLUGNTRUST_OBJECT_DOESNT_EXIST                 2

/**
 * @brief Applet provided objects.
 * @details Reserved applet provided objects.
 */
#define A5000PLUGNTRUST_OBJID_SE05X_APPLET_RES_START        0x7FFF0000ul
#define A5000PLUGNTRUST_SSS_OBJID_DEMO_AUTH_START           0x7DA00000ul
#define A5000PLUGNTRUST_SSS_OBJID_IOT_HUB_A_START           0xF0000000ul

/**
 * @brief Mask for applet provided objects.
 * @details Mask for reserved applet provided objects.
 */
#define A5000PLUGNTRUST_OBJID_APPLET_MASK                   0xFFFF0000ul
#define A5000PLUGNTRUST_OBJID_IOT_MASK                      0xF0000000ul


/*! @} */ // apdu

/**
 * @defgroup a5000plugntrust_set A5000 Plug n Trust Registers Settings
 * @brief Settings for registers of A5000 Plug n Trust Click driver.
 */

/**
 * @addtogroup a5000plugntrust_set
 * @{
 */

/**
 * @brief Card manager response data.
 * @details Card manager response data option parameters.
 */
#define A5000PLUGNTRUST_CARD_MANAGER_WITH_RSP               1
#define A5000PLUGNTRUST_CARD_MANAGER_WITHOUT_RSP            0

/**
 * @brief A5000 Plug n Trust device address setting.
 * @details Specified setting for device slave address selection of
 * A5000 Plug n Trust Click driver.
 */
#define A5000PLUGNTRUST_DEVICE_ADDRESS                      0x48

/*! @} */ // a5000plugntrust_set

/**
 * @defgroup a5000plugntrust_map A5000 Plug n Trust MikroBUS Map
 * @brief MikroBUS pin mapping of A5000 Plug n Trust Click driver.
 */

/**
 * @addtogroup a5000plugntrust_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of A5000 Plug n Trust Click to the selected MikroBUS.
 */
#define A5000PLUGNTRUST_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // a5000plugntrust_map
/*! @} */ // a5000plugntrust

/**
 * @brief A5000 Plug n Trust Click context object.
 * @details Context object definition of A5000 Plug n Trust Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Enable pin (Active high). */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} a5000plugntrust_t;

/**
 * @brief A5000 Plug n Trust Click configuration object.
 * @details Configuration object definition of A5000 Plug n Trust Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;          /**< Enable pin (Active high). */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} a5000plugntrust_cfg_t;

/**
 * @brief APDU data object
 * @details Contatins data for sending and recieving data in APDU protocol.
 */
typedef struct
{
    uint8_t cla;                /**< Instruction class. */
    uint8_t ins;                /**< Instruction code. */
    uint8_t p1;                 /**< Parameter 1. */
    uint8_t p2;                 /**< Prameter 2. */
    uint8_t payload_len;        /**< Payload data len. */
    uint8_t payload[ 0xFF ];    /**< Payload data. */
    uint16_t rsp_len;           /**< Response data len. */
    uint16_t status;            /**< Response status. */
    
} a5000plugntrust_apdu_t;

/**
 * @brief Communication frame data object
 * @details Contatins data for communication between Click and Host.
 */
typedef struct
{
    uint8_t nad;                    /**< Node Address Byte. */
    uint8_t pcb;                    /**< Protocol Control Byte. */
    uint8_t len;                    /**< Communication length->sizeof(apdu)+sizeof(crc16). */
    a5000plugntrust_apdu_t *apdu;   /**< Instruction class. */
    uint16_t crc16;                 /**< Coomunication CRC. */
    
} a5000plugntrust_frame_data_t;

/**
 * @brief Data after reset
 * @details Data that click is sending Host after Reset command.
 */
typedef struct
{
    uint8_t protocol_version;
    uint8_t vendor_id[ 5 ];
    
    uint8_t data_link_layer_parameters_len;
    uint8_t data_link_layer_parameters[ 0x04 ];
    
    uint8_t physical_layer_id;
    
    uint8_t physical_layer_parameters_len;
    uint8_t physical_layer_parameters[ 0x0B ];
    
    uint8_t historical_len;
    uint8_t historical[ 0x0A ];
    
} a5000plugntrust_atr_t;

/**
 * @brief Version info data
 * @details Applet version, configuration and secure data.
 */
typedef struct
{
    uint8_t major_version;
    uint8_t minor_version;
    uint8_t patch_version;
    
    uint16_t applet_config;
    uint16_t secure_box;
    
} a5000plugntrust_version_info_t;

/**
 * @brief A5000 Plug n Trust Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    A5000PLUGNTRUST_OK             = 0,
    A5000PLUGNTRUST_ERROR          = -1,
    A5000PLUGNTRUST_ERROR_TIMEOUT  = -2,
    A5000PLUGNTRUST_ERROR_DATA_OVF = -3

} a5000plugntrust_return_value_t;

/*!
 * @addtogroup a5000plugntrust A5000 Plug n Trust Click Driver
 * @brief API for configuring and manipulating A5000 Plug n Trust Click driver.
 * @{
 */

/**
 * @brief A5000 Plug n Trust configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #a5000plugntrust_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void a5000plugntrust_cfg_setup ( a5000plugntrust_cfg_t *cfg );

/**
 * @brief A5000 Plug n Trust initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #a5000plugntrust_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_init ( a5000plugntrust_t *ctx, a5000plugntrust_cfg_t *cfg );

/**
 * @brief Writing frame data function.
 * @details This function writes a @b frame_data to device.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] frame_data : Communication data.
 * See #a5000plugntrust_frame_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_apdu_write ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );

/**
 * @brief Reading frame data function function.
 * @details This function reads a @b frame_data from device.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[out] frame_data : Communication data.
 * See #a5000plugntrust_frame_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_apdu_read ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );

/**
 * @brief Write-Read frame data function.
 * @details This function writes a @b frame_data and then reads return data from device and stores it in @b frame_data.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in,out] frame_data : Communication data.
 * See #a5000plugntrust_frame_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_apdu_transfer ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );

/**
 * @brief Set Enable pin state.
 * @details This function sets @b en pin state.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return Nothing.
 * @note None.
 */
void a5000plugntrust_set_en ( a5000plugntrust_t *ctx, uint8_t state );

/**
 * @brief Add TLV data of 1 byte value in payload buffer.
 * @details Concatenates TLV data in APDU payload for writing data to device.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] value : Value of TLV data.
 * @return Nothing.
 * @note None.
 * @b Example
 * @code
 * a5000plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                             A5000PLUGNTRUST_TLV_TAG_1, A5000PLUGNTRUST_MEM_PERSISTENT );
 * @endcode
 */
void a5000plugntrust_set_tlv_u8 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t value );

/**
 * @brief Add TLV data of 2 bytes value in payload buffer.
 * @details Concatenates TLV data in APDU payload for writing data to device.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] value : Value of TLV data.
 * @return Nothing.
 * @note None.
 * @b Example
 * @code
 * uint16_t offset = 0;
 * a5000plugntrust_set_tlv_u16( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                              A5000PLUGNTRUST_TLV_TAG_2, offset );
 * @endcode
 */
void a5000plugntrust_set_tlv_u16 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value );

/**
 * @brief Add TLV data of 2 bytes value in payload buffer if value is greater then 0.
 * @details Calls @b a5000plugntrust_set_tlv_u16 if @b value parameter is greater then 0.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] value : Value of TLV data.
 * @return Nothing.
 * @note None.
 * @b Example
 * @code
 * uint16_t offset = 10;
 * a5000plugntrust_set_tlv_u16_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                                       A5000PLUGNTRUST_TLV_TAG_2, offset );
 * @endcode
 */
void a5000plugntrust_set_tlv_u16_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint16_t value );

/**
 * @brief Add TLV data of 4 bytes value in payload buffer.
 * @details Concatenates TLV data in APDU payload for writing data to device.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] value : Value of TLV data.
 * @return Nothing.
 * @note None.
 * @b Example
 * @code
 * uint32_t object_id = 0x12345678;
 * a5000plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                              A5000PLUGNTRUST_TLV_TAG_1, object_id );
 * @endcode
 */
void a5000plugntrust_set_tlv_u32 ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint32_t value );

/**
 * @brief Add TLV data buffer in payload buffer.
 * @details Concatenates TLV data in APDU payload for writing data to device.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] cmd : TLV data buffer.
 * @param[in] cmd_len : TLV data buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 * @b Example
 * @code
 * #define AES_KEY_SIZE 16
 * uint8_t aes_key[ AES_KEY_SIZE ] = { 0 }
 * a5000plugntrust_set_tlv_u8buf( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                                A5000PLUGNTRUST_TLV_TAG_3, aes_key, AES_KEY_SIZE );
 * @endcode
 */
err_t a5000plugntrust_set_tlv_u8buf ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len );

/**
 * @brief Add TLV data buffer in payload buffer if TLV data buffer length greater then 0.
 * @details Calls @b a5000plugntrust_set_tlv_u8buf if @b cmd_len parameter is greater then 0.
 * @param[out] buf : Output buffer.
 * @param[out] buf_len : Output buffer size, incresed by adding TLV.
 * @param[in] tag : Tag of TLV data.
 * @param[in] cmd : TLV data buffer.
 * @param[in] cmd_len : TLV data buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 * @b Example
 * @code
 * #define AES_KEY_SIZE 16
 * uint8_t aes_key[ AES_KEY_SIZE ] = { 0 }
 * a5000plugntrust_set_tlv_u8buf_optional( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
 *                                         A5000PLUGNTRUST_TLV_TAG_3, aes_key, AES_KEY_SIZE );
 * @endcode
 */
err_t a5000plugntrust_set_tlv_u8buf_optional ( uint8_t *buf, uint8_t *buf_len, uint8_t tag, uint8_t *cmd, uint32_t cmd_len );

/**
 * @brief Parses TLV data from payload buffer to find data for desired tag.
 * @details Searches APDU payload response to find 1 byte of value for desired @b tag.
 * @param[in] buf : Input buffer.
 * @param[in,out] buf_index : Buffer index to search from.
 * @param[in] tag : Tag of TLV data.
 * @param[out] rsp : Value of TLV data.
 * @return @li @c  0 - Data found,
 *         @li @c -1 - Data missing.
 * See #err_t definition for detailed explanation.
 * @note None.
 * @b Example
 * @code
 * uint32_t buff_index = 0;
 * uint8_t value = 0;
 * a5000plugntrust_get_tlv_u8( frame_data.apdu->payload, &parse_index, A5000PLUGNTRUST_TLV_TAG_1, &value )
 * @endcode
 */
err_t a5000plugntrust_get_tlv_u8 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint8_t *rsp );

/**
 * @brief Parses TLV data from payload buffer to find data for desired tag.
 * @details Searches APDU payload response to find 2 bytes of value for desired @b tag.
 * @param[in] buf : Input buffer.
 * @param[in,out] buf_index : Buffer index to search from.
 * @param[in] tag : Tag of TLV data.
 * @param[out] rsp : Value of TLV data.
 * @return @li @c  0 - Data found,
 *         @li @c -1 - Data missing.
 * See #err_t definition for detailed explanation.
 * @note None.
 * @b Example
 * @code
 * uint32_t buff_index = 0;
 * uint16_t value = 0;
 * a5000plugntrust_get_tlv_u16( frame_data.apdu->payload, &parse_index, A5000PLUGNTRUST_TLV_TAG_1, &value )
 * @endcode
 */
err_t a5000plugntrust_get_tlv_u16 ( uint8_t *buf, uint32_t *buf_index, uint8_t tag, uint16_t *rsp );

/**
 * @brief Parses TLV data from payload buffer to find data for desired tag.
 * @details Searches APDU payload response to find 4 bytes of value for desired @b tag.
 * @param[in] buf : Input buffer.
 * @param[in,out] buf_index : Buffer index to search from.
 * @param[in] buf_len : Input buffer length.
 * @param[in] tag : Tag of TLV data.
 * @param[out] rsp : Buffer of TLV data.
 * @param[in,out] rsp_len : Rsp buffer length.
 * @return @li @c  0 - Data found,
 *         @li @c -1 - Error parssing data.
 * See #err_t definition for detailed explanation.
 * @note None.
 * @b Example
 * @code
 * uint32_t buff_index = 0;
 * uint8_t parse_len = 0xFF;
 * uint8_t data_out[ 0xFF ] = 0;
 * a5000plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
 *                                A5000PLUGNTRUST_TLV_TAG_1, data_out, &parse_len )
 * @endcode
 */
err_t a5000plugntrust_get_tlv_u8buf ( uint8_t *buf, uint32_t *buf_index, uint8_t buf_len, 
                                      uint8_t tag, uint8_t *rsp, uint32_t *rsp_len );

/**
 * @brief Calculates APDU object size.
 * @details Goes through apdu object and returns size value of it.
 * @param[in] apdu_data : APDU object.
 * See a5000plugntrust_apdu_t object definition for detailed explanation.
 * @return Value size of APDU data object
 * @note On the start return value is 4[CLA,INS,P1,P2] and then adds @b payload_len and @b rsp_len.
 */
uint8_t a5000plugntrust_calculate_apdu_size ( a5000plugntrust_apdu_t *apdu_data );

/**
 * @brief Sends command for ending APDU session.
 * @details This function sends SBLOCK request for ending APDU session.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_end_apdu_session ( a5000plugntrust_t *ctx );

/**
 * @brief Reads all Object ID's from Applet.
 * @details Reads list of all objects from Applet and outputs array of objects ID's.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[out] id_list : Buffer of Object ID's.
 * @param[out] list_len : Length of @b id_list.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note By default Applet has 26 predefined and reserved objects.
 */
err_t a5000plugntrust_object_id_list ( a5000plugntrust_t *ctx, uint32_t *id_list, uint8_t *list_len );

/**
 * @brief Sends request to reset device and reads ATR data.
 * @details Sends request to reset device and parses and returns ATR data.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[out] atr_data : Output data after reset.
 * See #a5000plugntrust_atr_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_sw_reset ( a5000plugntrust_t *ctx, a5000plugntrust_atr_t *atr_data );

/**
 * @brief Selects Clicks Applet and returns info that device sends back to host.
 * @details Selects Clicks Applet and returns version info that device sens back to host.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] ns_encode : NS encode of I-Block.
 * @param[out] ver_info : Version info data.
 * See #a5000plugntrust_version_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_select_applet ( a5000plugntrust_t *ctx, uint8_t ns_encode, a5000plugntrust_version_info_t *ver_info );

/**
 * @brief Select card manager.
 * @details Selects card manager and depending of @b rsp parameter returns data to host.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] rsp : Request response from card manager.
 * @param[out] cardmanager_rsp : Response buffer.
 * @param[out] cardmanager_rsp_len : Length of response buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t a5000plugntrust_select_card_manager ( a5000plugntrust_t *ctx, uint8_t rsp, 
                                            uint8_t *cardmanager_rsp, uint8_t *cardmanager_rsp_len );

/**
 * @brief Reads Applet free memory
 * @details Sends request to check free memory of @b memory_type.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] memory_type : Memory type to check.
 * See #Memory type definition for memory type options.
 * @param[out] free_memory : Response buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_get_free_memory ( a5000plugntrust_t *ctx, uint8_t memory_type, uint16_t *free_memory );

/**
 * @brief Get random data.
 * @details Sends request to get @b buff_len of random data.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[out] random_buf : Buffer to store random data.
 * @param[in] buf_len : Length of random buffer data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_get_random_numbers ( a5000plugntrust_t *ctx, uint8_t *random_buf, uint8_t buf_len );

/**
 * @brief Check if object exists.
 * @details Sends request to check if  object with @b object_id exists.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] object_id : Object ID.
 * @return @li @c  1 - Does exists,
 *         @li @c  2 - Doesn't exist,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_check_object_exist ( a5000plugntrust_t *ctx, uint32_t object_id );

/**
 * @brief Delete object.
 * @details Sends request to delete object with @b object_id.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] object_id : Object ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_delete_object ( a5000plugntrust_t *ctx, uint32_t object_id );

/**
 * @brief Read object data.
 * @details Sends request to read object data of object with @b object_id.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] object_id : Object ID.
 * @param[in] offset : Offset read data @b OPTIONAL: set 0 if not needed.
 * @param[in] read_len : Length to be read @b OPTIONAL: set 0 to read full data from object.
 * @param[out] data_buf : Read data buffer.
 * @param[out] data_len : Length of read data bffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_read_object ( a5000plugntrust_t *ctx, uint32_t object_id, uint16_t offset, 
                                    uint16_t read_len, uint8_t *data_buf, uint32_t *data_len );

/**
 * @brief Create/Write to binary object.
 * @details If binary object with @b object_id exist function will write @b data_buf to it.
 * If binary object doesn't exist it will be created and then data will be written.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[in] object_id : Object ID.
 * @param[in] offset : Offset of data to be written.
 * @param[in] data_len : Length of data to be written to binary object.
 * @param[in] data_buf : Buffer of data to be written to binary object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_write_binary_object ( a5000plugntrust_t *ctx, uint32_t object_id, uint16_t offset, 
                                            uint16_t data_len, uint8_t *data_buf );

/**
 * @brief Get Version info from Applet.
 * @details Sends request to read version info from Applet.
 * @param[in] ctx : Click context object.
 * See #a5000plugntrust_t object definition for detailed explanation.
 * @param[out] ver_info : Version info data.
 * See #ver_info object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Functions @b a5000plugntrust_select_card_manager and 
 * @b a5000plugntrust_select_applet needs to be called for this 
 * function to be successful. At the end of function it 
 * calls @b a5000plugntrust_end_apdu_session function.
 */
err_t a5000plugntrust_get_applet_info ( a5000plugntrust_t *ctx, a5000plugntrust_version_info_t *ver_info );

#ifdef __cplusplus
}
#endif
#endif // A5000PLUGNTRUST_H

/*! @} */ // a5000plugntrust

// ------------------------------------------------------------------------ END
