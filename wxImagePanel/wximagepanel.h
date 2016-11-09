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

	void paintEvent(wxPaintEvent &evt);
	void paintNow();
	void render(wxDC &dc);
	wxSize size();
	size_t width();
	size_t height();

	void setImage(wxImage *newImage); wxImage *image(); wxImage imageByVal();
	static void grayscale(wxImage *image);
	// wxImage edge();

};

inline size_t wxImagePanel::width(){
	return d_image->GetWidth();
}

inline size_t wxImagePanel::height(){
	return d_image->GetHeight();
}

inline void wxImagePanel::setImage(wxImage *newImage)
{
	d_image = newImage;
}

inline wxImage *wxImagePanel::image(){ return d_image; }

inline wxImage wxImagePanel::imageByVal() { return *d_image; }

inline wxSize wxImagePanel::size(){ return d_image->GetSize(); }


#endif
