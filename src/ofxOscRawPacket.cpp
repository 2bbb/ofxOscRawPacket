//
//  ofxOscRawPacket.cpp
//
//  Created by ISHII 2bit on 2018/06/07.
//

#include "ofxOscRawPacket.h"

#include "detail/ofx_osc_from_binary.h"
#include "detail/ofx_osc_to_binary.h"

ofBuffer ofxOscToBuffer(const ofxOscMessage &mess) {
    auto &&v = to_binary(mess);
    return {v.first, v.second};
}

ofBuffer ofxOscToBuffer(const ofxOscBundle &bundle) {
    auto &&v = to_binary(bundle);
    return {v.first, v.second};
}

std::vector<ofxOscMessage> ofxOscFromBuffer(const ofBuffer &buf) {
    return process_packet(buf.getData(), buf.size());
}
