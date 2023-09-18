#ifndef buffer_h
#define buffer_h

class Buffer
{
private:
    int index;
    int size;
    bool full;
    float *inner;

public:
    Buffer(int size);
    Buffer();
    ~Buffer();
    bool is_full();
    void push(float value);
    float average();
    void clear();
};

#endif
