/*
 *  @brief A simple FIFO, whose elements are pairs of integers,
 *      one being the id of the producer and the other the value produced
 *
 * @remarks safe, non busy waiting version
 *
 *  The following operations are defined:
 *     \li insertion of a value
 *     \li retrieval of a value.
 *
 * \author (2016-2022) Artur Pereira <artur at ua.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdint.h>

#include "fifo.h"
#include "delays.h"
#include "thread.h"
#include "dbc.h"

namespace fifo
{
    /** \brief internal storage size of <em>FIFO memory</em> */


    static pthread_mutex_t accessCR = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t fifoNotFull = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t fifoNotEmpty = PTHREAD_COND_INITIALIZER;

    /* ************************************************* */

    /* create a FIFO in shared memory and initialize it */
    void create(FIFO * fifo)
    {
        require(fifo == NULL, "fifo must not exist");

        /* create the shared memory */
        fifo = new FIFO;
        if (fifo == NULL)
        {
            perror("Fail creating fifo");
            exit(EXIT_FAILURE);
        }

        /* init fifo */
        for (uint32_t i = 0; i < FIFOSZ; i++)
        {
            fifo->slot[i].id = 99;
            fifo->slot[i].value = 99999;
        }
        fifo->ii = fifo->ri = 0;
        fifo->cnt = 0;
    }

    /* ************************************************* */

    void destroy(FIFO * fifo)
    {
        require(fifo != NULL, "fifo must exist");

        /* destroy the shared memory */
        if (fifo != NULL)
        {
            delete fifo;
            fifo = NULL;
        }
    }

    /* ************************************************* */

    /* Insertion of a pair <id, value> into the FIFO  */
    static bool isFull(FIFO * fifo)
    {
        require(fifo != NULL, "fifo must exist");

        return fifo->cnt == FIFOSZ;
    }

    /* ************************************************* */

    /* Check if FIFO is empty */
    static bool isEmpty(FIFO * fifo)
    {
        require(fifo != NULL, "fifo must exist");

        return fifo->cnt == 0;
    }

    /* ************************************************* */

    /* Insertion of a pait <id, value> into the FIFO  */
    void in(uint32_t id, uint32_t value, FIFO *fifo)
    {
        require(fifo != NULL, "fifo must exist");

        mutex_lock(&accessCR);

        /* wait while fifo is full */
        while (isFull(fifo))
        {
            cond_wait(&fifoNotFull, &accessCR); 
        }

        /* Insert pair */
        fifo->slot[fifo->ii].value = value;
        bwRandomDelay(10000, 100000);
        fifo->slot[fifo->ii].id = id;
        fifo->ii = (fifo->ii + 1) % FIFOSZ;
        fifo->cnt++;

        cond_broadcast(&fifoNotEmpty);
        mutex_unlock(&accessCR);
    }

    /* ************************************************* */

    /* Retrieval of a pair <id, value> from the FIFO */

    void out(uint32_t * idp, uint32_t * valuep, FIFO * fifo)
    {
        require(fifo != NULL, "fifo must exist");

        mutex_lock(&accessCR);

        /* wait while fifo is empty */
        while (isEmpty(fifo))
        {
            cond_wait(&fifoNotEmpty, &accessCR); 
        }

        /* Retrieve pair */
        *valuep = fifo->slot[fifo->ri].value;
        fifo->slot[fifo->ri].value = 99999;
        *idp = fifo->slot[fifo->ri].id;
        fifo->slot[fifo->ri].id = 99;
        fifo->ri = (fifo->ri + 1) % FIFOSZ;
        fifo->cnt--;

        cond_broadcast(&fifoNotFull);
        mutex_unlock(&accessCR);
    }

    /* ************************************************* */

}
