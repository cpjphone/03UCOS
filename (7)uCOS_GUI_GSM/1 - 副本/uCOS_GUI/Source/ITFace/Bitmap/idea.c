/*
  C-file generated by �C/GUI-BitmapConvert V2.30c, compiled Jul 23 2002, 12:06:33

  (c) 2002  Micrium, Inc.
  www.micrium.com

  (c) 1998-2002  Segger
  Microcontroller Systeme GmbH
  www.segger.com

  Source file: idea
  Dimensions:  82 * 59
  NumColors:   256
*/

#include "stdlib.h"

#include "GUI.H"

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

const GUI_COLOR Colorsidea[] = {
     0xFFFFFF,0xFEFEFE,0xFDFEFD,0xFCFEFE
    ,0xFCFEFD,0xFDFDFB,0xFEFBF9,0xFCF8F6
    ,0xFBF4F2,0xFAEEED,0xF9E8E8,0xF8E4E2
    ,0xF8E1DE,0xF8DFDC,0xF8DDDC,0xF8DEDE
    ,0xF8E1E0,0xF9E8E7,0xFBF3F2,0xFDF8F7
    ,0xFDFBFA,0xFCFDFC,0xFDFEFE,0xFCFDFD
    ,0xFCF9F8,0xFBF1F0,0xF8E5E4,0xF6D6D4
    ,0xF2C6C4,0xF1B4B2,0xEEA3A2,0xEB9593
    ,0xEB8886,0xE87C7A,0xE87472,0xE9706E
    ,0xE86D6B,0xE76A69,0xE86B68,0xE7706E
    ,0xE87572,0xEA7D7B,0xEA8987,0xEC9695
    ,0xEFA4A3,0xF1B4B4,0xF4C6C5,0xF5D6D6
    ,0xFCF1F0,0xFCF9F9,0xFDFDFD,0xFEFFFE
    ,0xFEFEFD,0xFDFCFC,0xFCF4F3,0xF5CFCE
    ,0xF2B3B3,0xEC9595,0xE5787A,0xE76262
    ,0xE95150,0xEC4442,0xF03B3A,0xF13635
    ,0xF43332,0xF73131,0xF83130,0xF9312F
    ,0xF93130,0xF53333,0xF23737,0xED3C3C
    ,0xE94544,0xE95252,0xE76464,0xE97B7A
    ,0xEE9696,0xF5CECE,0xF9E4E4,0xFBF4F3
    ,0xFDFCFB,0xFBF6F5,0xF8E4E3,0xF3C8C8
    ,0xF0A5A3,0xEA7E7C,0xE75C5B,0xEA4442
    ,0xC9274B,0xE82E37,0xF9302E,0xFA302E
    ,0xFA2F2E,0xFB2F2E,0xFB302F,0xFB302E
    ,0xFA302D,0xF8302F,0xF53130,0xF13736
    ,0xEA4544,0xE95E5B,0xEB7E7D,0xF0A3A3
    ,0xF4C7C6,0xF7E3E2,0xFBF6F4,0xFCFDFB
    ,0xFDFBFB,0xFBF0F0,0xF7D6D5,0xF1AFAD
    ,0xEA807E,0xEA5754,0xEE3C3A,0xF5302F
    ,0xF92F2D,0xFB2F2D,0xFB2E2E,0x991E66
    ,0xBC2256,0xFA2E2E,0xFA2E2D,0xFA2F2D
    ,0xFC2E2D,0xFB2E2D,0xF92E2D,0xF6302F
    ,0xEE3D3A,0xE95755,0xEC7F7E,0xF3AEAC
    ,0xF6D5D3,0xFCEFEF,0xFBFBFB,0xFAEEEE
    ,0xEDA1A0,0xE86C6A,0xEE4140,0xF43030
    ,0xFB2D2C,0xFA2D2D,0x6B1386,0x841876
    ,0xF92D2D,0xF92D2C,0xFA2D2C,0xFA2E2C
    ,0xF82E2D,0xF33030,0xEB4242,0xE96C6B
    ,0xEEA19F,0xFCEDED,0xFCFBFA,0xFCFCFC
    ,0xF7D3D2,0xEA6462,0xED3A39,0xF72E2D
    ,0xFA2E2B,0xFC2E2C,0xFB2D2D,0xF22D31
    ,0x390AA6,0x5E118F,0xFB2E2C,0xF92E2C
    ,0xF72E2E,0xEE3B3A,0xE96564,0xEFA09F
    ,0xF5D1D0,0xFEFCFC,0xFBF9F8,0xF8DFDE
    ,0xF0ADAD,0xEA6C6A,0xEB3B3A,0xFA2C2C
    ,0xFB2C2B,0xFA2C2B,0xFA2D2A,0xFA2C2D
    ,0xD8283F,0x1303BE,0x430BA1,0xF62C2F
    ,0xF92D2B,0xF92C2C,0xD62826,0xB92323
    ,0xF52C2B,0xFA2D2B,0xF72D2C,0xED3C3B
    ,0xF1ABA9,0xF8DBDA,0xFDF6F6,0xFBFEFE
    ,0xFAF0EE,0xF6CAC7,0xEC8987,0xED4443
    ,0xF62D2A,0xFA2C2A,0xFA2B2A,0xF92B2A
    ,0xFA2C29,0xF82C2A,0x8F196D,0x0301C9
    ,0x3D0AA5,0xF52A2E,0xF92C2A,0xFB2B2A
    ,0xF62C2A,0xD42927,0x490D0E,0x070100
    ,0x671213,0xF72C2B,0xFC2B2B,0xF72C2C
    ,0xEC8381,0xF3C4C2,0xFCEDEB,0xFBFDFB
    ,0xFAE4E3,0xF2B1AF,0xEB6563,0xF33131
    ,0xFC2A2A,0xFB2A2A,0xF92A2A,0xFA2A2A
    ,0xFA2B28,0xE82834,0x3007AC,0x0000CB
    ,0x3F0AA2,0xF6292C,0xF92A29,0xF72A2A
    ,0xF82A29,0xE42B29,0xA01E1C,0x500E0F
    ,0x140202,0x180203,0x54100F,0x551111
    ,0xBB2222,0xF92B29,0xFC2B2A,0xF33130
};

