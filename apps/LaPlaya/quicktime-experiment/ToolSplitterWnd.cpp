/*************************************************************************
                     LaPlaya
**************************************************************************

Copyright (C) June, 2001 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/

// ToolSplitterWnd.cpp: implementation of the CToolSplitterWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LaPlaya.h"
#include "ToolSplitterWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolSplitterWnd::CToolSplitterWnd()
{
	m_cxSplitter=3;      // put your own values here, to make the splitter fit your needs
	m_cySplitter=3;
	m_cxBorderShare=0;
	m_cyBorderShare=0;
	m_cxSplitterGap=3;
	m_cySplitterGap=3;
}

CToolSplitterWnd::~CToolSplitterWnd()
{

}

int CToolSplitterWnd::HitTest(CPoint pt) const
{
	ASSERT_VALID(this);

	return 0;
}
