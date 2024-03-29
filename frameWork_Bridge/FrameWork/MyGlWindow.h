
#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>

#include "stdio.h"
#include "math.h"
#include "3DUtils.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

#include "core.h"
#include "mover.h"
#include "plinks.h"

#include <vector>

#define MAX_CONTACT 120

class MyGlWindow : public Fl_Gl_Window {
	public:
		MyGlWindow(int x, int y, int w, int h);
		

		std::vector<Vec3f *> history;
		

		Fl_Slider* time;	
		int run;
		int selected;
		void update();
		void drawStuff();
		void doPick();
		void test();
	private:
		void draw();					// standard FlTk
		void drawBridge(int shadow);
		
		
		int handle(int);				// standard FlTk
		
		float fieldOfView;
		Viewer *m_viewer;
		std::vector<mover *>m_movers;
		cyclone::ParticleWorld *m_world;
		//std::vector<cyclone::ParticleCable*> m_cables;
		//std::vector<cyclone::ParticleRod*> m_rods;
		//std::vector<cyclone::ParticleCableConstraint*> m_supports;
		cyclone::ParticleCable m_cables[10];
		cyclone::ParticleRod m_rods[6];
		cyclone::ParticleCableConstraint m_supports[12];

		cyclone::ParticleContact m_contact[MAX_CONTACT]; // 공간에 등장할 수 있는 최대 충돌 수 = Particle개수 * 10 = 12 * 10 = 120
		// 각종 충돌을 위한 충돌생성기 : 위에 정의한 MyGroundContact 저장
		std::vector<cyclone::ParticleContactGenerator*> m_contactGenerators;
		// 충돌 해결기 (impulse를 계산해서 속도를 변환시키고, 위치를 변경함)
		cyclone::ParticleContactResolver * m_resolver;

		cyclone::Vector3 prevPoint;

		void setProjection(int clearProjection = 1);
		void getMouseNDC(float& x, float& y);
		void setupLight(float x, float y, float z);
};

