/*******************************************************************************
 * 
 * RapidIO IP Library Core
 * 
 * This file is part of the RapidIO IP library project
 * http://www.opencores.org/cores/rio/
 * 
 * Description:
 * This file can be used to automatically generate a VHDL-code that can 
 * encode/decode 8b/10b codegroups/characters.
 * 
 * To Do:
 * - Add more VHDL statements to generate both receiver and transmitter code 
 *   directly.
 * 
 * Author(s): 
 * - Magnus Rosenius, magro732@opencores.org 
 * 
 *******************************************************************************
 * 
 * Copyright (C) 2015 Authors and OPENCORES.ORG 
 * 
 * This source file may be used and distributed without 
 * restriction provided that this copyright statement is not 
 * removed from the file and that any derivative work contains 
 * the original copyright notice and the associated disclaimer. 
 * 
 * This source file is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU Lesser General 
 * Public License as published by the Free Software Foundation; 
 * either version 2.1 of the License, or (at your option) any 
 * later version. 
 * 
 * This source is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE. See the GNU Lesser General Public License for more 
 * details. 
 * 
 * You should have received a copy of the GNU Lesser General 
 * Public License along with this source; if not, download it 
 * from http://www.opencores.org/lgpl.shtml 
 * 
 *******************************************************************************/

/*
 * REMARK: 
 */ 
#include <stdio.h>


