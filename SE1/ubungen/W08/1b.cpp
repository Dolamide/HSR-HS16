void_fastcall TC_FileListView::OnFormResize(TObject *Sender)
{
    const int MIN_WIDTH = 650;
    const int MIN_HEIGHT = 350;

    if(this->Width < MIN_WIDTH)
    {
        this->Width = MIN_WIDTH;
    }
    if(this->Height < MIN_HEIGHT)
    {
        this->Height = MIN_HEIGHT;
    }
}
