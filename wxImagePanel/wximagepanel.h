#ifndef WX__IMAGE__PANEL__
#define WX__IMAGE__PANEL__

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>

#include <iostream>

class wxImagePanel : public wxPanel
{
	wxImage *d_image;

public:
	wxImagePanel(wxFrame * parent, wxString file, wxBitmapType format);
	void setImage(wxImage *newImage)
	{
		d_image = newImage;
	}
	wxImage *image()
	{
		return d_image;
	}
	wxImage imageByVal()
	{
		return *d_image;
	}
	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC &dc);
	wxSize size();

	DECLARE_EVENT_TABLE()
};

inline wxSize wxImagePanel::size()
{
	return d_image->GetSize();
}

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
END_EVENT_TABLE();

wxImagePanel::wxImagePanel(wxFrame*parent, wxString file, wxBitmapType format) :
	wxPanel(parent),
	d_image(new wxImage(file, format))
{}

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

void wxImagePanel::render(wxDC&dc)
{
	std::cout << "redrawn\n";
	dc.DrawBitmap( *d_image, 0, 0, false );
}
#endif