char table[256+12][8][20] =
  {
    {"--D0.0", "00", "000", "00000", "100111", "0100", "011000", "1011"},
    {"--D1.0", "01", "000", "00001", "011101", "0100", "100010", "1011"},
    {"--D2.0", "02", "000", "00010", "101101", "0100", "010010", "1011"},
    {"--D3.0", "03", "000", "00011", "110001", "1011", "110001", "0100"},
    {"--D4.0", "04", "000", "00100", "110101", "0100", "001010", "1011"},
    {"--D5.0", "05", "000", "00101", "101001", "1011", "101001", "0100"},
    {"--D6.0", "06", "000", "00110", "011001", "1011", "011001", "0100"},
    {"--D7.0", "07", "000", "00111", "111000", "1011", "000111", "0100"},
    {"--D8.0", "08", "000", "01000", "111001", "0100", "000110", "1011"},
    {"--D9.0", "09", "000", "01001", "100101", "1011", "100101", "0100"},
    {"--D10.0", "0A", "000", "01010", "010101", "1011", "010101", "0100"},
    {"--D11.0", "0B", "000", "01011", "110100", "1011", "110100", "0100"},
    {"--D12.0", "0C", "000", "01100", "001101", "1011", "001101", "0100"},
    {"--D13.0", "0D", "000", "01101", "101100", "1011", "101100", "0100"},
    {"--D14.0", "0E", "000", "01110", "011100", "1011", "011100", "0100"},
    {"--D15.0", "0F", "000", "01111", "010111", "0100", "101000", "1011"},
    {"--D16.0", "10", "000", "10000", "011011", "0100", "100100", "1011"},
    {"--D17.0", "11", "000", "10001", "100011", "1011", "100011", "0100"},
    {"--D18.0", "12", "000", "10010", "010011", "1011", "010011", "0100"},
    {"--D19.0", "13", "000", "10011", "110010", "1011", "110010", "0100"},
    {"--D20.0", "14", "000", "10100", "001011", "1011", "001011", "0100"},
    {"--D21.0", "15", "000", "10101", "101010", "1011", "101010", "0100"},
    {"--D22.0", "16", "000", "10110", "011010", "1011", "011010", "0100"},
    {"--D23.0", "17", "000", "10111", "111010", "0100", "000101", "1011"},
    {"--D24.0", "18", "000", "11000", "110011", "0100", "001100", "1011"},
    {"--D25.0", "19", "000", "11001", "100110", "1011", "100110", "0100"},
    {"--D26.0", "1A", "000", "11010", "010110", "1011", "010110", "0100"},
    {"--D27.0", "1B", "000", "11011", "110110", "0100", "001001", "1011"},
    {"--D28.0", "1C", "000", "11100", "001110", "1011", "001110", "0100"},
    {"--D29.0", "1D", "000", "11101", "101110", "0100", "010001", "1011"},
    {"--D30.0", "1E", "000", "11110", "011110", "0100", "100001", "1011"},
    {"--D31.0", "1F", "000", "11111", "101011", "0100", "010100", "1011"},
    {"--D0.1", "20", "001", "00000", "100111", "1001", "011000", "1001"},
    {"--D1.1", "21", "001", "00001", "011101", "1001", "100010", "1001"},
    {"--D2.1", "22", "001", "00010", "101101", "1001", "010010", "1001"},
    {"--D3.1", "23", "001", "00011", "110001", "1001", "110001", "1001"},
    {"--D4.1", "24", "001", "00100", "110101", "1001", "001010", "1001"},
    {"--D5.1", "25", "001", "00101", "101001", "1001", "101001", "1001"},
    {"--D6.1", "26", "001", "00110", "011001", "1001", "011001", "1001"},
    {"--D7.1", "27", "001", "00111", "111000", "1001", "000111", "1001"},
    {"--D8.1", "28", "001", "01000", "111001", "1001", "000110", "1001"},
    {"--D9.1", "29", "001", "01001", "100101", "1001", "100101", "1001"},
    {"--D10.1", "2A", "001", "01010", "010101", "1001", "010101", "1001"},
    {"--D11.1", "2B", "001", "01011", "110100", "1001", "110100", "1001"},
    {"--D12.1", "2C", "001", "01100", "001101", "1001", "001101", "1001"},
    {"--D13.1", "2D", "001", "01101", "101100", "1001", "101100", "1001"},
    {"--D14.1", "2E", "001", "01110", "011100", "1001", "011100", "1001"},
    {"--D15.1", "2F", "001", "01111", "010111", "1001", "101000", "1001"},
    {"--D16.1", "30", "001", "10000", "011011", "1001", "100100", "1001"},
    {"--D17.1", "31", "001", "10001", "100011", "1001", "100011", "1001"},
    {"--D18.1", "32", "001", "10010", "010011", "1001", "010011", "1001"},
    {"--D19.1", "33", "001", "10011", "110010", "1001", "110010", "1001"},
    {"--D20.1", "34", "001", "10100", "001011", "1001", "001011", "1001"},
    {"--D21.1", "35", "001", "10101", "101010", "1001", "101010", "1001"},
    {"--D22.1", "36", "001", "10110", "011010", "1001", "011010", "1001"},
    {"--D23.1", "37", "001", "10111", "111010", "1001", "000101", "1001"},
    {"--D24.1", "38", "001", "11000", "110011", "1001", "001100", "1001"},
    {"--D25.1", "39", "001", "11001", "100110", "1001", "100110", "1001"},
    {"--D26.1", "3A", "001", "11010", "010110", "1001", "010110", "1001"},
    {"--D27.1", "3B", "001", "11011", "110110", "1001", "001001", "1001"},
    {"--D28.1", "3C", "001", "11100", "001110", "1001", "001110", "1001"},
    {"--D29.1", "3D", "001", "11101", "101110", "1001", "010001", "1001"},
    {"--D30.1", "3E", "001", "11110", "011110", "1001", "100001", "1001"},
    {"--D31.1", "3F", "001", "11111", "101011", "1001", "010100", "1001"},
    {"--D0.2", "40", "010", "00000", "100111", "0101", "011000", "0101"},
    {"--D1.2", "41", "010", "00001", "011101", "0101", "100010", "0101"},
    {"--D2.2", "42", "010", "00010", "101101", "0101", "010010", "0101"},
    {"--D3.2", "43", "010", "00011", "110001", "0101", "110001", "0101"},
    {"--D4.2", "44", "010", "00100", "110101", "0101", "001010", "0101"},
    {"--D5.2", "45", "010", "00101", "101001", "0101", "101001", "0101"},
    {"--D6.2", "46", "010", "00110", "011001", "0101", "011001", "0101"},
    {"--D7.2", "47", "010", "00111", "111000", "0101", "000111", "0101"},
    {"--D8.2", "48", "010", "01000", "111001", "0101", "000110", "0101"},
    {"--D9.2", "49", "010", "01001", "100101", "0101", "100101", "0101"},
    {"--D10.2", "4A", "010", "01010", "010101", "0101", "010101", "0101"},
    {"--D11.2", "4B", "010", "01011", "110100", "0101", "110100", "0101"},
    {"--D12.2", "4C", "010", "01100", "001101", "0101", "001101", "0101"},
    {"--D13.2", "4D", "010", "01101", "101100", "0101", "101100", "0101"},
    {"--D14.2", "4E", "010", "01110", "011100", "0101", "011100", "0101"},
    {"--D15.2", "4F", "010", "01111", "010111", "0101", "101000", "0101"},
    {"--D16.2", "50", "010", "10000", "011011", "0101", "100100", "0101"},
    {"--D17.2", "51", "010", "10001", "100011", "0101", "100011", "0101"},
    {"--D18.2", "52", "010", "10010", "010011", "0101", "010011", "0101"},
    {"--D19.2", "53", "010", "10011", "110010", "0101", "110010", "0101"},
    {"--D20.2", "54", "010", "10100", "001011", "0101", "001011", "0101"},
    {"--D21.2", "55", "010", "10101", "101010", "0101", "101010", "0101"},
    {"--D22.2", "56", "010", "10110", "011010", "0101", "011010", "0101"},
    {"--D23.2", "57", "010", "10111", "111010", "0101", "000101", "0101"},
    {"--D24.2", "58", "010", "11000", "110011", "0101", "001100", "0101"},
    {"--D25.2", "59", "010", "11001", "100110", "0101", "100110", "0101"},
    {"--D26.2", "5A", "010", "11010", "010110", "0101", "010110", "0101"},
    {"--D27.2", "5B", "010", "11011", "110110", "0101", "001001", "0101"},
    {"--D28.2", "5C", "010", "11100", "001110", "0101", "001110", "0101"},
    {"--D29.2", "5D", "010", "11101", "101110", "0101", "010001", "0101"},
    {"--D30.2", "5E", "010", "11110", "011110", "0101", "100001", "0101"},
    {"--D31.2", "5F", "010", "11111", "101011", "0101", "010100", "0101"},
    {"--D0.3", "60", "011", "00000", "100111", "0011", "011000", "1100"},
    {"--D1.3", "61", "011", "00001", "011101", "0011", "100010", "1100"},
    {"--D2.3", "62", "011", "00010", "101101", "0011", "010010", "1100"},
    {"--D3.3", "63", "011", "00011", "110001", "1100", "110001", "0011"},
    {"--D4.3", "64", "011", "00100", "110101", "0011", "001010", "1100"},
    {"--D5.3", "65", "011", "00101", "101001", "1100", "101001", "0011"},
    {"--D6.3", "66", "011", "00110", "011001", "1100", "011001", "0011"},
    {"--D7.3", "67", "011", "00111", "111000", "1100", "000111", "0011"},
    {"--D8.3", "68", "011", "01000", "111001", "0011", "000110", "1100"},
    {"--D9.3", "69", "011", "01001", "100101", "1100", "100101", "0011"},
    {"--D10.3", "6A", "011", "01010", "010101", "1100", "010101", "0011"},
    {"--D11.3", "6B", "011", "01011", "110100", "1100", "110100", "0011"},
    {"--D12.3", "6C", "011", "01100", "001101", "1100", "001101", "0011"},
    {"--D13.3", "6D", "011", "01101", "101100", "1100", "101100", "0011"},
    {"--D14.3", "6E", "011", "01110", "011100", "1100", "011100", "0011"},
    {"--D15.3", "6F", "011", "01111", "010111", "0011", "101000", "1100"},
    {"--D16.3", "70", "011", "10000", "011011", "0011", "100100", "1100"},
    {"--D17.3", "71", "011", "10001", "100011", "1100", "100011", "0011"},
    {"--D18.3", "72", "011", "10010", "010011", "1100", "010011", "0011"},
    {"--D19.3", "73", "011", "10011", "110010", "1100", "110010", "0011"},
    {"--D20.3", "74", "011", "10100", "001011", "1100", "001011", "0011"},
    {"--D21.3", "75", "011", "10101", "101010", "1100", "101010", "0011"},
    {"--D22.3", "76", "011", "10110", "011010", "1100", "011010", "0011"},
    {"--D23.3", "77", "011", "10111", "111010", "0011", "000101", "1100"},
    {"--D24.3", "78", "011", "11000", "110011", "0011", "001100", "1100"},
    {"--D25.3", "79", "011", "11001", "100110", "1100", "100110", "0011"},
    {"--D26.3", "7A", "011", "11010", "010110", "1100", "010110", "0011"},
    {"--D27.3", "7B", "011", "11011", "110110", "0011", "001001", "1100"},
    {"--D28.3", "7C", "011", "11100", "001110", "1100", "001110", "0011"},
    {"--D29.3", "7D", "011", "11101", "101110", "0011", "010001", "1100"},
    {"--D30.3", "7E", "011", "11110", "011110", "0011", "100001", "1100"},
    {"--D31.3", "7F", "011", "11111", "101011", "0011", "010100", "1100"},
    {"--D0.4", "80", "100", "00000", "100111", "0010", "011000", "1101"},
    {"--D1.4", "81", "100", "00001", "011101", "0010", "100010", "1101"},
    {"--D2.4", "82", "100", "00010", "101101", "0010", "010010", "1101"},
    {"--D3.4", "83", "100", "00011", "110001", "1101", "110001", "0010"},
    {"--D4.4", "84", "100", "00100", "110101", "0010", "001010", "1101"},
    {"--D5.4", "85", "100", "00101", "101001", "1101", "101001", "0010"},
    {"--D6.4", "86", "100", "00110", "011001", "1101", "011001", "0010"},
    {"--D7.4", "87", "100", "00111", "111000", "1101", "000111", "0010"},
    {"--D8.4", "88", "100", "01000", "111001", "0010", "000110", "1101"},
    {"--D9.4", "89", "100", "01001", "100101", "1101", "100101", "0010"},
    {"--D10.4", "8A", "100", "01010", "010101", "1101", "010101", "0010"},
    {"--D11.4", "8B", "100", "01011", "110100", "1101", "110100", "0010"},
    {"--D12.4", "8C", "100", "01100", "001101", "1101", "001101", "0010"},
    {"--D13.4", "8D", "100", "01101", "101100", "1101", "101100", "0010"},
    {"--D14.4", "8E", "100", "01110", "011100", "1101", "011100", "0010"},
    {"--D15.4", "8F", "100", "01111", "010111", "0010", "101000", "1101"},
    {"--D16.4", "90", "100", "10000", "011011", "0010", "100100", "1101"},
    {"--D17.4", "91", "100", "10001", "100011", "1101", "100011", "0010"},
    {"--D18.4", "92", "100", "10010", "010011", "1101", "010011", "0010"},
    {"--D19.4", "93", "100", "10011", "110010", "1101", "110010", "0010"},
    {"--D20.4", "94", "100", "10100", "001011", "1101", "001011", "0010"},
    {"--D21.4", "95", "100", "10101", "101010", "1101", "101010", "0010"},
    {"--D22.4", "96", "100", "10110", "011010", "1101", "011010", "0010"},
    {"--D23.4", "97", "100", "10111", "111010", "0010", "000101", "1101"},
    {"--D24.4", "98", "100", "11000", "110011", "0010", "001100", "1101"},
    {"--D25.4", "99", "100", "11001", "100110", "1101", "100110", "0010"},
    {"--D26.4", "9A", "100", "11010", "010110", "1101", "010110", "0010"},
    {"--D27.4", "9B", "100", "11011", "110110", "0010", "001001", "1101"},
    {"--D28.4", "9C", "100", "11100", "001110", "1101", "001110", "0010"},
    {"--D29.4", "9D", "100", "11101", "101110", "0010", "010001", "1101"},
    {"--D30.4", "9E", "100", "11110", "011110", "0010", "100001", "1101"},
    {"--D31.4", "9F", "100", "11111", "101011", "0010", "010100", "1101"},
    {"--D0.5", "A0", "101", "00000", "100111", "1010", "011000", "1010"},
    {"--D1.5", "A1", "101", "00001", "011101", "1010", "100010", "1010"},
    {"--D2.5", "A2", "101", "00010", "101101", "1010", "010010", "1010"},
    {"--D3.5", "A3", "101", "00011", "110001", "1010", "110001", "1010"},
    {"--D4.5", "A4", "101", "00100", "110101", "1010", "001010", "1010"},
    {"--D5.5", "A5", "101", "00101", "101001", "1010", "101001", "1010"},
    {"--D6.5", "A6", "101", "00110", "011001", "1010", "011001", "1010"},
    {"--D7.5", "A7", "101", "00111", "111000", "1010", "000111", "1010"},
    {"--D8.5", "A8", "101", "01000", "111001", "1010", "000110", "1010"},
    {"--D9.5", "A9", "101", "01001", "100101", "1010", "100101", "1010"},
    {"--D10.5", "AA", "101", "01010", "010101", "1010", "010101", "1010"},
    {"--D11.5", "AB", "101", "01011", "110100", "1010", "110100", "1010"},
    {"--D12.5", "AC", "101", "01100", "001101", "1010", "001101", "1010"},
    {"--D13.5", "AD", "101", "01101", "101100", "1010", "101100", "1010"},
    {"--D14.5", "AE", "101", "01110", "011100", "1010", "011100", "1010"},
    {"--D15.5", "AF", "101", "01111", "010111", "1010", "101000", "1010"},
    {"--D16.5", "B0", "101", "10000", "011011", "1010", "100100", "1010"},
    {"--D17.5", "B1", "101", "10001", "100011", "1010", "100011", "1010"},
    {"--D18.5", "B2", "101", "10010", "010011", "1010", "010011", "1010"},
    {"--D19.5", "B3", "101", "10011", "110010", "1010", "110010", "1010"},
    {"--D20.5", "B4", "101", "10100", "001011", "1010", "001011", "1010"},
    {"--D21.5", "B5", "101", "10101", "101010", "1010", "101010", "1010"},
    {"--D22.5", "B6", "101", "10110", "011010", "1010", "011010", "1010"},
    {"--D23.5", "B7", "101", "10111", "111010", "1010", "000101", "1010"},
    {"--D24.5", "B8", "101", "11000", "110011", "1010", "001100", "1010"},
    {"--D25.5", "B9", "101", "11001", "100110", "1010", "100110", "1010"},
    {"--D26.5", "BA", "101", "11010", "010110", "1010", "010110", "1010"},
    {"--D27.5", "BB", "101", "11011", "110110", "1010", "001001", "1010"},
    {"--D28.5", "BC", "101", "11100", "001110", "1010", "001110", "1010"},
    {"--D29.5", "BD", "101", "11101", "101110", "1010", "010001", "1010"},
    {"--D30.5", "BE", "101", "11110", "011110", "1010", "100001", "1010"},
    {"--D31.5", "BF", "101", "11111", "101011", "1010", "010100", "1010"},
    {"--D0.6", "C0", "110", "00000", "100111", "0110", "011000", "0110"},
    {"--D1.6", "C1", "110", "00001", "011101", "0110", "100010", "0110"},
    {"--D2.6", "C2", "110", "00010", "101101", "0110", "010010", "0110"},
    {"--D3.6", "C3", "110", "00011", "110001", "0110", "110001", "0110"},
    {"--D4.6", "C4", "110", "00100", "110101", "0110", "001010", "0110"},
    {"--D5.6", "C5", "110", "00101", "101001", "0110", "101001", "0110"},
    {"--D6.6", "C6", "110", "00110", "011001", "0110", "011001", "0110"},
    {"--D7.6", "C7", "110", "00111", "111000", "0110", "000111", "0110"},
    {"--D8.6", "C8", "110", "01000", "111001", "0110", "000110", "0110"},
    {"--D9.6", "C9", "110", "01001", "100101", "0110", "100101", "0110"},
    {"--D10.6", "CA", "110", "01010", "010101", "0110", "010101", "0110"},
    {"--D11.6", "CB", "110", "01011", "110100", "0110", "110100", "0110"},
    {"--D12.6", "CC", "110", "01100", "001101", "0110", "001101", "0110"},
    {"--D13.6", "CD", "110", "01101", "101100", "0110", "101100", "0110"},
    {"--D14.6", "CE", "110", "01110", "011100", "0110", "011100", "0110"},
    {"--D15.6", "CF", "110", "01111", "010111", "0110", "101000", "0110"},
    {"--D16.6", "D0", "110", "10000", "011011", "0110", "100100", "0110"},
    {"--D17.6", "D1", "110", "10001", "100011", "0110", "100011", "0110"},
    {"--D18.6", "D2", "110", "10010", "010011", "0110", "010011", "0110"},
    {"--D19.6", "D3", "110", "10011", "110010", "0110", "110010", "0110"},
    {"--D20.6", "D4", "110", "10100", "001011", "0110", "001011", "0110"},
    {"--D21.6", "D5", "110", "10101", "101010", "0110", "101010", "0110"},
    {"--D22.6", "D6", "110", "10110", "011010", "0110", "011010", "0110"},
    {"--D23.6", "D7", "110", "10111", "111010", "0110", "000101", "0110"},
    {"--D24.6", "D8", "110", "11000", "110011", "0110", "001100", "0110"},
    {"--D25.6", "D9", "110", "11001", "100110", "0110", "100110", "0110"},
    {"--D26.6", "DA", "110", "11010", "010110", "0110", "010110", "0110"},
    {"--D27.6", "DB", "110", "11011", "110110", "0110", "001001", "0110"},
    {"--D28.6", "DC", "110", "11100", "001110", "0110", "001110", "0110"},
    {"--D29.6", "DD", "110", "11101", "101110", "0110", "010001", "0110"},
    {"--D30.6", "DE", "110", "11110", "011110", "0110", "100001", "0110"},
    {"--D31.6", "DF", "110", "11111", "101011", "0110", "010100", "0110"},
    {"--D0.7", "E0", "111", "00000", "100111", "0001", "011000", "1110"},
    {"--D1.7", "E1", "111", "00001", "011101", "0001", "100010", "1110"},
    {"--D2.7", "E2", "111", "00010", "101101", "0001", "010010", "1110"},
    {"--D3.7", "E3", "111", "00011", "110001", "1110", "110001", "0001"},
    {"--D4.7", "E4", "111", "00100", "110101", "0001", "001010", "1110"},
    {"--D5.7", "E5", "111", "00101", "101001", "1110", "101001", "0001"},
    {"--D6.7", "E6", "111", "00110", "011001", "1110", "011001", "0001"},
    {"--D7.7", "E7", "111", "00111", "111000", "1110", "000111", "0001"},
    {"--D8.7", "E8", "111", "01000", "111001", "0001", "000110", "1110"},
    {"--D9.7", "E9", "111", "01001", "100101", "1110", "100101", "0001"},
    {"--D10.7", "EA", "111", "01010", "010101", "1110", "010101", "0001"},
    {"--D11.7", "EB", "111", "01011", "110100", "1110", "110100", "1000"},
    {"--D12.7", "EC", "111", "01100", "001101", "1110", "001101", "0001"},
    {"--D13.7", "ED", "111", "01101", "101100", "1110", "101100", "1000"},
    {"--D14.7", "EE", "111", "01110", "011100", "1110", "011100", "1000"},
    {"--D15.7", "EF", "111", "01111", "010111", "0001", "101000", "1110"},
    {"--D16.7", "F0", "111", "10000", "011011", "0001", "100100", "1110"},
    {"--D17.7", "F1", "111", "10001", "100011", "0111", "100011", "0001"},
    {"--D18.7", "F2", "111", "10010", "010011", "0111", "010011", "0001"},
    {"--D19.7", "F3", "111", "10011", "110010", "1110", "110010", "0001"},
    {"--D20.7", "F4", "111", "10100", "001011", "0111", "001011", "0001"},
    {"--D21.7", "F5", "111", "10101", "101010", "1110", "101010", "0001"},
    {"--D22.7", "F6", "111", "10110", "011010", "1110", "011010", "0001"},
    {"--D23.7", "F7", "111", "10111", "111010", "0001", "000101", "1110"},
    {"--D24.7", "F8", "111", "11000", "110011", "0001", "001100", "1110"},
    {"--D25.7", "F9", "111", "11001", "100110", "1110", "100110", "0001"},
    {"--D26.7", "FA", "111", "11010", "010110", "1110", "010110", "0001"},
    {"--D27.7", "FB", "111", "11011", "110110", "0001", "001001", "1110"},
    {"--D28.7", "FC", "111", "11100", "001110", "1110", "001110", "0001"},
    {"--D29.7", "FD", "111", "11101", "101110", "0001", "010001", "1110"},
    {"--D30.7", "FE", "111", "11110", "011110", "0001", "100001", "1110"},
    {"--D31.7", "FF", "111", "11111", "101011", "0001", "010100", "1110"},
    {"--K28.0 /SC/", "1C", "000", "11100", "001111", "0100", "110000", "1011"},
    {"--K28.1 /M/", "3C", "001", "11100", "001111", "1001", "110000", "0110"},
    {"--K28.2 /ILLEGAL/", "5C", "010", "11100", "001111", "0101", "110000", "1010"},
    {"--K28.3 /PD/", "7C", "011", "11100", "001111", "0011", "110000", "1100"},
    {"--K28.4 /ILLEGAL/", "9C", "100", "11100", "001111", "0010", "110000", "1101"},
    {"--K28.5 /K/", "BC", "101", "11100", "001111", "1010", "110000", "0101"},
    {"--K28.6 /ILLEGAL/", "DC", "110", "11100", "001111", "0110", "110000", "1001"},
    {"--K28.7 /ILLEGAL/", "FC", "111", "11100", "001111", "1000", "110000", "0111"},
    {"--K23.7 /ILLEGAL/", "F7", "111", "10111", "111010", "1000", "000101", "0111"},
    {"--K27.7 /A/", "FB", "111", "11011", "110110", "1000", "001001", "0111"},
    {"--K29.7 /R/", "FD", "111", "11101", "101110", "1000", "010001", "0111"},
    {"--K30.7 /ILLEGAL/", "FE", "111", "11110", "011110", "1000", "100001", "0111"}
  };

