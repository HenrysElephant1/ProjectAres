#include "Hitbox.h"

Hitbox::Hitbox( float w, float l, float x, float z, float d ) {
	locx = x;
	locz = z;
	dir = d;
	width = w;
	length = l;
	height = 1;
	colliding = false;

	calcVecs();
	calcCBMat();
}

Hitbox::~Hitbox() {

}

void Hitbox::calcCBMat() {
	// // glm::vec3 translate = glm::vec3(locx, 0, locz);
	// glm::vec3 l = glm::vec3( Cos(dir)*width/2, 0, Sin(dir)*width/2 );
	// glm::vec3 m = glm::vec3( -Sin(dir)*length/2, 0, Cos(dir)*length/2 );
	// glm::vec3 n = glm::vec3( 0, height, 0 );

	glm::vec3 l = bbr - bbl;
	glm::vec3 m = tbl - bbl;
	glm::vec3 n = bfl - bbl;

	cbMat = glm::mat3(l, m, n);
	cbMat = glm::inverse(cbMat);
}

void Hitbox::calcVecs() {
	glm::vec3 loc = glm::vec3(locx, 0, locz);

	// Hitbox corner points
	// Naming - t/b: Top/Bottom, b/f: Back/Front: l/r: Left/Right
	bbl = loc + glm::vec3( +width/2*Cos(dir) -length/2*Sin(dir),       0, -width/2*Sin(dir) -length/2*Cos(dir) );
	bbr = loc + glm::vec3( -width/2*Cos(dir) -length/2*Sin(dir),       0, +width/2*Sin(dir) -length/2*Cos(dir) );
	tbr = loc + glm::vec3( -width/2*Cos(dir) -length/2*Sin(dir),  height, +width/2*Sin(dir) -length/2*Cos(dir) );
	tbl = loc + glm::vec3( +width/2*Cos(dir) -length/2*Sin(dir),  height, -width/2*Sin(dir) -length/2*Cos(dir) );
	bfl = loc + glm::vec3( +width/2*Cos(dir) +length/2*Sin(dir),       0, -width/2*Sin(dir) +length/2*Cos(dir) );
	bfr = loc + glm::vec3( -width/2*Cos(dir) +length/2*Sin(dir),       0, +width/2*Sin(dir) +length/2*Cos(dir) );
	tfr = loc + glm::vec3( -width/2*Cos(dir) +length/2*Sin(dir),  height, +width/2*Sin(dir) +length/2*Cos(dir) );
	tfl = loc + glm::vec3( +width/2*Cos(dir) +length/2*Sin(dir),  height, -width/2*Sin(dir) +length/2*Cos(dir) );
	
	// Back to front vectors
	bVecs[0]  = bbl;   mVecs[0]  = bfl - bbl;
	bVecs[1]  = tbl;   mVecs[1]  = tfl - tbl;
	bVecs[2]  = tbr;   mVecs[2]  = tfr - tbr;
	bVecs[3]  = bbr;   mVecs[3]  = bfr - bbr;

	// Bottom to top vectors
	bVecs[4]  = bbl;   mVecs[4]  = tbl - bbl;
	bVecs[5]  = bfl;   mVecs[5]  = tfl - bfl;
	bVecs[6]  = bfr;   mVecs[6]  = tfr - bfr;
	bVecs[7]  = bbr;   mVecs[7]  = tbr - bbr;

	// Left to right vectors
	bVecs[8]  = bbl;   mVecs[8]  = bbr - bbl;
	bVecs[9]  = tbl;   mVecs[9]  = tbr - tbl;
	bVecs[10] = tfl;   mVecs[10] = tfr - tfl;
	bVecs[11] = bfl;   mVecs[11] = bfr - bfl;
}

void Hitbox::update( float x, float z, float d ) {
	locx = x;
	locz = z;
	dir = d;
	calcVecs();
	calcCBMat();
	colliding = false;
}

