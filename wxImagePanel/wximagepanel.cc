#include "wximagepanel.h"

wxImagePanel::wxImagePanel(wxFrame*parent, wxString file, wxBitmapType format) :
	wxPanel(parent),
	d_image(new wxImage(file, format))
{
	Bind(wxEVT_PAINT, &wxImagePanel::paintEvent, this);
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

void wxImagePanel::render(wxDC&dc)
{
	std::cout << "redrawn\n";
	dc.DrawBitmap( *d_image, 0, 0, false );
}

wxImage wxImagePanel::grayscale()
{
	return d_image->ConvertToGreyscale();
}
