#pragma once

#include <windows.h>
#include <cassert>

/// <summary>
///時間計測用のクラス
/// </summary>
class TimeMeasure
{
private:
	///<summary>
	///単位時間(1フレ当たりの経過時間)
	/// </summary>
	LARGE_INTEGER freq;
	/// <summary>
	/// 計測の開始時間
	/// </summary>
	LARGE_INTEGER start;
	/// <summary>
	/// 計測の終了時間
	/// </summary>
	LARGE_INTEGER end;
	/// <summary>
	/// 前回のLapの時間
	/// </summary>
	LARGE_INTEGER before;
	/// <summary>
	/// 現在の時間
	/// </summary>
	LARGE_INTEGER now;
	/// <summary>
	/// 関数を呼んだか確認する用のステート変数
	/// </summary>
	int state;
public:
	TimeMeasure();
	//計測用の関数(Start➛Endの順で呼びましょう)
	void Start();
	double End();

	double Lap();
	~TimeMeasure() {}

};