bool Hitbox::testPointHit( float x, float y, float z ) {
	glm::vec3 pointPos = glm::vec3(x-locx,y,z-locz);
	glm::vec3 transformedPos = cbMat * pointPos;
	if( abs(transformedPos.x) <= 1 && abs(transformedPos.y) <= 1 && abs(transformedPos.z) <= 1 )
		return true;
	else
		return false;
}

bool Hitbox::testVolumeHit( float x, float y, float z, float radius ) {
	return true;
}

bool Hitbox::testVectorHit( glm::vec3 pos, glm::vec3 vec ) {
	// Transform input vector to coordinate space formed by hitbox
	glm::vec3 transPos = cbMat * (pos - bbl);
	glm::vec3 transVec = cbMat * vec;

	float t;
	glm::vec3 newVec;

	// Test intersection with plane x=1
	t = (1 - transPos.x) / transVec.x;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.y >= 0 && newVec.y <=1 && newVec.z >= 0 && newVec.z <=1 ) {
			colliding = true;
			return true;
		}
	}

	// Test intersection with plane x=0
	t = (0 - transPos.x) / transVec.x;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.y >= 0 && newVec.y <=1 && newVec.z >= 0 && newVec.z <=1 ) {
			colliding = true;
			return true;
		}
	}

	// Test intersection with plane y=1
	t = (1 - transPos.y) / transVec.y;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.x >= 0 && newVec.x <=1 && newVec.z >= 0 && newVec.z <=1 ) {
			colliding = true;
			return true;
		}
	}

	// Test intersection with plane y=0
	t = (0 - transPos.y) / transVec.y;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.x >= 0 && newVec.x <=1 && newVec.z >= 0 && newVec.z <=1 ) {
			colliding = true;
			return true;
		}
	}

	// Test intersection with plane z=1
	t = (1 - transPos.z) / transVec.z;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.x >= 0 && newVec.x <=1 && newVec.y >= 0 && newVec.y <=1 ) {
			colliding = true;
			return true;
		}
	}

	// Test intersection with plane z=0
	t = (0 - transPos.z) / transVec.z;
	if( t >= 0 && t <=1 ) {
		newVec = transPos + (transVec * t);
		if( newVec.x >= 0 && newVec.x <=1 && newVec.y >= 0 && newVec.y <=1 ) {
			colliding = true;
			return true;
		}
	}

	return false;
}

bool testHitboxCollision( Hitbox *h1, Hitbox *h2 ) {
	for( int i=0; i<12; i++ ) {
		if( h1->testVectorHit( h2->bVecs[i], h2->mVecs[i]) ) {
			h1->colliding = true;
			h2->colliding = true;
			return true;
		}
	}
	return false;
}

void Hitbox::display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();

	// // Test - display transformed hitbox and vector
	// glm::vec3 transPos = cbMat * (glm::vec3(0,0,-5) - bbl);
	// glm::vec3 transVec = cbMat * glm::vec3(0,0,10);
	// glColor3d(0,0,1);
	// glBegin(GL_LINES);
	// glVertex3d(transPos.x, transPos.y, transPos.z);
	// glVertex3d(transPos.x+transVec.x, transPos.y+transVec.y, transPos.z+transVec.z);
	// glEnd();

	// glColor3d(1,0,1);
	// glBegin(GL_LINES);
	// for(int i=0; i<12; i++) {
	// 	glm::vec3 curPos = cbMat * (bVecs[i] - bbl);
	// 	glm::vec3 curVec = cbMat * mVecs[i];
	// 	glVertex3d(curPos.x, curPos.y, curPos.z);
	// 	glVertex3d(curPos.x + curVec.x, curPos.y + curVec.y, curPos.z + curVec.z);
	// }
	// glEnd();

	if( colliding )
		glColor3d(1,0,0);
	else
		glColor3d(0,1,0);
	glBegin(GL_LINES);
	for(int i=0; i<12; i++){
		glVertex3d(bVecs[i].x, bVecs[i].y, bVecs[i].z);
		glVertex3d(bVecs[i].x + mVecs[i].x, bVecs[i].y + mVecs[i].y, bVecs[i].z + mVecs[i].z);
	}
	// glVertex3d(0,0,-5);
	// glVertex3d(0,0,5);
	glEnd();

	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
