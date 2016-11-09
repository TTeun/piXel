#ifndef MY__FRAME__
#define MY__FRAME__

#include "../wxImagePanel/wximagepanel.h"
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
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
	~MyFrame();
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

class ActionList {
	std::vector<wxImage> d_imageList;
	size_t d_actionSize = 0;
	MyFrame *d_frame;
public:
	ActionList(MyFrame * frame);
	void addAction(wxImage && newAction);
	void undo();
	void redo();
	void update();
};

inline wxImage MyFrame::imageByVal()
{
	return d_drawPane->imageByVal();
}

inline void MyFrame::setImage(wxImage *newImage)
{
	d_drawPane->setImage(newImage);
}

inline void MyFrame::paintNow()
{
	d_drawPane->paintNow();
}

inline void MyFrame::OnGray(wxCommandEvent &event)
{
	actionList->addAction(imageByVal().ConvertToGreyscale());
}

inline void MyFrame::OnUndo(wxCommandEvent &event)
{
	actionList->undo();
}

inline void MyFrame::OnRedo(wxCommandEvent &event)
{
	actionList->redo();
}

inline void MyFrame::OnExit(wxCommandEvent &event)
{
	Close( true );
}

inline void MyFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox( "This is a wxWidgets' Hello world sample",
	              "About Hello World", wxOK | wxICON_INFORMATION );
}
inline void MyFrame::OnHello(wxCommandEvent &event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

inline wxImagePanel *MyFrame::drawPane()
{
	return d_drawPane;
}
#endif
