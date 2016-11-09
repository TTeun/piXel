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

enum
{
	ID_HELLO,
	ID_GRAY,
	ID_ORIG
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H",
	                 "Help string shown in status bar for this menu item");
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_HELLO);
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText( "Welcome to wxWidgets!" );
}

void MyFrame::OnExit(wxCommandEvent&event)
{
	Close( true );
}
void MyFrame::OnAbout(wxCommandEvent&event)
{
	wxMessageBox( "This is a wxWidgets' Hello world sample",
	              "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent&event)
{
	wxLogMessage("Hello world from wxWidgets!");
}





#endif
