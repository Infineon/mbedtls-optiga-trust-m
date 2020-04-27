/*
 * Amazon FreeRTOS V1.4.7
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


#ifndef __AWS_CLIENTCREDENTIAL__H__
#define __AWS_CLIENTCREDENTIAL__H__

/*
 * Include for device certificate and private key
 */
#include "aws_clientcredential_keys.h"

//External wifi connectivity to the internet other wise it will connect to local wifi AP
#define EXTERNAL_WIFI    1
/*
 * Wi-Fi network to join.
 */
#if (EXTERNAL_WIFI==1)
#define clientcredentialWIFI_SSID       "iPhoneArtem"
#define clientcredentialWIFI_PASSWORD   "AWSTrustX"
#endif
/*
 * Password needed to join Wi-Fi network.
 */
#if (EXTERNAL_WIFI==0)
#define clientcredentialWIFI_SSID       "raspi-webgui"
#define clientcredentialWIFI_PASSWORD   "password123"
//#define clientcredentialWIFI_PASSWORD   "ChangeMe" //Default raspberry pi webgui software password
#endif

/**
 * @brief Security type
 * WPA2 Security, @see WIFISecurity_t
 * Possible values are - eWiFiSecurityOpen, eWiFiSecurityWEP, eWiFiSecurityWPA,
 * eWiFiSecurityWPA2
 */
#define clientcredentialWIFI_SECURITY                eWiFiSecurityWPA2

#endif /* ifndef __AWS_CLIENTCREDENTIAL__H__ */
