#pragma once
#include "Windows.h"

/// <summary>
/// Represents a double WChar, associated with a color
/// </summary>
struct DoubleWChar
{
private:
	WCHAR m_char0;
	WCHAR m_char1;
	WORD m_color;

public:

	/// <summary>
	/// Creates a DoubleWChar
	/// </summary>
	/// <param name="char0">The first char</param>
	/// <param name="char1">The second char</param>
	/// <param name="color">The char's color</param>
	DoubleWChar(WCHAR char0, WCHAR char1, WORD color) :
		m_char0(char0),
		m_char1(char1),
		m_color(color)
	{
	}

	/// <summary>
	/// Assignation operator for the DoubleWChar
	/// </summary>
	/// <param name="other">The other DoubleWChar</param>
	/// <returns>The copied DoubleWChar</returns>
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

	/// <summary>
	/// Inserts the DoubleWChar in a buffer
	/// </summary>
	/// <param name="buffer">The buffer</param>
	/// <param name="index">The index where the chars have to be inserted</param>
	void InsertIn(CHAR_INFO* buffer, int index)
	{
		buffer[index].Char.UnicodeChar = m_char0;
		buffer[index].Attributes = m_color;
		buffer[index + 1].Char.UnicodeChar = m_char1;
		buffer[index + 1].Attributes = m_color;
	}
};

