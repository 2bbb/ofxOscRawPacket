//
//  ofxBianryToOsc.h
//
//  Created by ISHII 2bit on 2018/06/07.
//

#ifndef ofxBianryToOsc_h
#define ofxBianryToOsc_h

#include "ofxOscReceiver.h"

namespace {
    ofxOscMessage process_message(const osc::ReceivedMessage &m) {
        // convert the message to an ofxOscMessage
        ofxOscMessage msg;
        
        // set the address
        msg.setAddress(m.AddressPattern());
        
        // transfer the arguments
        for(osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd(); ++arg){
            if(arg->IsInt32()){
                msg.addIntArg(arg->AsInt32Unchecked());
            }
            else if(arg->IsInt64()){
                msg.addInt64Arg(arg->AsInt64Unchecked());
            }
            else if( arg->IsFloat()){
                msg.addFloatArg(arg->AsFloatUnchecked());
            }
            else if(arg->IsDouble()){
                msg.addDoubleArg(arg->AsDoubleUnchecked());
            }
            else if(arg->IsString()){
                msg.addStringArg(arg->AsStringUnchecked());
            }
            else if(arg->IsSymbol()){
                msg.addSymbolArg(arg->AsSymbolUnchecked());
            }
            else if(arg->IsChar()){
                msg.addCharArg(arg->AsCharUnchecked());
            }
            else if(arg->IsMidiMessage()){
                msg.addMidiMessageArg(arg->AsMidiMessageUnchecked());
            }
            else if(arg->IsBool()){
                msg.addBoolArg(arg->AsBoolUnchecked());
            }
//            else if(arg->IsNil()){
//                msg.addNoneArg();
//            }
            else if(arg->IsInfinitum()){
                msg.addTriggerArg();
            }
            else if(arg->IsTimeTag()){
                msg.addTimetagArg(arg->AsTimeTagUnchecked());
            }
            else if(arg->IsRgbaColor()){
                msg.addRgbaColorArg(arg->AsRgbaColorUnchecked());
            }
            else if(arg->IsBlob()){
                const char * dataPtr;
                osc::osc_bundle_element_size_t len = 0;
                arg->AsBlobUnchecked((const void*&)dataPtr, len);
                ofBuffer buffer(dataPtr, len);
                msg.addBlobArg(buffer);
            }
            else {
                ofLogError("ofxOscReceiver") << "ProcessMessage(): argument in message "
                << m.AddressPattern() << " is an unknown type "
                << (int) arg->TypeTag() << " '" << (char) arg->TypeTag() << "'";
                break;
            }
        }
        
        return msg;
    }
    
    void process_bundle(const osc::ReceivedBundle& b, std::vector<ofxOscMessage> &ms) {
        for(osc::ReceivedBundle::const_iterator i = b.ElementsBegin(); i != b.ElementsEnd(); ++i) {
            if(i->IsBundle()) {
                process_bundle(osc::ReceivedBundle(*i), ms);
            } else {
                ms.push_back(process_message(osc::ReceivedMessage(*i)));
            }
        }
    }
    
    std::vector<ofxOscMessage> process_packet(const char *data, std::size_t size) {
        osc::ReceivedPacket p(data, size);
        std::vector<ofxOscMessage> ms;
        if(p.IsBundle()) {
            process_bundle(osc::ReceivedBundle(p), ms);
        } else {
            ms.push_back(process_message(osc::ReceivedMessage(p)));
        }
        return ms;
    }
};

#endif /* ofxBianryToOsc_h */