int calculateDisparity(char *codeWord6, char *codeWord4, int disp)
{
  int i;
  int ones;
  int zeros;


  //printf("disp=%i:", disp);

  ones = 0;
  zeros = 0;
  for(i = 0; i < 6; i++)
  {
    if(codeWord6[i] == '1')
    {
      ones++;
      //printf("1");
    }
    if(codeWord6[i] == '0')
    {
      zeros++;
      //printf("0");
    }
  }

  if(zeros > ones)
  {
    disp = -1;
  }
  else if(zeros < ones)
  {
    disp = 1;
  }
  else
  {
    if(!strncmp("000111", codeWord6, 6))
    {
      disp = 1;
    }
    else if(!strncmp("111000", codeWord6, 6))
    {
      disp = -1;
    }
  }
  //printf(":0=%i;1=%i=>%i:", zeros, ones, disp);

  ones = 0;
  zeros = 0;
  for(i = 0; i < 4; i++)
  {
    if(codeWord4[i] == '1')
    {
      ones++;
      //printf("1");
    }
    if(codeWord4[i] == '0')
    {
      zeros++;
      //printf("0");
    }
  }

  if(zeros > ones)
  {
    disp = -1;
  }
  else if(zeros < ones)
  {
    disp = 1;
  }
  else
  {
    if(!strncmp("0011", codeWord4, 4))
    {
      disp = 1;
    }
    else if(!strncmp("1100", codeWord4, 4))
    {
      disp = -1;
    }
  }
  //printf(":0=%i;1=%i=>%i:", zeros, ones, disp);

  return disp;
}


