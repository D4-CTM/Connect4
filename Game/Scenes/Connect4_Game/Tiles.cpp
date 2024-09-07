#include "Tiles.hpp"

Tiles::Tiles()
: Owner(0)
{}

int Tiles::getOwner()
{ return Owner; }

int Tiles::getRow()
{ return Row; }

int Tiles::getCol()
{ return Col; }

bool Tiles::operator==(int val)
{ return (Owner == val); }

bool Tiles::operator!=(int val)
{ return Owner != val; }

void Tiles::setOwner(int _Owner)
{ Owner = _Owner; }

void Tiles::setRow(int _Row)
{ Row = _Row; }

void Tiles::setCol(int _Col)
{ Col = _Col; }

void Tiles::Draw(TextConsole& Con)
{ BoardRenderer::RenderBlock(Con, Col, Row, Owner); }
