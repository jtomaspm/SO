#include "fifo.h"
class shared_data
{
    public:
        fifo::FIFO * free_buffers;
        fifo::FIFO * pending_requests;
        char * buffers [5];

};

