#include "stdafx.h"
#include "GUI.hpp"
#include "GUIRenderer.hpp"

// Label/Text Element

void Label::Render(GUIRenderData rd)
{
	if(m_dirty)
		m_UpdateText(rd.guiRenderer);

	rd.area.pos = Vector2i(rd.area.pos);
	rd.guiRenderer->RenderText(*rd.rq, m_text, rd.area.pos, color);
}
bool Label::GetDesiredSize(GUIRenderData rd, Vector2& sizeOut)
{
	if(m_dirty)
		m_UpdateText(rd.guiRenderer);

	if(!m_text)
		return false;

	sizeOut = m_text->size;

	return true;
}
void Label::SetText(const WString& text)
{
	m_textString = text;
	m_dirty = true;
}
WString Label::GetText() const
{
	return m_textString;
}
void Label::SetFontSize(uint32 size)
{
	m_fontSize = size;
	m_dirty = true;
}
uint32 Label::GetFontSize() const
{
	return m_fontSize;
}
void Label::m_UpdateText(class GUIRenderer* renderer)
{
	Font fontToUse = m_font;
	if(!fontToUse)
		fontToUse = renderer->font;
	m_text = fontToUse->CreateText(m_textString, m_fontSize);
	m_dirty = false;
}