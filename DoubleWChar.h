#pragma once
#include "Windows.h"

struct DoubleWChar
{
private:
	WCHAR m_char0;
	WCHAR m_char1;
	WORD m_color;

public:

	DoubleWChar(WCHAR char0, WCHAR char1, WORD color) :
		m_char0(char0),
		m_char1(char1),
		m_color(color)
	{
	}

	DoubleWChar& operator=(const DoubleWChar& other) 
	{
		if (this == &other) 
		{
			return *this;
		}

		m_char0 = other.m_char0;
		m_char1 = other.m_char1;
		m_color = other.m_color;

		return *this;
	}

	void InsertIn(CHAR_INFO* buffer, int index)
	{
		buffer[index].Char.UnicodeChar = m_char0;
		buffer[index].Attributes = m_color;
		buffer[index + 1].Char.UnicodeChar = m_char1;
		buffer[index + 1].Attributes = m_color;
	}
};

