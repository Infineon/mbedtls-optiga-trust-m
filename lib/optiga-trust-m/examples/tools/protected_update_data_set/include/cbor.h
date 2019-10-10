/**
* \copyright
* MIT License
*
* Copyright (c) 2019 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
* \endcopyright
*
* \author Infineon Technologies AG
*
* \file cbor.h
*
* \brief   This file defines APIs, types and data structures used for cbor format coding.
*
* \ingroup  grProtectedUpdateTool
*
* @{
*/
#define CBOR_MAJOR_TYPE_0					(0x00)
#define CBOR_MAJOR_TYPE_1					(0x20)
#define CBOR_MAJOR_TYPE_2					(0x40)
#define CBOR_MAJOR_TYPE_3					(0x60)
#define CBOR_MAJOR_TYPE_4					(0x80)
#define CBOR_MAJOR_TYPE_5					(0xA0)
#define CBOR_MAJOR_TYPE_7					(0xF6)

#define CBOR_ADDITIONAL_TYPE_0x17           (0x17)
#define CBOR_ADDITIONAL_TYPE_0x18           (0x18)
#define CBOR_ADDITIONAL_TYPE_0x19           (0x19)
#define CBOR_ADDITIONAL_TYPE_0x1A           (0x1A)

// Encodes cbor NULL
int cbor_set_null(unsigned char * buffer, unsigned short * offset);
// Encodes cbor array
int cbor_set_array_of_data(unsigned char * buffer, unsigned int value, unsigned short * offset);
// Encodes cbor unsiged integer
int cbor_set_unsigned_integer(unsigned char * buffer, unsigned int value, unsigned short * offset);
// Encodes cbor unsiged integer
int cbor_set_signed_integer(unsigned char * buffer, signed int value, unsigned short * offset);
// Encodes cbor byte string
int cbor_set_byte_string(unsigned char * buffer, unsigned int value, unsigned short * offset);
// Set the tag for map
void cbor_set_map_tag(unsigned char * buffer, unsigned char map_number, unsigned short * offset);
// Encodes cbor map for unsigned type
int cbor_set_map_unsigned_type(unsigned char * buffer, unsigned int key_data_item, unsigned int value_data_item, unsigned short * offset);
// Encodes cbor map for signed type
int cbor_set_map_signed_type(unsigned char * buffer, unsigned int key_data_item, signed int value_data_item, unsigned short * offset);
// Encodes cbor map for byte array type
int cbor_set_map_byte_string_type(unsigned char * buffer, unsigned int key_data_item, unsigned char * value_data_item, unsigned short value_data_item_len, unsigned short * offset);

/**
* @}
*/