const GUI_LOGPALETTE Palidea = {
  256,	/* number of entries */
  0, 	/* No transparency */
  &Colorsidea[0]
};

const unsigned char acidea[] = {
  0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x03, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0E, 0x0F, 0x10, 0x0B, 0x11, 0x09, 0x12, 0x13, 0x14, 0x15, 0x02, 0x02, 0x16, 0x16, 0x01, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x24, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x1A, 0x30, 0x31, 0x32, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x33, 0x34, 0x34, 0x35, 0x36, 0x1A, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x42, 0x43, 0x43, 0x43, 0x43, 0x44, 0x44, 0x41, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x2D, 0x4D, 0x4E, 0x4F, 0x50, 0x02, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x15, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x3F, 0x58, 0x59, 0x5A, 0x5B, 0x5B, 0x5C, 0x5C, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5E, 0x5F, 0x5D, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x03, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x01, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x74, 0x79, 0x79, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7B, 0x7B, 0x74, 0x7B, 0x7B, 0x75, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x6C, 0x03, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x86, 0x87, 0x37, 0x88, 0x89, 0x8A, 0x8B, 0x7A, 0x7D, 0x7C, 0x7C, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x92, 0x8C, 0x8C, 0x8C, 0x8C, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x4D, 0x99, 0x9A, 0x02, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x9B, 0x30, 0x9C, 0x98, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0x8C, 0x8C, 0x8C, 0xA2, 0xA2, 0xA3, 0xA4, 0xA5, 0x8D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0xA6, 0x8C, 0xA6, 0xA6, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0xA6, 0x93, 0x93, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0x6D, 0xAD, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x03, 0x32, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0x91, 0xB3, 0x92, 0xB4, 0xB5, 0xB5, 0x8C, 0x8C, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0x92, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x92, 0x91, 0x92, 0xBD, 0xB3, 0xBE, 0xBF, 0xC0, 0x92, 0x91, 0x92, 0x8C, 0x8C, 0x8C, 0x8C, 0xC1, 0xB4, 0xB4, 0xB5, 0xB4, 0xB4, 0xC2, 0xC3, 0x24, 0xC4, 0xC5, 0xC6, 0x04, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xC7, 0x17, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCE, 0xCF, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xD7, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCE, 0xCF, 0xCF, 0xCE, 0xDE, 0xD7, 0xDF, 0x57, 0xE0, 0xE1, 0xE2, 0xE3, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x01, 0x16, 0x9A, 0xE4, 0xE5, 0xE6, 0xE7, 0xCE, 0xE8, 0xE8, 0xE9, 0xEA, 0xEA, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEA, 0xEA, 0xEB, 0xEB, 0xE8, 0xE9, 0xFE, 0xFF, 0x9D, 0xB0, 0x10, 0x14, 0x16, 0x34, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0xC7, 0x51, 0x6E, 0x4C, 0x64, 0xEA, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xF3, 0x8F, 0xD3, 0xEF, 0xA5, 0xEA, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xF2, 0xEC, 0xBE, 0xFB, 0xDC, 0xDA, 0xF6, 0xF5, 0xBE, 0xF9, 0xF9, 0xF5, 0xF2, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xE9, 0xEB, 0xF2, 0xF3, 0x64, 0x4C, 0x6E, 0x07, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x08, 0xC9, 0xE0, 0x63, 0xE9, 0xEC, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0x78, 0xB9, 0xEF, 0xD3, 0xD2, 0xEB, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xF2, 0xF2, 0xF2, 0xF3, 0xDA, 0xFB, 0xF5, 0xDC, 0xDA, 0xC0, 0xDC, 0xF9, 0xBF, 0xF3, 0xF4, 0xE9, 0xF2, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xE9, 0xF2, 0xE8, 0xF4, 0x72, 0xE0, 0xC9, 0x36, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x04, 0x12, 0xE1, 0x23, 0x95, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0xF4, 0x78, 0xB9, 0xD3, 0xD3, 0xB9, 0x58, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF3, 0xF4, 0xF6, 0xDB, 0xFC, 0xBE, 0xF6, 0xF6, 0xFB, 0xBF, 0xBF, 0xF6, 0xDC, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xE7, 0x4B, 0x2E, 0x12, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x08, 0xE1, 0xB1, 0xF3, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF1, 0xD2, 0xB9, 0xD3, 0xD3, 0xD3, 0xD4, 0xF1, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xF6, 0xBF, 0xF6, 0xDC, 0xDC, 0xFB, 0xDA, 0xF9, 0xF9, 0xF9, 0xDA, 0xDA, 0xDB, 0xF9, 0xFC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xC0, 0x23, 0xE1, 0x12, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x16, 0x07, 0xC9, 0x23, 0xF3, 0xEC, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0xF2, 0xB8, 0xA5, 0xD3, 0xEF, 0xD3, 0xD3, 0xD3, 0x77, 0xF4, 0xF2, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xBE, 0xF6, 0xFB, 0xDA, 0xDC, 0xDA, 0xF9, 0xF6, 0xBE, 0xF5, 0xF5, 0xF5, 0xDA, 0xF9, 0xDC, 0xD9, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF2, 0xEC, 0xEC, 0xC0, 0x22, 0x53, 0x6A, 0x04, 0x16, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x03, 0x9A, 0x6E, 0x55, 0xC0, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF3, 0x77, 0xEE, 0xD3, 0xEF, 0xEF, 0xEF, 0xD3, 0xBA, 0xB8, 0x78, 0x78, 0xF1, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xDC, 0xF8, 0xBE, 0xF4, 0xF4, 0xF6, 0xF9, 0xDC, 0xF6, 0xDC, 0xDA, 0xDA, 0xF6, 0xF3, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xEC, 0xEC, 0x95, 0x70, 0x9C, 0x31, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x16, 0x17, 0xE4, 0x4C, 0xFF, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xED, 0xA5, 0xD3, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEE, 0x8F, 0xEE, 0xB9, 0x78, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xFA, 0xFA, 0xFC, 0xDC, 0xFA, 0xBF, 0xBE, 0xF9, 0xF9, 0xDA, 0xDC, 0xF6, 0xF5, 0xF2, 0xEC, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF2, 0xF2, 0xEC, 0x3F, 0x4C, 0x10, 0x17, 0x01, 0x00, 0x00,
  0x01, 0x01, 0x03, 0x12, 0xE5, 0xCB, 0xEC, 0xEC, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x78, 0xEE, 0xD3, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xD3, 0xEE, 0xD3, 0xD3, 0x8E, 0xF4, 0xEC, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF5, 0xF5, 0xFC, 0xDC, 0xDC, 0xDA, 0xF6, 0xBE, 0xFC, 0xF6, 0xF3, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xEC, 0x64, 0x6F, 0xC8, 0xC7, 0x16, 0x00,
  0x33, 0x01, 0x50, 0xAC, 0xB1, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x77, 0xB9, 0xD3, 0xD3, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xD3, 0xD3, 0xD3, 0xB9, 0x58, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF4, 0xF6, 0xF6, 0xDA, 0xF9, 0xF9, 0xDB, 0xDA, 0xF5, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0xEC, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0xF4, 0xB1, 0x4D, 0x6C, 0xC7, 0x33,
  0x04, 0x04, 0xE2, 0xAB, 0x95, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x77, 0xB9, 0xEF, 0xD3, 0xEF, 0xD3, 0xEF, 0xEF, 0xD3, 0xEF, 0xEF, 0xEF, 0xEF, 0xEE, 0xF5, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xF6, 0xF6, 0xDC, 0xFC, 0xBE, 0xF6, 0xDB, 0xF7, 0xF5, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xEC, 0xF4, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xE7, 0x4C, 0xE2, 0x02, 0x33,
  0x16, 0x9A, 0xC9, 0x71, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0x78, 0xB9, 0xEF, 0xD3, 0xEF, 0xB9, 0xBA, 0xA5, 0xBA, 0xB9, 0xD3, 0xEF, 0xEF, 0xEF, 0xEE, 0xF5, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF6, 0xF9, 0xF6, 0xDA, 0xDA, 0xF6, 0xF9, 0xFA, 0xF4, 0xF2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xFC, 0xF5, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x65, 0xC9, 0x50, 0x01,
  0x02, 0x30, 0xAB, 0xC0, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF2, 0xF5, 0xEE, 0xD3, 0xD3, 0xD3, 0x8E, 0xB8, 0xF4, 0xF4, 0xF4, 0xF5, 0xD2, 0xB9, 0xEF, 0xD3, 0xD3, 0x78, 0xF2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF6, 0xF9, 0xDC, 0xF4, 0xF5, 0xFB, 0xBE, 0xDC, 0xFC, 0xF4, 0xF2, 0xF2, 0xF2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF9, 0xF9, 0xF6, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xFF, 0xAB, 0x30, 0x01,
  0x04, 0xC5, 0xB1, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xD2, 0xD3, 0xD3, 0xD3, 0x8F, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0x78, 0xB9, 0xD3, 0xD3, 0xF0, 0xF1, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF6, 0xDA, 0xF6, 0xBE, 0xF6, 0xDA, 0xF9, 0xF6, 0xDA, 0xDB, 0xFA, 0xFC, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xDC, 0xDB, 0xF6, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x23, 0xC5, 0x01,
  0x50, 0xE1, 0x8A, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF1, 0xA4, 0xEF, 0xEF, 0xA4, 0xF1, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xD2, 0xD3, 0xEF, 0xD3, 0x78, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF6, 0xDC, 0xBE, 0xF6, 0xDA, 0xDC, 0xF6, 0xF5, 0xF4, 0xF5, 0xDC, 0xDB, 0xDB, 0xDA, 0xDC, 0xFC, 0xBE, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xDC, 0xDB, 0xFC, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xCB, 0xE1, 0x14,
  0x51, 0xAB, 0xF1, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xB8, 0xB9, 0xEF, 0xD3, 0x77, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF5, 0xB9, 0xEF, 0xEF, 0x8F, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xEC, 0xF4, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF6, 0xF9, 0xDB, 0xDB, 0xF9, 0xFA, 0xF5, 0xF4, 0xF2, 0xF2, 0xF4, 0xF4, 0xDC, 0xF8, 0xFC, 0xFC, 0xF6, 0xFA, 0xDC, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xC0, 0xAB, 0x36,
  0xE2, 0x82, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0x58, 0xD3, 0xEF, 0xD3, 0x58, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF0, 0xEF, 0xEF, 0xA5, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xBE, 0xFC, 0xFC, 0xF5, 0xF4, 0xF4, 0xF6, 0xFC, 0xF6, 0xDC, 0xF7, 0xDC, 0xBE, 0xDA, 0xF9, 0xDA, 0xF9, 0xDB, 0xF9, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xE0, 0x0A,
  0x0C, 0xE6, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0x58, 0xD3, 0xEF, 0xD3, 0x58, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xBA, 0xEF, 0xEF, 0xA5, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xDC, 0xFA, 0xDC, 0xF6, 0xF6, 0xDC, 0xDA, 0xFC, 0xF4, 0xF4, 0xF6, 0xDB, 0xDA, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xB1, 0x0E,
  0x6E, 0x49, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xBE, 0xB9, 0xEF, 0xD3, 0xD2, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF5, 0xEE, 0xEF, 0xEF, 0x8E, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xBE, 0xDB, 0xFA, 0xF4, 0xF4, 0xF6, 0xDA, 0xDC, 0xDC, 0xBE, 0xDC, 0xDB, 0xDC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0x71, 0x9C,
  0x4D, 0xCB, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xBA, 0xEF, 0xEF, 0xA4, 0xF5, 0xF2, 0xF4, 0xEC, 0xEC, 0xEC, 0xF4, 0xF2, 0xF4, 0x78, 0xD3, 0xD3, 0xD3, 0x77, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xF9, 0xDA, 0xF6, 0xF9, 0xDC, 0xFC, 0xFA, 0xDC, 0xBE, 0xF7, 0xDB, 0xFC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0x3C, 0xC9,
  0xC9, 0xCB, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0x77, 0xD3, 0xEF, 0xD3, 0xD2, 0xF4, 0xF2, 0xF2, 0xEC, 0xEC, 0xF2, 0xF2, 0xBE, 0xEE, 0xEF, 0xD3, 0xB9, 0xF5, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xFA, 0xF9, 0xF5, 0xBE, 0xDC, 0xF9, 0xF5, 0xF4, 0xF5, 0xF9, 0xF9, 0xF5, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0x3C, 0xC9,
  0xC9, 0xCB, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF5, 0xA4, 0xD3, 0xD3, 0xD3, 0x8E, 0xBE, 0xF4, 0xF4, 0xF2, 0xF4, 0x58, 0xF0, 0xEF, 0xD3, 0xD3, 0xD2, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF2, 0xF6, 0xF8, 0xBE, 0xF4, 0xDC, 0xF9, 0xBE, 0xBE, 0xF6, 0xDB, 0xDC, 0xF4, 0xEC, 0xF4, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0x3C, 0xC9,
  0x37, 0xCB, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0x58, 0xB9, 0xD3, 0xEF, 0xD3, 0xB9, 0xA5, 0x8F, 0x8E, 0xBA, 0xB9, 0xEF, 0xD3, 0xD3, 0xA5, 0xF5, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xBE, 0xF9, 0xF6, 0xF6, 0xDC, 0xFA, 0xF6, 0xFC, 0xDC, 0xF8, 0xFC, 0xF2, 0xF4, 0xF6, 0xF6, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0x3C, 0x4D,
  0xC5, 0x71, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0x78, 0xB9, 0xD3, 0xD3, 0xD3, 0xEF, 0xD3, 0xEF, 0xEF, 0xD3, 0xD3, 0xD3, 0xBA, 0xBE, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0xF4, 0xF6, 0xF5, 0xF4, 0xDC, 0xF8, 0xBE, 0xF4, 0xF4, 0xBE, 0xF4, 0xF2, 0xF4, 0xDC, 0xF7, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0x65, 0x6E,
  0x0B, 0xE6, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0xF4, 0xBE, 0xA5, 0xB9, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xB9, 0xD2, 0xF5, 0xF4, 0xF2, 0xEC, 0xEC, 0xF4, 0xF4, 0xF2, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0xEC, 0xF4, 0xF4, 0xF4, 0xF6, 0xDB, 0xFC, 0xF4, 0xF4, 0xF2, 0xF4, 0xEC, 0xF5, 0xF9, 0xF9, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0x23, 0x10,
  0x85, 0xCA, 0xF4, 0xEC, 0xEC, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xEC, 0xF2, 0xF4, 0xBE, 0xD2, 0xA5, 0xF0, 0xBA, 0x8E, 0x77, 0xBE, 0xF4, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xD9, 0x25, 0x3A, 0xD9, 0xF4, 0xEC, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF2, 0xF2, 0xFC, 0xF8, 0xDA, 0xF6, 0xFC, 0xFC, 0xFC, 0xF6, 0xDA, 0xDB, 0xDB, 0xFC, 0xF2, 0xEC, 0xF4, 0xF4, 0xEC, 0xEC, 0xF4, 0xCA, 0x09,
  0xAE, 0xC4, 0xF4, 0xEC, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xF4, 0xD9, 0x25, 0x3A, 0x25, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xD9, 0x3A, 0x88, 0x88, 0x88, 0x25, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xEC, 0xF2, 0xF6, 0xF9, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB, 0xF9, 0xDC, 0xF5, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF3, 0xC4, 0x07,
  0x15, 0xC9, 0x3E, 0xEC, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0x3B, 0x88, 0x88, 0x88, 0x2A, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF5, 0x2A, 0x1F, 0x1F, 0x1F, 0x88, 0x56, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xF5, 0xFC, 0xF6, 0xF6, 0xF6, 0xF6, 0xFC, 0xF5, 0xF4, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xCB, 0x2E, 0x32,
  0x04, 0xE4, 0x23, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xD9, 0x88, 0x88, 0x88, 0x88, 0x3A, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF2, 0xBE, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xD9, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xEC, 0xF2, 0xEC, 0xEC, 0xEC, 0xF2, 0xEC, 0xEC, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xEC, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0x29, 0xE4, 0x01,
  0x02, 0x36, 0xC4, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xD9, 0x88, 0x88, 0x88, 0x88, 0x4A, 0xF4, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF5, 0x58, 0x56, 0xBF, 0xBF, 0x1F, 0x1F, 0x1F, 0x1F, 0xBE, 0xF4, 0xEC, 0xEC, 0xEC, 0xF4, 0xF4, 0xD9, 0x56, 0x27, 0x25, 0xBF, 0xF4, 0xF4, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xBE, 0x58, 0x77, 0x77, 0x56, 0xD9, 0xF4, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xC0, 0xC4, 0x36, 0x01,
  0x04, 0x6B, 0x6E, 0x71, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0x58, 0x88, 0x88, 0x88, 0x58, 0xF4, 0xEC, 0xEC, 0xF2, 0xEC, 0xBE, 0x3A, 0x1F, 0x1F, 0x1F, 0x3A, 0x1F, 0x1F, 0x1F, 0x1F, 0xBE, 0xF4, 0xF2, 0xEC, 0xEC, 0xF4, 0x58, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x25, 0xF4, 0xEC, 0xEC, 0xEC, 0xF5, 0x4A, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xBF, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0xF4, 0xE6, 0x9C, 0x9B, 0x01,
  0x01, 0x01, 0x19, 0x54, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xD9, 0x88, 0x88, 0x88, 0xD9, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0x77, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xF5, 0xF2, 0xF2, 0xF2, 0xF4, 0xBF, 0x1F, 0x1F, 0x1F, 0x3A, 0x1F, 0x1F, 0x1F, 0x56, 0xF4, 0xF2, 0xF4, 0x58, 0x1F, 0x1F, 0x1F, 0x3A, 0x1F, 0x1F, 0x1F, 0x3A, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF3, 0x54, 0x30, 0x04, 0x01,
  0x01, 0x01, 0x05, 0x6E, 0xB1, 0xF4, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xD9, 0x88, 0x88, 0xA5, 0x58, 0xF2, 0xF2, 0xF2, 0xF4, 0xBE, 0x1F, 0xA5, 0x1F, 0x1F, 0x77, 0x3A, 0x1F, 0x1F, 0x1F, 0x3A, 0xF4, 0xEC, 0xF2, 0xF4, 0xBE, 0x1F, 0x1F, 0x1F, 0x77, 0xBE, 0x77, 0x1F, 0x1F, 0x1F, 0xBE, 0xF2, 0xF4, 0x77, 0x1F, 0x1F, 0x58, 0xBE, 0x1F, 0x1F, 0x1F, 0x1F, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xEC, 0xF4, 0x23, 0x6E, 0x50, 0x02, 0x01,
  0x01, 0x01, 0x01, 0x51, 0x2D, 0x3F, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF2, 0xD9, 0x88, 0xA5, 0xA5, 0x78, 0xF4, 0xF2, 0xF2, 0xF2, 0x78, 0x1F, 0xA5, 0xA5, 0x1F, 0xBE, 0x78, 0xA5, 0x1F, 0xA5, 0x3A, 0xF4, 0xF2, 0xF4, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0x1F, 0x1F, 0x1F, 0xA5, 0xA5, 0x1F, 0xBE, 0xF2, 0xF2, 0xBF, 0x3A, 0x77, 0xFC, 0x77, 0x1F, 0xA5, 0xA5, 0x1F, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0x8A, 0x2D, 0x36, 0x01, 0x01, 0x33,
  0x01, 0x01, 0x01, 0x04, 0x11, 0x4C, 0xF4, 0xEC, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF2, 0x58, 0xA5, 0xBA, 0xA4, 0x77, 0xF4, 0xF2, 0xF2, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0x3A, 0xF4, 0xBF, 0xA5, 0xA5, 0xA5, 0x3A, 0xF4, 0xF2, 0xF2, 0xF4, 0x3A, 0xA5, 0xA5, 0xA5, 0x8F, 0x3A, 0x1F, 0x1F, 0x3A, 0x58, 0xF4, 0xF2, 0xF2, 0xF4, 0xBE, 0x3A, 0x1F, 0xA5, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF4, 0xAB, 0x11, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x02, 0x16, 0x14, 0xC5, 0x82, 0xF4, 0xF2, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF2, 0x78, 0xA5, 0xA4, 0xA4, 0x8E, 0xF4, 0xEC, 0xEC, 0xBE, 0x1F, 0xA5, 0xA5, 0xA5, 0x3A, 0xF4, 0x78, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xEC, 0xF4, 0xBE, 0x1F, 0xA5, 0xA5, 0xA5, 0x77, 0xF4, 0xBE, 0xBE, 0xBE, 0xF4, 0xF4, 0xEC, 0xEC, 0xBE, 0x3A, 0xA5, 0xA5, 0x8F, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xEC, 0xF2, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xF4, 0xE0, 0xC5, 0x6C, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x18, 0x37, 0xE6, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF4, 0x77, 0xA4, 0xA4, 0xA4, 0xBA, 0xBE, 0xF2, 0xF2, 0xBE, 0x1F, 0xA5, 0xA5, 0xA5, 0x8E, 0xBF, 0x77, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xF4, 0xF4, 0xBE, 0x1F, 0xA5, 0xA5, 0xA5, 0x1F, 0xFC, 0xF5, 0xD9, 0xBF, 0xD9, 0xF4, 0xF4, 0xBE, 0x3A, 0xA5, 0xA5, 0x1F, 0xBF, 0x1F, 0xA5, 0xA5, 0xA5, 0xBF, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF4, 0xB1, 0x4D, 0x18, 0x01, 0x16, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x36, 0xC9, 0xE6, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x8E, 0xA4, 0xA4, 0xA4, 0xA4, 0xBF, 0xF2, 0xF2, 0xF5, 0x3A, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xBF, 0xF4, 0xEC, 0xBE, 0x1F, 0xA5, 0xA5, 0xA5, 0xA5, 0x1F, 0x3A, 0x1F, 0xA5, 0x1F, 0xBE, 0xF2, 0xBF, 0xA5, 0xA5, 0xA5, 0x1F, 0xF6, 0xA5, 0xA5, 0xA5, 0xA5, 0x77, 0xF4, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xF4, 0xB1, 0xC9, 0x36, 0xC7, 0x16, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x08, 0xC9, 0xE6, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xBE, 0xA5, 0xA4, 0xA4, 0xA4, 0xA4, 0x77, 0xF4, 0xEC, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x3A, 0xBE, 0xF4, 0xF4, 0x3A, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xD9, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xB1, 0xC9, 0x36, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x32, 0x36, 0xC9, 0x23, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xBF, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA5, 0xBE, 0xF4, 0xF4, 0xBF, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xBF, 0xEC, 0xF4, 0xBF, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1F, 0xBE, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xBF, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0x4B, 0xC9, 0x4F, 0x03, 0x16, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0xC6, 0x9C, 0xCA, 0xF4, 0xF2, 0xF2, 0xF2, 0xF4, 0x8E, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x78, 0xF4, 0xF4, 0xBE, 0x77, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xBF, 0xF4, 0xF2, 0xBE, 0x8F, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x77, 0xF4, 0xF2, 0xFC, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xBF, 0xF4, 0xF2, 0xF4, 0xF4, 0xCA, 0x9C, 0xC6, 0xC7, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x18, 0x0D, 0x54, 0x3E, 0xF4, 0xEC, 0xF4, 0x77, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xD9, 0xF4, 0xF2, 0xF4, 0xBE, 0x8F, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x8E, 0xBF, 0xF4, 0xF4, 0xF2, 0xF2, 0xBE, 0x8F, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x77, 0xBE, 0xF2, 0xF4, 0xF4, 0x77, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x77, 0xF5, 0xEC, 0xF4, 0x8A, 0x54, 0x0E, 0x31, 0x16, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x50, 0x99, 0xE1, 0x22, 0xF4, 0xF4, 0xF5, 0x78, 0x8F, 0xA5, 0x8E, 0x8F, 0xFC, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xBE, 0xBF, 0xBF, 0xFC, 0xFC, 0x77, 0x77, 0xBF, 0xBE, 0xF4, 0xF4, 0xF4, 0xF2, 0xF2, 0xF4, 0xBE, 0xBF, 0x77, 0x77, 0x77, 0xBF, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF4, 0xFC, 0xBF, 0xBF, 0xBE, 0xBF, 0x77, 0x77, 0xBF, 0xF4, 0xF4, 0xF5, 0x28, 0xE1, 0xE2, 0x86, 0x03, 0x01, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x13, 0x0E, 0xC4, 0x3C, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF2, 0xF2, 0xF4, 0xF4, 0xF2, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF2, 0xF4, 0xF2, 0xF4, 0xF4, 0xF4, 0x71, 0xC4, 0xC5, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x16, 0x9A, 0x19, 0x9C, 0xAB, 0xCB, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0x3C, 0xAB, 0x9C, 0x6D, 0x35, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x01, 0x01, 0x01, 0x50, 0x85, 0x4D, 0xAB, 0x3C, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0x71, 0xAB, 0x4D, 0x99, 0x6C, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x16, 0x6C, 0x19, 0x6E, 0x83, 0x23, 0xFF, 0xF4, 0xF4, 0xF2, 0xEC, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xF4, 0x3F, 0x22, 0x83, 0x6E, 0x30, 0x6C, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x32, 0xC6, 0xE4, 0x68, 0xAB, 0xE6, 0x46, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xEC, 0xEC, 0xF4, 0xF4, 0xF4, 0x3E, 0xB1, 0x67, 0x2E, 0xE4, 0xC6, 0xAD, 0x16, 0x16, 0x16, 0x16, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x03, 0xC7, 0x35, 0x36, 0xE4, 0x4D, 0xE5, 0xCA, 0xE6, 0xCB, 0xC0, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF2, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0x95, 0x3C, 0xB1, 0x4C, 0xE5, 0x4D, 0xE4, 0x36, 0x50, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x16, 0x00, 0x16, 0x04, 0x04, 0x05, 0xAE, 0x30, 0x11, 0x6E, 0x2E, 0x38, 0x67, 0x4C, 0x82, 0xB1, 0x65, 0x71, 0x3C, 0x3C, 0x3C, 0x3C, 0x71, 0xE6, 0x23, 0x82, 0x4C, 0x67, 0x38, 0x2E, 0x6E, 0x11, 0x12, 0x18, 0x05, 0x04, 0x02, 0x02, 0x16, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

const GUI_BITMAP bmidea = {
 82, /* XSize */
 59, /* YSize */
 82, /* BytesPerLine */
 8, /* BitsPerPixel */
 acidea,  /* Pointer to picture data (indices) */
 &Palidea  /* Pointer to palette */
};

/* *** End of file *** */
