#include "buffer.h"

Buffer::Buffer() : Buffer(100) {}

Buffer::Buffer(int size)
{
    this->size = size;
    this->index = 0;
    this->full = false;
    this->inner = new float[size];
}

Buffer::~Buffer()
{
    delete[] this->inner;
}

bool Buffer::is_full()
{
    return this->full;
}

float Buffer::average()
{
    auto total = 0.0f;
    int count = this->full ? this->size : this->index;
    for (int i = 0; i < count; i++)
    {
        total += this->inner[i];
    }
    return total / count;
}

void Buffer::push(float value)
{
    this->inner[this->index] = value;
    index += 1;
    if (this->index >= this->size)
    {
        this->index = 0;
        this->full = true;
    }
}

void Buffer::clear()
{
    this->index = 0;
    this->full = false;
}
