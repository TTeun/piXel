#include "myapp.h"

bool MyApp::OnInit()
{
	// make sure to call this first
	wxInitAllImageHandlers();
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	frame =
	    new MyFrame(wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600), wxT(
	                    "valve.jpg"), wxBITMAP_TYPE_JPEG);

	frame->actionList->addAction(frame->imageByVal());

	sizer->Add(frame->drawPane(), 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->Show();
	return true;
}
