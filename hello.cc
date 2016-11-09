#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include "wxImagePanel/wximagepanel.h"
#include "MyFrame/myframe.h"

class MyApp : public wxApp
{
	MyFrame *frame;
public:
	bool OnInit();
};

bool MyApp::OnInit()
{
	// make sure to call this first
	wxInitAllImageHandlers();
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	frame = new MyFrame(wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

	// then simply create like this
	frame->drawPane = new wxImagePanel( frame, wxT("ass.jpg"), wxBITMAP_TYPE_JPEG);
	wxSize imSize = frame->drawPane->size();
	sizer->Add(frame->drawPane, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->Show();
	return true;
}

IMPLEMENT_APP(MyApp);