int main(int argc, char *argv[])
{
  int i;
  int disp;

#if 1
  printf("if (disparity = '0') then\n");
  printf("  case input_i is\n");
  for(i = 0; i < 256+12; i++)
  {
    disp = calculateDisparity(table[i][4], table[i][5], -1);
    printf("    when \"%s%s\" =>\n", table[i][4], table[i][5]);
    printf("      %s\n", table[i][0]);
    printf("      invalid_o <= '%c';\n", (table[i][0][9]=='I')?'1':'0');
    printf("      control_o <= '%c';\n", (table[i][0][2]=='K')?'1':'0');
    printf("      character_o <= \"%s%s\";\n", table[i][2], table[i][3]);
    printf("      disparity <= '%c';\n", (disp==-1)?'0':'1');
  }
  printf("    when others =>\n");
  printf("      invalid_o <= '1';\n");
  printf("      control_o <= '0';\n");
  printf("      character_o <= \"00000000\";\n");
  printf("      disparity <= '0';\n");
  printf("  end case;\n");
  printf("else\n");
  printf("  case input_i is\n");
  for(i = 0; i < 256+12; i++)
  {
    disp = calculateDisparity(table[i][6], table[i][7], 1);
    printf("    when \"%s%s\" =>\n", table[i][6], table[i][7]);
    printf("      %s\n", table[i][0]);
    printf("      invalid_o <= '%c';\n", (table[i][0][9]=='I')?'1':'0');
    printf("      control_o <= '%c';\n", (table[i][0][2]=='K')?'1':'0');
    printf("      character_o <= \"%s%s\";\n", table[i][2], table[i][3]);
    printf("      disparity <= '%c';\n", (disp==-1)?'0':'1');
  }
  printf("    when others =>\n");
  printf("      invalid_o <= '1';\n");
  printf("      control_o <= '0';\n");
  printf("      character_o <= \"00000000\";\n");
  printf("      disparity <= '1';\n");
  printf("  end case;\n");
  printf("end if;\n");
#endif
#if 0
  printf("if (disparity = '0') then\n");
  printf("  case (control_i & character_i) is\n");
  for(i = 0; i < 256+12; i++)
  {
    disp = calculateDisparity(table[i][4], table[i][5], -1);
    printf("    when \"%s%s%s\" =>\n", (table[i][0][2]=='K')?"1":"0", table[i][2], table[i][3]);
    printf("      %s\n", table[i][0]);
    printf("      output_o <= \"%s%s\";\n", table[i][4], table[i][5]);
    printf("      disparity <= '%c';\n", (disp==-1)?'0':'1');
  }
  printf("    when others =>\n");
  printf("      output_o <= \"0000000000\";\n");
  printf("      disparity <= '0';\n");
  printf("  end case;\n");
  printf("else\n");
  printf("  case (control_i & character_i) is\n");
  for(i = 0; i < 256+12; i++)
  {
    disp = calculateDisparity(table[i][6], table[i][7], 1);
    printf("    when \"%s%s%s\" =>\n", (table[i][0][2]=='K')?"1":"0", table[i][2], table[i][3]);
    printf("      %s\n", table[i][0]);
    printf("      output_o <= \"%s%s\";\n", table[i][6], table[i][7]);
    printf("      disparity <= '%c';\n", (disp==-1)?'0':'1');
  }
  printf("    when others =>\n");
  printf("      output_o <= \"0000000000\";\n");
  printf("      disparity <= '1';\n");
  printf("  end case;\n");
  printf("end if;\n");
#endif
}