#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(255, 32);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	if (ofGetFrameNum() % 50 < 30) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 30, 0.1, 0);
	}

	float size = 1;
	for (float x = 80; x <= ofGetWidth() - 80; x += size) {

		for (float y = 80; y <= ofGetHeight() - 80; y += size) {

			if (glm::distance(glm::vec2(x, y), ofGetWindowSize() * 0.5) < 300) {

				float deg = ofMap(ofNoise(x * 0.0035, y * 0.0035, this->noise_step), 0, 1, -1800, 1800);
				this->mesh.addVertex(glm::vec3(
					x + size * 3 * cos(deg * DEG_TO_RAD), 
					y + size * 3 * sin(deg * DEG_TO_RAD),
					ofMap(abs(deg), 0, 360, 0, 250)));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(ofGetWindowSize() * -0.5);

	this->mesh.drawVertices();

	this->cam.end();

	/*
	int start = 500;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}