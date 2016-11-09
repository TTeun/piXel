#ifndef WX__IMAGE__PANEL__
#define WX__IMAGE__PANEL__

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>

#include <iostream>

class wxImagePanel : public wxPanel
{
	wxImage d_image;
	wxImage d_gray;
	wxImage const d_orig;

public:
	wxImagePanel(wxFrame * parent, wxString file, wxBitmapType format);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC&dc);
	wxSize size();
	enum Mode { GRAY, ORIG, IMAGE };
	void setMode(Mode mode);
private:
	Mode d_mode = ORIG;

	DECLARE_EVENT_TABLE()
};

inline wxSize wxImagePanel::size()
{
	return d_image.GetSize();
}

inline void wxImagePanel::setMode(Mode mode)
{
	d_mode = mode;
}


BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
END_EVENT_TABLE();

wxImagePanel::wxImagePanel(wxFrame*parent, wxString file, wxBitmapType format) :
	wxPanel(parent),
	d_orig(file, format),
	d_image(file, format)
{
	d_gray = d_image.ConvertToGreyscale();
}

void wxImagePanel::paintEvent(wxPaintEvent &evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);

	render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC&dc)
{
	std::cout << "redrawn\n";
	dc.DrawBitmap( d_mode == ORIG ? d_orig :
	               d_mode == GRAY ? d_gray :
	               d_image
	               , 0, 0, false );
}
#endif
