typedef struct {
    int* encoding;
    int encodingSize;
    int currentSection;
    int currentExhaust;
} RLEIterator;


RLEIterator* rLEIteratorCreate(int* encoding, int encodingSize) {
    RLEIterator* iterator = (RLEIterator*)malloc(sizeof(RLEIterator));
    iterator->encoding = encoding;
    iterator->encodingSize = encodingSize;
    iterator->currentSection = 0;
    iterator->currentExhaust = 0;
    return iterator;
}

int rLEIteratorNext(RLEIterator* obj, int n) {
    // if we have exhausted everything already, return 1
    if (obj->currentSection * 2 >= obj->encodingSize) {
        return -1;
    }

    int lastExhaust = obj->encoding[obj->currentSection * 2 + 1];
    while (n > 0 && obj->currentSection * 2 < obj->encodingSize) {
        int leftToExhaust = obj->encoding[obj->currentSection * 2] - obj->currentExhaust;
        
        // if nothing can be exhausted out of the current section anyways, simply move on
        if (leftToExhaust == 0) {
            obj->currentExhaust = 0;
            obj->currentSection++;
        }
        // if the entire current section can be exhausted, exhaust it and move to the next section
        else if (n >= leftToExhaust) {
            n -= leftToExhaust;
            lastExhaust = obj->encoding[obj->currentSection * 2 + 1];
            obj->currentExhaust = 0;
            obj->currentSection++;
        }
        // if there is enough available in the available section to not completely exhaust it, increment the current exhaust counter and return the current exhaust count. The section will remain the same for subsequent calls
        else if (n < leftToExhaust) {
            lastExhaust = obj->encoding[obj->currentSection * 2 + 1];
            obj->currentExhaust += n;
            return lastExhaust;
        }


    }

    // if we have exhausted the required amount but exited the loop for whatever reason, return the last exhausted amount
    if (n == 0) {
        return lastExhaust;
    }
    return -1;
}

// since only the iterator itself is allocated, 
void rLEIteratorFree(RLEIterator* obj) {
    free(obj);
}
