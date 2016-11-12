#include "wximagepanel.h"

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}
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

unsigned char *wxImagePanel::edge(unsigned char *data, size_t width, size_t height)
{
	unsigned char *newData = (unsigned char*)malloc(width * height * 3);

	int minR = 1000, minG = 1000, minB = 1000, maxR = 0, maxG = 0, maxB = 0;

	for (size_t row = 1; row != height - 1; ++row)
		for (size_t col = 1; col != width - 1; ++col)
			for (size_t RGB = 0; RGB != 3; ++RGB)
			{
				if (data[row * width * 3 + col * 3 + RGB] >
				    data[row * width * 3 + col * 3 + RGB - 3])
					newData[row * width * 3 + col * 3 +
					        RGB] = data[row * width * 3 + col * 3 + RGB]
					               - data[row * width * 3 + col * 3 +
					                      RGB - 3];
				else
				{
					newData[row * width * 3 + col * 3 + RGB] = data[row * width * 3 + col * 3 +
					                                                RGB -
					                                                3] -
					                                           data[row * width * 3 + col * 3 +
					                                                RGB];


				}
			}

	for (size_t row = 1; row != height - 1; ++row)
		for (size_t col = 1; col != width - 1; ++col)
		{
			minR = min(minR, newData[row * width * 3 + col * 3]);
			maxR = max(maxR, newData[row * width * 3 + col * 3]);
			minG = min(minG, newData[row * width * 3 + col * 3 + 1]);
			maxG = max(maxG, newData[row * width * 3 + col * 3 + 1]);
			minB = min(minB, newData[row * width * 3 + col * 3 + 2]);
			maxB = max(maxB, newData[row * width * 3 + col * 3 + 2]);
		}
	for (size_t row = 1; row != height - 1; ++row)
		for (size_t col = 1; col != width - 1; ++col)
		{
			newData[row * width * 3 + col * 3] += minR;
			newData[row * width * 3 + col * 3] *= 255 / (float)(maxR - minR);
			newData[row * width * 3 + col * 3 + 1] += minG;
			newData[row * width * 3 + col * 3 + 1] *= 255 / (float)(maxG - minG);
			newData[row * width * 3 + col * 3 + 2] += minB;
			newData[row * width * 3 + col * 3 + 2] *= 255 / (float)(maxB - minB);
		}

	// grayscale(newData, width, height);
	return newData;
}

unsigned char *wxImagePanel::grayscale(unsigned char*data, size_t width, size_t height)
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
	return data;
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
