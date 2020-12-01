#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();
	this->front_list.clear();
	this->color_list.clear();

	for (int i = 0; i < 500; i++) {

		auto x = ofRandom(-115, 115);
		auto y = (int)(ofRandom(1000) + ofGetFrameNum() * ofRandom(2, 4)) % 600 - 300;
		auto z = ofRandom(-115, 115);
		auto index = this->frame.getNumVertices();

		for (int k = 0; k < 30; k++) {

			auto tmp_y = y - k;
			if (tmp_y > 300 || tmp_y < -300) break;

			auto location = glm::vec3(x, tmp_y, z);

			if (glm::length(location) < 230) {

				location = glm::normalize(location) * 230;
			}

			this->frame.addVertex(location);

			if (k > 0) {

				this->frame.addIndex(index + k - 1); this->frame.addIndex(index + k);
			}
			else {

				this->front_list.push_back(location);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 0.5);

	this->frame.drawWireframe();

	for (int i = 0; i < this->front_list.size(); i++) {

		ofDrawSphere(this->front_list[i], 3);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}