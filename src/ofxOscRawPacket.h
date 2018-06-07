//
//  ofxOscRawPacket.h
//
//  Created by ISHII 2bit on 2018/06/07.
//

#ifndef ofxOscRawPacket_h
#define ofxOscRawPacket_h

#include "ofxOscMessage.h"
#include "ofxOscBundle.h"
#include "ofFileUtils.h"

ofBuffer ofxOscToBuffer(const ofxOscMessage &mess);
ofBuffer ofxOscToBuffer(const ofxOscBundle &bundle);
std::vector<ofxOscMessage> ofxOscFromBuffer(const ofBuffer &buf);

#endif /* ofxOscRawPacket_hpp */
