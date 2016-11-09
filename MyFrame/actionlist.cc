#include "myframe.h"
#include <iostream>

ActionList::ActionList(MyFrame *frame)
	: d_frame(frame)
{}

void ActionList::undo()
{
	if (d_actionSize > 1)
	{
		--d_actionSize;
		update();
	}
}

void ActionList::addAction(void (*f)(unsigned char*, size_t, size_t))
{
	size_t width = (d_imageList[d_actionSize - 1]).GetWidth();
	size_t height = (d_imageList[d_actionSize - 1]).GetHeight();
	unsigned char *data = (unsigned char*)malloc(width * height * 3);

	data = (d_imageList[d_actionSize - 1]).GetData();

	unsigned char *newData = (unsigned char*)malloc(width * height * 3);
	for (size_t i = 0; i < width * height * 3; ++i)
		newData[i] = data[i];

	f(newData, width, height);
	wxImage image(width, height, newData);


	d_imageList.push_back(image);
	++d_actionSize;
	update();
}

void ActionList::addAction(wxImage && newImage)
{
	d_imageList.push_back(newImage);
	++d_actionSize;
	update();
}

void ActionList::redo()
{
	if (d_actionSize < d_imageList.size())
	{
		++d_actionSize;
		update();
	}
}
void ActionList::update()
{
	d_frame->drawPane()->setImage(&(d_imageList[d_actionSize - 1]));
	d_frame->paintNow();
}
