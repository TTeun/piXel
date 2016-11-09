#ifndef MY__FRAME__
#define MY__FRAME__

#include <wx/utils.h>

class MyFrame : public wxFrame
{

public:
	wxImagePanel *drawPane;
	MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
	void OnHello(wxCommandEvent&event);
	void OnExit(wxCommandEvent&event);
	void OnAbout(wxCommandEvent&event);
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{}



#endif
