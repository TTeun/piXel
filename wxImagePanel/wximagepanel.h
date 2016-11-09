#ifndef WX__IMAGE__PANEL__
#define WX__IMAGE__PANEL__

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>

class wxImagePanel : public wxPanel
{
	wxImage *d_image;

public:
	wxImagePanel(wxFrame * parent, wxString file, wxBitmapType format);
	void setImage(wxImage *newImage);
	wxImage *image();
	wxImage imageByVal();
	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC &dc);
	wxSize size();

};

inline void wxImagePanel::setImage(wxImage *newImage)
{
	d_image = newImage;
}

inline wxImage *wxImagePanel::image()
{
	return d_image;
}

inline wxImage wxImagePanel::imageByVal()
{
	return *d_image;
}

inline wxSize wxImagePanel::size()
{
	return d_image->GetSize();
}


#endif
