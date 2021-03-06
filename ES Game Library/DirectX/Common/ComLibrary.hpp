/*
================================================================================
					 オブジェクト指向＆＆ゲームプログラミング
	     Copyright (c) 2011 Human Academy Sendai. All rights reserved.
================================================================================

 【対象ＯＳ】
     Microsoft Windows 7以降

 【コンパイラ】
     Microsoft VisualC++ 2013

 【プログラム】
	 ComLibrary.hpp
				COMライブラリクラスヘッダーファイル

 【バージョン】
	 * Version    2015.10.00      2015/08/28  03:10:03

================================================================================
*/

#pragma once

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include <objbase.h>

//------------------------------------------------------------------------------
//	COMライブラリクラス定義
//------------------------------------------------------------------------------
class CComLibrary {
public:
	static bool Initialize();
	static void Uninitialize();

private:
	static int   m_Ref;		// 参照回数
};
