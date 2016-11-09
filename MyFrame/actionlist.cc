#include "myframe.h"

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

void ActionList::addAction(wxImage && newAction)
{
	d_imageList.push_back(newAction);
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
	d_frame->setImage(&(d_imageList[d_actionSize - 1]));
	d_frame->paintNow();
}
