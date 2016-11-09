#include "wximagepanel.h"

wxImagePanel::wxImagePanel(wxFrame*parent, wxString file, wxBitmapType format) :
	wxPanel(parent),
	d_image(new wxImage(file, format))
{
	Bind(wxEVT_PAINT, &wxImagePanel::paintEvent, this);
}

void wxImagePanel::paintEvent(wxPaintEvent &evt)
{
	wxPaintDC dc(this);

	render(dc);
}

// wxImage wxImagePanel::edge(){
//  unsigned char *data = (unsigned char*)malloc(height() * width() * 3);
//  data = d_image->GetData();
//  for (size_t i = 0; i < 3 * width() * height(); i += 3)
//      data[i] = 0;
//  wxImage image(width(), height(), data, false);
//  return image;
// }

void wxImagePanel::grayscale(unsigned char*data, size_t width, size_t height)
{
	float coef[3] = {0.2126, 0.7152, 0.0722};
	int res;

	for (size_t index = 0; index != width * height * 3; index += 3)
	{
		res = 0;
		for (size_t RGB = 0; RGB != 3; ++RGB)
			res += coef[RGB] * data[index + RGB];
		for (size_t RGB = 0; RGB != 3; ++RGB)
			data[index + RGB] = res;
	}

}

void wxImagePanel::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);

	render(dc);
}

void wxImagePanel::render(wxDC &dc)
{
	std::cout << "redrawn\n";
	dc.DrawBitmap( *d_image, 0, 0, false );
}
