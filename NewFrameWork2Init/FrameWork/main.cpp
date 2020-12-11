// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>
#include <ctime>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>

#include "MyGlWindow.h"


Fl_Group* widgets;


long lastRedraw;
int frameRate = 30;

void changeFrameCB(Fl_Widget * w, void* data)
{
	Fl_Choice * widget = (Fl_Choice *)w;
	int i = widget->value();
	const char * menu = widget->text(i);
	frameRate = atoi(menu);

	MyGlWindow * win = (MyGlWindow *)data;
	win->redraw();
}


void idleCB(void* w)
{
	MyGlWindow * win = (MyGlWindow *)w;
	if (clock() - lastRedraw > CLOCKS_PER_SEC / frameRate) {
		lastRedraw = clock();
		win->update();
	}
	win->redraw();
}


void but_cb(Fl_Widget* o, void*data) 
{
	Fl_Button* b = (Fl_Button*)o; //ĳ������ �ݵ�� �ʿ�
	MyGlWindow * win = (MyGlWindow *)data;
	win->test();
	win->damage(1);
}


int main()
{
	Fl::scheme("plastic") ;// plastic
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100,100,width,height,"GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window
	
	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();

	MyGlWindow* gl = new MyGlWindow(10, 10, width - 20, height - 50);
	Fl::add_idle((void(*)(void*)) idleCB, gl);  //
	
	widgets->end();
	Fl_Group::current()->resizable(widgets);
	
	Fl_Choice* choice;
	choice = new Fl_Choice(100, height - 40, 50, 20, "FrameRate");
	choice->add("15");
	choice->add("30");
	choice->add("60");
	choice->value(2);
	choice->callback((Fl_Callback*)changeFrameCB, gl);
	

		
	Fl_Button * test = new Fl_Button(width-600, height-40,100,20,"Test");
	test->callback(but_cb, gl);

	

	

	wind->end();

	
	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;
}
