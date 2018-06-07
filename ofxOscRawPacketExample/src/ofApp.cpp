#include "ofMain.h"
#include "ofxOscRawPacket.h"

#include "ofxZmq.h"

class ofApp : public ofBaseApp {
    ofxZmqPublisher pub;
    ofxZmqSubscriber sub;
    
public:
    void setup() {
        pub.bind("tcp://*:26660");
        sub.connect("tcp://0.0.0.0:26660");
    }
    void update() {
        while(sub.hasWaitingMessage()) {
            ofBuffer buf;
            sub.receive(buf);
            auto ms = ofxOscFromBuffer(buf);
            for(auto &m : ms) {
                ofLogNotice() << m.getAddress() << ": " << m.getNumArgs();
            }
        }
    }
    void draw() {}
    void exit() {}
    
    void keyPressed(int key) {
        if(key == ' ') {
            ofxOscMessage m;
            m.setAddress("/space");
            m.addInt32Arg(32);
            m.addFloatArg(0.0f);
            auto b = ofxOscToBuffer(m);
            pub.send(b);
        } else if(key == OF_KEY_RETURN) {
            ofxOscBundle bundle;
            {
                ofxOscMessage m;
                m.setAddress("/return/a");
                m.addInt32Arg(32);
                m.addFloatArg(0.0f);
                bundle.addMessage(m);
            }
            {
                ofxOscBundle b;
                {
                    ofxOscMessage m;
                    m.setAddress("/return/b/a");
                    m.addInt32Arg(32);
                    m.addFloatArg(0.0f);
                    bundle.addMessage(m);
                }
                {
                    ofxOscMessage m;
                    m.setAddress("/return/b/b");
                    m.addInt32Arg(32);
                    m.addFloatArg(0.0f);
                    bundle.addMessage(m);
                }
                bundle.addBundle(b);
            }
            auto b = ofxOscToBuffer(bundle);
            pub.send(b);
        }
    }
    void keyReleased(int key) {}
    void mouseMoved(int x, int y ) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
};

int main() {
    ofGLFWWindowSettings setting;
    setting.width = 1280;
    setting.height = 720;
    auto window = ofCreateWindow(setting);
    auto app = std::make_shared<ofApp>();
    ofRunApp(window, app);
    ofRunMainLoop();
}
