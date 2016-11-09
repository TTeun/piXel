#include "../MyFrame/myframe.h"
#include "../wxImagePanel/wximagepanel.h"
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/utils.h>

class MyApp : public wxApp
{
	MyFrame *frame;
public:
	bool OnInit();
};
