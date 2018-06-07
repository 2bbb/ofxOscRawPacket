//
//  ofxOscOnZmq.h
//
//  Created by ISHII 2bit on 2018/06/07.
//

#ifndef ofxOscOnZmq_h
#define ofxOscOnZmq_h

#include "UdpSocket.h"
#include "ofxOscSender.h"

namespace {
    void append_message(const ofxOscMessage &message, osc::OutboundPacketStream &p) {
        p << osc::BeginMessage(message.getAddress().c_str());
        for(size_t i = 0; i < message.getNumArgs(); ++i) {
            switch(message.getArgType(i)){
                case OFXOSC_TYPE_INT32:
                    p << message.getArgAsInt32(i);
                    break;
                case OFXOSC_TYPE_INT64:
                    p << (osc::int64)message.getArgAsInt64(i);
                    break;
                case OFXOSC_TYPE_FLOAT:
                    p << message.getArgAsFloat(i);
                    break;
                case OFXOSC_TYPE_DOUBLE:
                    p << message.getArgAsDouble(i);
                    break;
                case OFXOSC_TYPE_STRING:
                    p << message.getArgAsString(i).c_str();
                    break;
                case OFXOSC_TYPE_SYMBOL:
                    p << osc::Symbol(message.getArgAsString(i).c_str());
                    break;
                case OFXOSC_TYPE_CHAR:
                    p << message.getArgAsChar(i);
                    break;
                case OFXOSC_TYPE_MIDI_MESSAGE:
                    p << osc::MidiMessage(message.getArgAsMidiMessage(i));
                    break;
                case OFXOSC_TYPE_TRUE: case OFXOSC_TYPE_FALSE:
                    p << message.getArgAsBool(i);
                    break;
                case OFXOSC_TYPE_NONE:
                    p << osc::NilType();
                    break;
                case OFXOSC_TYPE_TRIGGER:
                    p << osc::InfinitumType();
                    break;
                case OFXOSC_TYPE_TIMETAG:
                    p << osc::TimeTag(message.getArgAsTimetag(i));
                    break;
                case OFXOSC_TYPE_RGBA_COLOR:
                    p << osc::RgbaColor(message.getArgAsRgbaColor(i));
                    break;
                case OFXOSC_TYPE_BLOB: {
                    ofBuffer buff = message.getArgAsBlob(i);
                    p << osc::Blob(buff.getData(), (unsigned long)buff.size());
                    break;
                }
                default:
                    ofLogError("ofxOscSender") << "appendMessage(): bad argument type "
                    << message.getArgType(i) << " '" << (char) message.getArgType(i) << "'";
                    break;
            }
        }
        p << osc::EndMessage;
    }
    
    void append_bundle(const ofxOscBundle &bundle_, osc::OutboundPacketStream &p) {
        ofxOscBundle bundle = bundle_;
        // recursively serialise the bundle
        p << osc::BeginBundleImmediate;
        for(int i = 0; i < bundle.getBundleCount(); i++){
            append_bundle(bundle.getBundleAt(i), p);
        }
        for(int i = 0; i < bundle.getMessageCount(); i++){
            append_message(bundle.getMessageAt(i), p);
        }
        p << osc::EndBundle;
    }
    std::pair<const char *, std::size_t> to_binary(const ofxOscMessage &message, bool wrapInBundle = false) {
        static const int OUTPUT_BUFFER_SIZE = 327680;
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
        
        if(wrapInBundle) {
            p << osc::BeginBundleImmediate;
        }
        
        append_message(message, p);
        
        if(wrapInBundle) {
            p << osc::EndBundle;
        }
        
        return std::make_pair(p.Data(), p.Size());
    }
    
    std::pair<const char *, std::size_t> to_binary(const ofxOscBundle &bundle){
        // setting this much larger as it gets trimmed down to the size its using before being sent.
        // TODO: much better if we could make this dynamic? Maybe have ofxOscBundle return its size?
        static const int OUTPUT_BUFFER_SIZE = 327680;
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
        
        // serialise the bundle and send
        append_bundle(bundle, p);
        return std::make_pair(p.Data(), p.Size());
    }
};

#endif /* ofxOscOnZmq_h */
