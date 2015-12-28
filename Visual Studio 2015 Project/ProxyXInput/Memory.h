#pragma once

typedef void (*Code)();

void writeByte(int offset, unsigned char byte);
Code* allocateCode(int size, unsigned char* code);
