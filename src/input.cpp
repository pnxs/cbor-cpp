/*
   Copyright 2014-2015 Stanislav Ovsyannikov

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

	   Unless required by applicable law or agreed to in writing, software
	   distributed under the License is distributed on an "AS IS" BASIS,
	   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	   See the License for the specific language governing permissions and
	   limitations under the License.
*/

#include "input.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>
using std::cout;

namespace cbor {

input::input(void *data, int size)
{
    _data = (unsigned char *) data;
    _size = size;
    _offset = 0;
}

input::input(const void *data, int size) {
    _data = (unsigned char *) data;
    _size = size;
    _offset = 0;
}

input::~input() {

}

bool input::has_bytes(int count) {
    return _size - _offset >= count;
}

void input::advance(int bytes)
{
    //cout << "advance: " << bytes << "\n";
    _offset += bytes;
}

unsigned char input::get_byte() {
    return _data[_offset++];
}

unsigned short input::get_short() {
    unsigned short value = ((unsigned short) _data[_offset] << 8) | ((unsigned short) _data[_offset + 1]);
    _offset += 2;
    return value;
}

unsigned int input::get_int() {
    unsigned int value = \
            ((unsigned int) _data[_offset] << 24) |
            ((unsigned int) _data[_offset + 1] << 16) |
            ((unsigned int) _data[_offset + 2] << 8) |
            ((unsigned int) _data[_offset + 3]);
    _offset += 4;
    return value;
}


unsigned long long input::get_long() {
    unsigned long long value = ((unsigned long long) _data[_offset] << 56) |
                               ((unsigned long long) _data[_offset + 1] << 48) |
                               ((unsigned long long) _data[_offset + 2] << 40) |
                               ((unsigned long long) _data[_offset + 3] << 32) |
                               ((unsigned long long) _data[_offset + 4] << 24) |
                               ((unsigned long long) _data[_offset + 5] << 16) |
                               ((unsigned long long) _data[_offset + 6] << 8) |
                               ((unsigned long long) _data[_offset + 7]);
    _offset += 8;
    return value;
}

float input::get_float() {
    union {
        uint32_t uint32_val;
        float float_val;
    } u;

    u.uint32_val = get_int();
    //return *(float*)&t;
    return u.float_val;
}

double input::get_double() {
    union {
        uint64_t uint64_val;
        double double_val;
    } u;

    u.uint64_val = get_long();
    //return *(double*)&t;
    return u.double_val;
}

void input::get_bytes(void *to, int count) {
    memcpy(to, _data + _offset, count);
    _offset += count;
}

uint8_t input::peek_byte() const
{
    return _data[_offset];
}

std::string input::toString() const
{
    return hexlify(_data, _size);
}

}