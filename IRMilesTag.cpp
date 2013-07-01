#include "IRMilesTag.h"
#include "IRremoteInt.h"
#include "IRMilesTagDefines.h"

void IRMilesTagSend::sendShot(unsigned int player, unsigned short team, unsigned int damage) {
    this->enableIROut(38);
    this->mark(MT_SIGNAL_HEADER);
    this->space(MT_SIGNAL_SPACE);

    int data = MT_SHOT(player, team, damage);

    for(int i = 0; i < MT_SIGNAL_SHOT_BITS; i ++)
    {
        if ((data >> i) & 1) {
        	this->mark(MT_SIGNAL_ONE);
        } else {
        	this->mark(MT_SIGNAL_ZERO);
        }
		this->space(MT_SIGNAL_SPACE);
    }
	this->space(0);
}


IRMilesTagRecv::IRMilesTagRecv(int recvpin) : IRrecv(recvpin) {}


int IRMilesTagRecv::recv(decode_results *results) {

	results->rawbuf = irparams.rawbuf;
	results->rawlen = irparams.rawlen;

	if (irparams.rcvstate != STATE_STOP) {
		return ERR;
	}

	unsigned long data = 0;
    int offset = 1;

    if (!MATCH_MARK(results->rawbuf[offset], MT_SIGNAL_HEADER)) {
        return ERR;
    }
    
	offset++;

    int numBits = 0;
    if (results->rawlen >= MT_SIGNAL_MESSAGE_BITS * 2 ) {
    	numBits = MT_SIGNAL_MESSAGE_BITS;
    } else if (results->rawlen >= MT_SIGNAL_SHOT_BITS * 2 ) {
    	numBits = MT_SIGNAL_SHOT_BITS;
    } else {
    	return ERR;
    }

    for (int i = 0; i < numBits; i++) {

	    if (!MATCH_MARK(results->rawbuf[offset], MT_SIGNAL_SPACE)) {
	        return ERR;
	    }
	    
		offset++;

    	if (MATCH_MARK(results->rawbuf[offset], MT_SIGNAL_ONE)) {
            data = data | (1 << i);
        } else if (MATCH_MARK(results->rawbuf[offset], MT_SIGNAL_ZERO)) {
        	// Leave as 0, so do nothing...
		} else {
        	return ERR;
        }

        offset ++;
    }

	results->value       = data;
    results->decode_type = MILES_TAG_II;
    results->bits        = numBits;
    return DECODED;
}
