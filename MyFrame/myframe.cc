#include "myframe.h"

enum
{
	ID_HELLO,
	ID_GRAY,
	ID_EDGES,
	ID_UNDO,
	ID_REDO
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
                 wxString file,
                 wxBitmapType format)
	: wxFrame(NULL, wxID_ANY, title, pos, size),
	d_drawPane(new wxImagePanel(this, file, format)),
	actionList(new ActionList(this))
{
	wxMenu *menuFile = new wxMenu;

	// FILE MENU //
	menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H",
	                 "Help string shown in status bar for this menu item");
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_HELLO);
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	// EDIT MENU //
	wxMenu *menuEdit = new wxMenu;
	menuEdit->Append(ID_UNDO, "&Undo...\tCtrl-U", "Revert to original image");
	Bind(wxEVT_MENU, &MyFrame::OnUndo, this, ID_UNDO);
	menuEdit->Append(ID_REDO, "&Redo...\tCtrl-Y", "Revert to original image");
	Bind(wxEVT_MENU, &MyFrame::OnRedo, this, ID_REDO);
	menuEdit->AppendSeparator();
	menuEdit->Append(ID_GRAY, "&Grayscale...\tCtrl-G", "Convert image to grayscale");
	Bind(wxEVT_MENU, &MyFrame::OnGray, this, ID_GRAY);
	menuEdit->Append(ID_EDGES, "&Sobel...\tCtrl-E", "Sobel filter");
	Bind(wxEVT_MENU, &MyFrame::OnEdge, this, ID_EDGES);

	// HELP MENU //
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);


	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuEdit, "&Edit" );
	menuBar->Append( menuHelp, "&Help" );
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText( "Welcome to wxWidgets!" );
}

MyFrame::~MyFrame()
{
	delete d_drawPane;
}
