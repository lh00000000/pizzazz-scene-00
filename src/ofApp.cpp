#include "ofApp.h"
#define SPRING_MIN_STRENGTH     0.005
#define SPRING_MAX_STRENGTH     0.1

#define SPRING_MIN_WIDTH        1
#define SPRING_MAX_WIDTH        3

#define NODE_MIN_RADIUS         1
#define NODE_MAX_RADIUS         2

#define MIN_MASS                .2
#define MAX_MASS                .3

#define MIN_BOUNCE              .8
#define MAX_BOUNCE              .9

#define FIX_PROBABILITY         0      // % probability of a particle being fixed on creation

#define FORCE_AMOUNT            10

#define EDGE_DRAG               0.98

#define GRAVITY                 1

#define MAX_ATTRACTION          10
#define MIN_ATTRACTION          3

#define SECTOR_COUNT            1

bool                mouseAttract    = false;
bool                doMouseXY       = false;        // pressing left mmouse button moves mouse in XY plane
bool                doMouseYZ       = false;        // pressing right mouse button moves mouse in YZ plane
bool                doRender        = true;
int                 forceTimer      = false;


float               rotSpeed        = 0;
float               mouseMass       = 1;

msa::physics::Particle3D		mouseNode;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    physics.setGravity(ofVec3f(0,GRAVITY, 0));
    
    physics.setWorldSize(ofVec3f(-ofGetWidth()/2, -ofGetHeight(), -ofGetWidth()/2), ofVec3f(ofGetWidth()/2, ofGetHeight(), ofGetWidth()/2));
    physics.setSectorCount(SECTOR_COUNT);
    physics.setDrag(0.97f);
    physics.setDrag(1);     // FIXTHIS
    physics.enableCollision();
}

//--------------------------------------------------------------
void ofApp::update(){
    physics.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, 0);
    for(int i=0; i<physics.numberOfParticles(); i++) {
        msa::physics::Particle3D *p = physics.getParticle(i);
        if(p->isFixed()) glColor4f(1, 0, 0, 1);
        else glColor4f(1, 1, 1, 1);
        
        glEnable(GL_ALPHA_TEST);
        
        // draw ball
        glPushMatrix();
        glTranslatef(p->getPosition().x, p->getPosition().y, p->getPosition().z);
        
        
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-p->getRadius(), -p->getRadius());
        glTexCoord2f(1, 0); glVertex2f(p->getRadius(), -p->getRadius());
        glTexCoord2f(1, 1); glVertex2f(p->getRadius(), p->getRadius());
        glTexCoord2f(0, 1); glVertex2f(-p->getRadius(), p->getRadius());
        glEnd();
        
        ofCircle(0, 0, p->getRadius());
        
        glPopMatrix();
        glDisable(GL_ALPHA_TEST);
        
        
        
    }
    //ballImage.getTextureReference().unbind();
    ofDisableNormalizedTexCoords();
    
    ofPopMatrix();
    
    ofDrawBitmapString(" FPS: " + ofToString(ofGetFrameRate(), 2)
                       + " | Number of particles: " + ofToString(physics.numberOfParticles(), 2)
                       + " | Number of springs: " + ofToString(physics.numberOfSprings(), 2)
                       + " | Mouse Mass: " + ofToString(mouseNode.getMass(), 2)
                       + "\nLook at source code keyPressed to see keyboard shortcuts"
                       , 20, 15);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    for (int i =0; i<50; i++) {
        float posX      = ofRandom(-ofGetWidth()/2, ofGetWidth()/2);
        float posY      = ofRandom(0, ofGetHeight());
        float posZ      = ofRandom(-ofGetWidth()/2, ofGetWidth()/2);
        float mass      = ofRandom(MIN_MASS, MAX_MASS);
        float bounce    = ofRandom(MIN_BOUNCE, MAX_BOUNCE);
        float radius    = ofMap(mass, MIN_MASS, MAX_MASS, NODE_MIN_RADIUS, NODE_MAX_RADIUS);
        ofVec3f wind(ofRandomf()/8,0,ofRandomf()/8);
        
        // physics.makeParticle returns a particle pointer so you can customize it
        msa::physics::Particle3D *p = physics.makeParticle(ofVec3f(posX, posY, posZ));
        
        // and set a bunch of properties (you don't have to set all of them, there are defaults)
        p->setMass(mass)->setBounce(bounce)->setRadius(radius)->enableCollision()->makeFree()->setVelocity(wind);
        
    
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

