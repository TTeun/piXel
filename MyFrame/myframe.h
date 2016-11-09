#ifndef MY__FRAME__
#define MY__FRAME__

#include <wx/utils.h>
#include <vector>
class ActionList;

class MyFrame : public wxFrame
{
	friend class ActionList;

	wxImagePanel *d_drawPane;
public:
	MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
	        wxString file,
	        wxBitmapType format);
	~MyFrame()
	{
		delete d_drawPane;
	}
	wxImagePanel *drawPane();
	void setImage(wxImage *newImage);
	void paintNow();
	wxImage imageByVal();

	ActionList *actionList;
private:
	void OnHello(wxCommandEvent &event);
	void OnGray(wxCommandEvent &event);
	void OnUndo(wxCommandEvent &event);
	void OnRedo(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
};

inline wxImagePanel *MyFrame::drawPane()
{
	return d_drawPane;
}


inline void MyFrame::setImage(wxImage *newImage)
{
	d_drawPane->setImage(newImage);
}
inline void MyFrame::paintNow()
{
	d_drawPane->paintNow();
}
inline wxImage MyFrame::imageByVal()
{
	return d_drawPane->imageByVal();
}


class ActionList {
	std::vector<wxImage> d_imageList;
	size_t d_actionSize = 0;
	MyFrame *d_frame;
public:
	ActionList(MyFrame * frame)
		: d_frame(frame)
	{}
	void addAction(wxImage && newAction)
	{
		d_imageList.push_back(newAction);
		++d_actionSize;
		update();
	}
	void undo()
	{
		if (d_actionSize > 1)
		{
			--d_actionSize;
			update();
		}
	}
	void redo()
	{
		if (d_actionSize < d_imageList.size())
		{
			++d_actionSize;
			update();
		}
	}
	void update()
	{
		d_frame->setImage(&(d_imageList[d_actionSize - 1]));
		d_frame->paintNow();
	}
};

enum
{
	ID_HELLO,
	ID_GRAY,
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

void MyFrame::OnGray(wxCommandEvent &event)
{
	actionList->addAction(imageByVal().ConvertToGreyscale());
}

void MyFrame::OnUndo(wxCommandEvent &event)
{
	actionList->undo();
}

void MyFrame::OnRedo(wxCommandEvent &event)
{
	actionList->redo();
}

void MyFrame::OnExit(wxCommandEvent &event)
{
	Close( true );
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox( "This is a wxWidgets' Hello world sample",
	              "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent &event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

#endif
